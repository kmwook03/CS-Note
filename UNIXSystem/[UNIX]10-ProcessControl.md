## Process Control

### wait
자식 프로세스가 종료하면 부모 프로세스에게 `SIGCHLD` 시그널을 전송하여 대기 상태를 해제한다.

```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *statloc);
```
자식 프로세스가 실행되는 동안 대기하다가 자식 프로세스가 종료하면 종료 상태 값과 함께 리턴한다.

* `statloc` : 종료된 자식 프로세스의 종료 상태 값 저장
* `반환값` : 자식 프로세스의 PID (없을 경우 `-1`)

자식 프로세스가 여러 개인 경우 그 중 하나만 종료해도 리턴한다.
만약 부모 프로세스가 wait()에서 리턴 후에 곧바로 종료하지 않고 다른 작업 수행을 이어간다면, 그 사이 종료된 자식 프로세스들이 좀비 프로세스가 된다.

```c
pid_t waitpid(pid_t pid, int *statloc, int options);
```
자식 프로세스들 중 하나라도 종료되면 리턴했던 wait과 달리 특정 자식의 종료를 대기할 수 있다.

* pid 인자 설정

    * pid == -1 : 아무 자식이나 기다림
    * pid > 0 : PID가 `pid`인 자식 기다림
    * pid == 0 : 같은 프로세스 그룹에 속하는 자식 중 하나를 기다림
    * pid < -1 : PID가 `abs(pid)`인 자식 기다림

### Zombie Process
자식 프로세스가 종료되었지만, 부모 프로세스가 아직 그 자식의 종료 상태를 회수하지 않아 시스템 프로세스 테이블에 껍데기 정보만 남아있는 상태

#### Avoid Zombie Process : Double Fork
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char ** argv)
{
    pid_t   pid, waitPID;
    int     status, data = 10;
    // 부모 프로세스(A)
    if ((pid = fork()) < 0) // 첫 번째 fork
        perror("fork error");

    if (pid == 0) { // 자식 프로세스(B)
        if ((pid = fork()) < 0) // 두 번째 fork
            perror("fork error");
        else if (pid > 0) { // B
                // A의 pid
            printf("first child, parent id: %d\n", getppid());
            // B의 pid
            printf("first child, its own id: %d\n", getpid());
            exit(0); // B 죽음
            // 부모가 죽었으니까, C는 고아가 되어 init에 입양됨
            // 따라서 C는 좀비가 될 수 없음
            // C의 종료는 init이 받는다.
        }
        // C 실행
        // sleep(2)가 필요한 이유:
        // B가 C 보다 먼저 죽는 것을 보장하기 위함
        sleep(2);
        data = data + 1;

        // B 죽음 -> init PID
        printf("second child. parent id: %d\n", getppid());
        // C의 pid
        printf("second child. its own id: %d\n", getpid());

        exit(0);
    }  

    waitPID = waitpid(pid, NULL, 0);  // pid => B의 pid

    if (waitPID != pid) // 자식 기다림
        perror("Wait error");

    // 셸의 pid
    printf("parent process, parent id: %d\n", getppid());
    // A의 pid
    printf("parent process, its own id: %d\n", getpid());

    exit(0);
}
```

### Race Condition between Process
여러 개의 프로세스가 공유된 데이터에 대해 작업을 수행하려고 할 때 발생

* Solution

    * Signal
    * Semaphore
    * Mutex

### exec
```c
#include <unistd.h>

// l: list 형태의 명령 인자
int execl(const char *path, const char *arg0, ..., 
            const char *argn, (char*) 0);

// v: vector 형태의 명령 인자
int execv(const char* path, char *const argv[]);

// l: list 형태의 명령 인자
// e: 환경 변수 인자
int execle(const char* path, const char *arg0, ..., 
            const char *argn, (char *)0, char *const envp[]);

// v: vector 형태의 명령 인자
// e: 환경 변수 인자
int execve(const char* path, char *const argv[], 
            char *const envp[]);

// l: list 형태의 명령 인자
// p: 패스 정보 없는 실행 파일 이름
int execlp(const char *file, const char *arg0, ..., 
            const char *argn, (char *)0);

// v: vector 형태의 명령 인자
// p: 패스 정보 없는 실행 파일 이름
int execvp(const char *file, char *const argv[]);
```
현재 실행 중인 프로세스의 메모리 공간에 새로운 프로그램 이미지(바이너리 코드)를 덮어씌워 실행하는 함수

`(주의): execve만이 시스템 콜이고, 나머지 exec 계열 함수는 내부적으로 execve 함수를 호출함`
```
    +--------+      +-------+      +--------+
    | execlp |      | execl |      | execle | 
    +--------+      +-------+      +--------+
        |               |               |
        ▼               ▼               ▼
    +--------+      +-------+      +--------+
    | execvp | ---> | execv | ---> | execve | system call
    +--------+      +-------+      +--------+
```

* `path`: 실행될 프로세스 이미지 파일 경로
* `arg0,..., argn` 또는 `argv[]`: 실행될 프로세스 명령 라인 인자
* `envp[]`: 실행될 프로세스 환경 변수 인자
* `file`: 완전한 패스 정보를 제외한 파일 이름

* return: 성공 시 없음, 실패 시 `-1`

    * 성공 시 새로운 프로그램이 프로세스를 장악하기 때문에 exec 이후 코드는 실행되지 않음

> **exec에 계승되는 속성**
* PID, PPID
* 사용자 ID, 그룹 ID, 보조 그룹 ID (실제)
* 프로세스 그룹 ID, 세션 ID, 제어 터미널
* alarm 시그널까지 남은 시간
* 현재 작업 디렉토리, root 디렉토리
* 파일 생성 마스크(권한), 파일 잠금
* 시그널 마스크, 처리되지 않은 시그널
* 자원 제약
* CPU 사용 시간
* 파일 디스크립터
* 시그널 처리(catch)


