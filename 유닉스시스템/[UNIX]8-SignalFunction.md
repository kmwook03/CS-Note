## Signal Function

### sigaction
```c
int sigaction(int signo,
            const struct sigaction *restrict act
            struct sigaction *restrict oact);
```

* `signo` : 기능을 조사하거나 변경하고자 하는 시그널 번호
* `act` : `signo`에 대해 새롭게 적용할 액션 지정(핸들러 포인터)
* `oact` : 기존에 설정되어 있던 액션 정보를 이 구조체에 담아서 반환

```c
struct sigaction {
    void (*sa_handler)(int); // 시그널 핸들러 함수 포인터
    // 또는 SIG_IGN 또는 SIG_DFL
    sigset_t sa_mask; // 추가로 블락할 시그널
    int sa_flags; // 시그널 옵션

    // 선택적 활용 핸들러
    void (*sa_sigaction)(int, siginfo_t*, void*);
};
```

* `sa_handler` : 시그널 catch 시 호출할 핸들러 포인터 (또는 SIG_IGN 또는 SIG_DFL)
* `sa_mask` : 핸들러 호출 전 프로세스 마스크에 추가될 시그널 집합
* `sa_flags` : 시그널 처리 옵션

    * (e.g.) `SA_RESTART`

### sigsetjmp / siglongjmp
```c
int sigsetjmp(sigjmp_buf env, int savemask);
```
되돌아올 지점(`env`)을 설정하고 저장

* `savemask`

    * 0이 아닌 값: 현재 프로세스의 시그널 마스크를 `env`에 저장
    * 0: 시그널 마스크 저장 X

```c
void siglongjmp(sigjmp_buf env, int val);
```
sigsetjmp()로 저장해 둔 env 지점으로 프로세스 실행 흐름 점프
savemask를 설정했다면 시그널 마스크까지 원래대로 복구시킴

### sigsuspend

> **등장 배경: `pause()`를 이용한 시그널 대기의 문제점**

기존 전역 변수와 pause()를 조합해 대기하던 방식은 심각한 경쟁 조건 문제가 있음

```c
while (flag == 0)
    // 이 때 시그널이 발생한다면?
    pause();
```

만약 시그널이 flag 검사 후 `pause()` 호출 직전에 발생한다면

* 시그널 핸들러가 실행되어 `flag`를 1로 변경함
* 프로세스는 이후 `pause()`를 호출하여 sleep
* 이미 시그널이 지나갔기 때문에 프로세스는 깨어나지 못함

**Solution: 시그널 마스크 해제와 프로세스 sleep을 원자적으로 처리**
$\Rightarrow$ `sigsuspend()`

```c
int sigsuspend(const sigset_t *sigmask);
```
항상 `-1`을 반환하며 `errno`는 `EINTR`로 설정됨

* **원자적 동작 과정**

    1. 시그널 마스크 임시 교체

        * 현재 시그널 마스크를 인자로 전달된 `sigmask`로 잠시 교체
    2. 프로세스 일시 정지

        * sleep
    3. 복구 및 리턴

        * 블록 해제된 시그널 도착
        * 핸들러 실행
        * 시그널 마스크 원상복구
        * 리턴

#### 예제 분석: sigsuspend를 활용한 동기화

```c
// USR1 USR2 Parent Child Process Synchronization using flag
// signal이 queuing 되는지 확인
// Ctrl+C를 눌렀을 때 중첩이 되는지 확인하라는 뜻 -> signal handler가 중첩 실행 되는가?

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static volatile sig_atomic_t sigflag; // 핸들러에 의해 nonzero로 변경됨
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) {
    sigflag = 1;
}

void charattime(char *str) {
    char *ptr;
    int c;
    setbuf(stdout, NULL); // unbuffered
    for (ptr = str; (c = *ptr++) != 0; ) {
        putc(c, stdout);
    }
}

void TELL_WAIT() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("signal(SIGUSR1) error");
        exit(1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("signal(SIGUSR2) error");
        exit(1);
    }
    // signal mask 초기화
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    // newmask에 SIGUSR1, SIGUSR2 추가
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    // SIGUSR1, SIGUSR2 블록
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("SIG_BLOCK error");
        exit(1);
    }
}

void TELL_PARENT(pid_t pid) {
    kill(pid, SIGUSR2); // 부모 프로세스에게 SIGUSR2 신호 전송
}

void WAIT_PARENT() {
    while (sigflag == 0) {
        sigsuspend(&zeromask); // 신호가 올 때까지 대기
    }
    sigflag = 0; // 신호 처리 후 플래그 초기화
}

void TELL_CHILD(pid_t pid) {
    kill(pid, SIGUSR1); // 자식 프로세스에게 SIGUSR1 신호 전송
}

void WAIT_CHILD() {
    while (sigflag == 0) {
        sigsuspend(&zeromask); // 신호가 올 때까지 대기
    }
    sigflag = 0; // 신호 처리 후 플래그 초기화
}

int main() {
    pid_t pid;
    char str[100] = {0};

    // 시그널 마스크 및 핸들러 초기화
    TELL_WAIT();
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid > 0) { // 부모 프로세스
        for (int i = 0; i < 10; i++) {
            charattime("Output from parent\n");
            TELL_CHILD(pid); // 자식 프로세스에게 신호 전송
            WAIT_CHILD(); // 자식 프로세스의 신호 대기
        }
        if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
            perror("SIG_SETMASK error");
            exit(1);
        }
        exit(0);
    } else { // 자식 프로세스
        for (int i = 0; i < 10; i++) {
            WAIT_PARENT(); // 부모 프로세스의 신호 대기
            charattime("Output from child\n");
            TELL_PARENT(getppid()); // 부모 프로세스에게 신호 전송
        }
        if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
            perror("SIG_SETMASK error");
            exit(1);
        }
        exit(0);
    }

    return 0;
}

```

`출력`
```bash
$ ./sigSync
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
Output from parent
Output from child
```

* **동작 원리**

    * `volatile sig_atomic_t sigflag`
        
        * `volatile` : 시그널 핸들러와 메인 루프 간에 공유되는 변수에 컴파일러 최적화 방지
    * `sigprocmask`

        * TELL_WAIT()에서 시그널을 미리 블록해둠
        * 대기 상테에 들어가기 전에 시그널이 도착하여 발생하는 데드락 방지
    * **`sigsuspend(&zeromask)`**

        * 시그널 블록 해제와 대기 상태 전환을 원자적으로 수행
        * 시그널이 도착하면 핸들러 실행 후 원래 블록 상태로 복구하고 반환

* **부모 프로세스 동작 과정**

    1. 출력(`charattime`)

        * 루프가 시작되자마자 문자열을 한 글자씩 출력
    2. 시그널 전송(`TELL_CHILD`)

        * 출력 마친 후 자식 프로세스에 `SIGUSR1` 시그널 전송
    3. 대기(`WAIT_CHILD`)

        * 자식이 출력을 마치고 다시 시그널을 전송해줄 때 까지 대기(`sigsuspend`)
        * `SIGUSR2` 시그널이 도착하면 깨어난 후 `sigflag` 초기화
        * 1단계부터 다시 수행

* **자식 프로세스 동작 과정**

    1. 대기(`WAIT_PARENT`)

        * 부모가 `SIGUSR1` 시그널을 전송해줄 때 까지 대기
        * 시그널이 도착하면 깨어난 후 실행 재개
    2. 출력(`charattime`)

        * 문자열을 한 글자씩 출력
    3. 시그널 전송

        * 출력 마친 후 부모 프로세스에 `SIGUSR2` 시그널 전송
        * 1단계부터 다시 수행

* **전체 실행 순서 정리**

    1. 부모: 출력 $\rightarrow$ 시그널 전송 $\rightarrow$ 대기
    2. 자식: 대기 $\rightarrow$ 출력 $\rightarrow$ 시그널 전송

`charattime`은 한글자씩 찍어내는 함수이므로, 이러한 동기화 처리가 없으면 글자가 섞여서 출력된다.

`sigsuspend(&zeromask)`의 의미: 모든 시그널을 다 열어두고 대기하겠다.
즉, 평소에는 시그널을 놓치지 않게 막아두었다가 대기하는 순간에만 열어두겠다는 뜻이다.
