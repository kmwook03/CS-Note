## Process

$\Rightarrow$ 운영체제에 의해 **실행 중인 프로그램**


### Scheduling

여러 프로세스를 동시에 실행시킬 때 어떤 순서로 실행시킬지 결정하는 방식

- 시분할(Time-Sharing) 스케쥴링

    - 개별 프로세스에 CPU 사용 시간을 할당함
- 실시간(Real-time) 스케쥴링

    - 데드라인 내에 실행 완료를 보장함

### Process State

- new: 생성됨
- running: 실행 중
- waiting: 다른 이벤트를 대기 중
- ready: CPU 할당 대기 중
- terminated: 실행 완료

$\Rightarrow$ 운영체제는 프로세스 상태를 저장 및 관리해야 한다!

어디에? $\rightarrow$ **PCB(Process Control Block)**

### ps

```bash
kmwook@kmwookgram:~$ ps -af
UID          PID    PPID  C STIME TTY          TIME CMD
kmwook      1082     776  0 18:47 pts/1    00:00:00 -bash
kmwook     41641     775  0 19:41 pts/0    00:00:00 ps -af
kmwook@kmwookgram:~$ ps -l
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S  1000     775     774  0  80   0 -  2541 do_wai pts/0    00:00:00 bash
0 R  1000   41920     775  0  80   0 -  2092 -      pts/0    00:00:00 ps
```

- UNIX Process State

    - O: 프로세스가 수행 중
    - S: 이벤트 대기 중
    - R: 프로세스가 실행 큐(run queue)에 있음
    - Z: 프로세스가 종료했으나 부모가 안거둬감
    - T: 작업제어 시그널이나 트레이스 동작에 의해 프로세스가 정지됨

### Process Management Data Structures

- In memory

    - User structure
    - Process table
    - Kernel Stack
    - Process address space

### User Level Context Switch Implementation

```c
// Task structure
typedef struct {
    ucontext_t context;
    int id;
    char stack[STACK_SIZE];
} TCB; // PCB의 흉내
```

`ucontext_t` : 실행 중인 프로세스 또는 스레드의 Context를 사용자 공간 메모리에 캡쳐하여 저장

```c
TCB taskQueue[MAX_TASK]; // 모든 태스크의 TCB를 저장하는 테이블
int readyQueue[MAX_TASK]; // 실행 대기 큐 (taskQueue의 인덱스 저장)
int currentTask = -1;  // 현재 실행 중인 작업
int front = 0, rear = 0; // ready queue의 처음과 끝 인덱스

void enqueue(int taskId) {
    readyQueue[rear] = taskId; // rear 자리에 새로운 태스크 추가
    rear = (rear + 1) % MAX_TASK; // rear 인덱스 증가
}

int dequeue() {
    if (front == rear) {
        return -1; // Queue is empty
    }
    int taskId = readyQueue[front]; // 다음 실행될 태스크
    front = (front + 1) % MAX_TASK; // front 인덱스 증가
    return taskId;
}

void scheduler(int signum) {
    int previousTask = currentTask;
    // 현재 실행 중인 태스크의 taskQueue 인덱스를 readyQueue에 넣음
    enqueue(previousTask); 
    // readyQueue에서 다음 태스크의 taskQueue 인덱스를 빼옴
    currentTask = dequeue();
    // 이전 태스크와 다음 태스크의 context를 교체함
    swapcontext(&taskQueue[previousTask].context, 
                &taskQueue[currentTask].context);
}
```

`swapcontext(ucontext_t *old, const ucontext_t *new)` : 현재 context 저장 + 다른 context로 저장

1. 현재 CPU 상태 -> old에 저장
2. new에 저장된 CPU 상태 복원
3. new가 가리키는 지점부터 실행

```c
void taskFunction(int id) {
    while (1) {
        printf("Running Task %d\n", id);
        fflush(stdout);
        pause(); // It need SIGALRM
    }
}
```
`pause()` : 프로세스를 대기 상태로 변경 -> CPU 반납

```c
int main() {
    // itimerval: 타이머의 만료 시간과 반복 주기를 설정하는 구조체
    struct itimerval timer; // time.h에 위치

    // 작업 초기화
    for (int i = 0; i < MAX_TASK; i++) {
        // 작업 id 할당
        taskQueue[i].id = i; 
        // 현재 cpu 상태 저장
        getcontext(&taskQueue[i].context);
        
        // getcontext()로 복제한 건 main() 함수의 context임
        // 스택 포인터(SP) 재설정 필요함
        
        // sp 시작 주소를 TCB 구조체의 stack 배열 시작 주소로 설정
        taskQueue[i].context.uc_stack.ss_sp = taskQueue[i].stack;
        // 스택 크기를 TCB 구조체의 stack 배열 크기로 설정
        taskQueue[i].context.uc_stack.ss_size = sizeof(taskQueue[i].stack);
        // context 종료 시 실행할 context = NULL -> 종료 
        taskQueue[i].context.uc_link = NULL;

        // context가 시작되면 실행할 함수 지정 -> taskFunction()
        makecontext(&taskQueue[i].context, (void (*)(void))taskFunction, 1, i);
        // 레디 큐에 넣음
        enqueue(i);
    }

    // 타이머 초기화
    // it_value: 첫 알람 울릴 시간
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = TIME_SLICE;
    // => 타이머 ON 후 500ms가 지난 시점에 첫 인터럽트 발생

    // it_interval: 반복 주기
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = TIME_SLICE;
    // => 첫 알람 이후 적용될 알람 반복 주기 = 500ms

    // 타이머 ON 요청
    setitimer(ITIMER_REAL, &timer, NULL);
    // SIGALRM이 오면 scheduler 함수로 실행 흐름 강제 이동
    signal(SIGALRM, scheduler);
    
    // 현재 수행할 작업 꺼냄
    currentTask = dequeue();
    // context 실행
    setcontext(&taskQueue[currentTask].context);

    return 0;
}
```

**출력**

```bash
kmwook@kmwookgram:~/advUNIX/UserLevelContextSwitch$ ./userLevelCtx 
Running Task 0
Running Task 1
Running Task 2
Running Task 0
     .
     .
     .
```

**전체 코드**

```c
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define STACK_SIZE 8192
#define MAX_TASK 3
#define TIME_SLICE 5* 100000 // 500ms

// Task structure
typedef struct {
    ucontext_t context;
    int id;
    char stack[STACK_SIZE];
} TCB;

TCB taskQueue[MAX_TASK];
int readyQueue[MAX_TASK];
int currentTask = -1;
int front = 0, rear = 0;

void enqueue(int taskId) {
    readyQueue[rear] = taskId;
    rear = (rear + 1) % MAX_TASK;
}

int dequeue() {
    if (front == rear) {
        return -1; // Queue is empty
    }
    int taskId = readyQueue[front];
    front = (front + 1) % MAX_TASK;
    return taskId;
}

void scheduler(int signum) {
    int previousTask = currentTask;
    enqueue(previousTask);
    currentTask = dequeue();
    swapcontext(&taskQueue[previousTask].context, &taskQueue[currentTask].context);
}

void taskFunction(int id) {
    while (1) {
        printf("Running Task %d\n", id);
        fflush(stdout);
        pause(); // It need SIGALRM
    }
}

int main() {
    struct itimerval timer;
    // Initialize tasks
    for (int i = 0; i < MAX_TASK; i++) {
        taskQueue[i].id = i;
        getcontext(&taskQueue[i].context);
        taskQueue[i].context.uc_stack.ss_sp = taskQueue[i].stack;
        taskQueue[i].context.uc_stack.ss_size = sizeof(taskQueue[i].stack);
        taskQueue[i].context.uc_link = NULL;
        makecontext(&taskQueue[i].context, (void (*)(void))taskFunction, 1, i);
        enqueue(i);
    }

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = TIME_SLICE;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = TIME_SLICE;
    setitimer(ITIMER_REAL, &timer, NULL);
    signal(SIGALRM, scheduler);
    
    currentTask = dequeue();
    setcontext(&taskQueue[currentTask].context);

    return 0;
}

```
