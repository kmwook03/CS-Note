## Signal
OS가 프로세스에 보내는 비동기적인 소프트웨어 인터럽트
랜덤한 시간에 랜덤하게 발생하는 비동기적 특성을 가진다.

```
    시그널 발생
        |
        ▼
    커널이 적절한 
    시그널 핸들러 실행
```

* 시그널 발생 상황

    * 터미널 입력

        * (e.g.) Ctrl + C
    * 하드웨어 예외

        * (e.g.) SIGFPE, SIGSEGV
    * 소프트웨어 상태
        
        * (e.g.) SIGURG, SIGALRM

모든 시그널은 이름과 번호를 가지고 있으며 이름은 `SIG`로 시작된다.

`(e.g.)`

| 번호 | 이름 |
|-|-|
| 2 | SIGINT |
| 9 | SIGKILL |
| 11 | SIGSEGV |

모든 번호는 양의 정수지만, kill 함수는 시그널 넘버로 0을 받을 수 있다.

```c
// 프로세서에 시그널을 보내는 함수
int kill(pid_t pid, int signo);
```
signo로 0을 받으면 해당 프로세스가 살아있는지 확인하는 테크닉으로 사용할 수 있다.

### Signal Disposition

1. Ignore the signal : 무시

    * 주의: SIGKILL과 SIGSTOP은 무시할 수 없음
2. Catch the signal : 사용자 정의 핸들러 호출
3. Default action : 디폴트 핸들러 호출

새로운 프로그램이 exec()에 의해 로드되면 기존 프로세스가 메모리에 가지고 있던 시그널 핸들러 함수의 주소공간이 모두 사라진다.
따라서 기존에 별도의 핸들러를 설정해 두었던 시그널들은 모두 기본 동작으로 리셋된다.
단, 무시 설정된 시그널은 그대로 유지된다.


### Signal Function

```c
void (*signal(int signo, void (*func)(int)))(int);
```

* `signo`: 처리할 시그널 넘버
* `void(*func)(int)`: 시그널 핸들러 함수 포인터

    * `func` 인자에는 함수 포인터 외에 다음 매크로도 전달 가능함
    * `SIG_IGN`, `SIG_DFL`
* `void (*...)(int)` : 반환값 타입 $\rightarrow$ 함수 포인터

새로운 핸들러를 등록하고 이전 핸들러 주소를 반환하는 함수
특정 구간에만 새로운 핸들러를 사용하고, 원래대로 되돌려야할 때 이전 핸들러 포인터를 사용한다.

* 문제점 : 시그널의 현재 disposition을 변경하지 않고는 현재 설정 상태를 알 수 없음
    
    * signal() 함수는 새로운 핸들러 함수를 인자로 넣어줘야만 이전 핸들러 주소를 리턴해줌
    * Solution: `sigaction()` 사용

### Unreliable Signal

* 초기 UNIX 시스템 시그널의 문제점

    1. 시그널 유실 가능성 : 시그널이 발생했는데 프로세스가 모르고 놓침
    2. 프로세스 제어력 부족

        * 핸들러가 매번 리셋됨
        * 시그널 차단 불가능

* 이상적인 시그널 처리

    * 시그널을 잠시 블락해뒀다가 받을 준비가 되면 다시 알림 받기

### Interrupted System Call
만약 느린 시스템 콜 수행 중 시그널에 의해 시스템 콜이 중단된다면 시그널 핸들링이 끝난 후 중단된 시스템 콜을 마저 실행하는가?
(느린 시스템 콜: `wait()`, `pause()`)

* 초기 UNIX: No. `-1` 반환
* 현대 UNIX: `SA_RESTART`

### Reliable Signal

1. Signal Generation

    * 이벤트 발생 시 시그널이 생성된다.
    * 커널은 프로세스 테이블 내부의 플래그를 설정하여 기록한다.
2. Signal Delivery

    * 시그널에 따른 액션이 발생한 순간을 전달(delivered)되었다고 한다.
3. Pending Signal

    * 시그널이 생성된 후 전달되기 까지의 시간
    * 이 시간 동안 시그널을 보류(Pending) 상태라고 한다.
4. Signal Blocking

    * 프로세스는 시그널을 차단(Block)할 수 있는 옵션을 가진다.
    * 차단된 시그널이 프로세스를 위해 생성되었고 해당 시그널에 대한 조치가 기본 동작이거나 시그널 포착인 경우 전달이 보류된 채 대기된다.

#### Signal Blocking
프로세스가 특정 시그널을 블락한 상태에서 해당 시그널이 발생했을 때, disposition이 default거나 catch라면 시그널은 pending 상태로 대기한다.

이렇게 보류된 시그널은 프로세스가 차단을 해제하거나 disposition을 ignore로 변경할 때 까지 계속 보류 상태로 남아있다.

* 보류 중인 시그널 확인: `sigpending()`

**(주의) 만약 차단된 시그널이 중복 발생한다면**

* POSIX.1 표준: Queuing
* 대부분의 UNIX 시스템: 실시간 확장 기능을 지원하지 않는 한 큐잉 X, 한 번만 전달

그렇다면, 여러 종류의 시그널이 동시에 대기할 때 어떤 시그널 먼저 전달되는가?
POSIX.1 표준은 전달 순서를 명시하지 않는다. 시스템 구현에 따라 달라진다.

> **Signal Mask**
모든 프로세스는 현재 전달이 차단된 시그널들의 집합을 나타내는 시그널 마스크를 가진다.
**개념적인 이해: 시그널 종류별로 1비트씩 배정된 비트맵 구조**
비트 1 $\rightarrow$ 해당 시그널 차단됨

### Signal Sets (`sigset_t`)
여러 시그널들을 하나의 그룹으로 묶어서 표현하기 위한 데이터타입

```c
#include <signal.h>

int sigemptyset(sigset_t *set); // 모든 시그널 제외
int sigfillset(sigset_t *set); // 모든 시그널 포함
int sigaddset(sigset_t *set, int signo); // signo 시그널 추가
int sigdelset(sigset_t *set, int signo); // signo 시그널 제거
int sigismember(const sigset_t *set, int signo); // signo 포함여부 판별
```

모든 응용 프로그램은 signal set을 사용하기 전에 sigemptyset 혹은 sigfillset을 호출하여 초기화 후 사용해야한다.
