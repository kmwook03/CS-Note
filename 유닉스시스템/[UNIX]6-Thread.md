## Thread : Light Weight Process
CPU 기본 이용 단위로, 프로그램 내에 선언된 function이다.
여러 개의 스레드가 하나의 프로세스를 공유하며 프로세스의 Context switching 오버헤드를 줄일 수 있다.

* Thread 구성 요소

    * Thread ID
    * Register Set (PC, SP, ...)
    * Stack
    * Scheduling priority and policy
    * Signal Mask
    * **Thread-specific Data**

스레드는 프로그램이 동시에 여러 작업을 할 수 있도록 하기 위한 메커니즘이다. Linux 커널은 스레드들을 비동기적으로 스케줄링한다.
개념적으로 스레드는 프로세스 내에 존재하며, 프로세스 실행의 finer-grained unit이다.
(process는 coarse-grained unit of execution임)

### 동작 구조
연관된 쓰레드들이 메모리와 파일을 공유 -> **Reduced State를 갖는 LWP**
각 스레드는 한 프로세스에만 속하며 스레드도 자식 스레드를 가질 수 있다.
스레드 기반 시스템에서 스케줄링 단위는 스레드다.

### 생성 과정
프로그램 실행 $\rightarrow$ Linux 커널이 새 프로세스 생성 $\rightarrow$ 그 프로세스가 프로그램을 순차적으로 실행시킬 스레드 생성 $\rightarrow$ 그 스레드가 다른 스레드 생성 $\rightarrow$ 모든 스레드가 같은 프로세스 내에서 같은 프로그램의 다른 파트를 실행시킴

스레드는 서로 같은 프로세스의 주소 공간을 공유하기 때문에 스레드를 생성할 때 부모로부터 복사되는 것은 없다.

자식 프로세스는 값을 바꾸거나 파일 디스크립터를 닫아도 부모 프로세스 실행에 영향을 주지 않지만, 스레드는 한 스레드의 값 조작이 다른 스레드 실행에 영향을 준다.

단, 스레드들은 단 하나의 프로세스에만 속할 수 있기 때문에 새로운 프로세스가 생성될 때 fork()를 호출한 스레드를 제외한 다른 스레드들은 복사하지 않는다.
특히 exec 계열 시스템 콜이 호출되면 기존에 그 프로세스에서 실행 중이던 모든 스레드를 종료한다.

### 동기화 문제
스레드들은 동일한 주소 공간을 공유 $\rightarrow$ 전역 변수 공유 $\rightarrow$ 한 스레드의 전역 변수 수정이 다른 스레드의 실행에도 영향을 줌
$\therefore$ **동기화(Synchronization)** 필요

**Consistency:** 여러 스레드가 공유 데이터에 접근할 때 데이터가 항상 올바른 상태로 유지되는 것

| Thread 고유 자원 | 프로세스 공유 자원 |
|-|-|
| Thread ID | Code Segment |
| Register Set | Data Segment |
| Stack| Heap Segment |
| Scheduling priority and policy | FD Table (including socket) |
| Signal mask | Process ID |
| Thread-specific data ||

```
[example]
Thread A: read counter (0)
Thread B: read counter (0)
Thread A: write 1
Thread B: write 1

Expected: counter == 2
Actually: counter == 1
```

### pThread

`헤더파일`
```c
#include <pthread.h>
```

`int pthread_equal(pthread_t tid1, pthread_t tid2)`
두 스레드의 TID를 비교한다.
* return: nonzero(equal) / 0(not equal)

`pthread_t pthread_self(void)`
자신의 TID를 반환한다.
* return: 호출한 스레드의 TID

> #### pthread ID와 Linux TID 차이

| | pthread | Linux |
|-|-|-|
| 조회 | `pthread_self()` | `gettid()` |
| 관리 | 사용자 공간 | 커널 |
| 역할 | POSIX 스레드 라이브러리 식별자 | 커널이 관리하는 실제 ID |

#### 생성
```c
int pthread_create( pthread_t *restrict tidp,
                    const pthread_attr_t *restrict attr,
                    void *(*start_rtn)(void *),
                    void *restrict arg)
```

* `start_rtn` : thread 진입점 주소
    
    * `void *(*start_rtn)(void *)`
        
        * void 포인터가 리턴형이고 void 포인터 타입의 매개변수를 받는 함수
        * 즉, 새롭게 생성된 스레드가 메모리 상에서 실행을 시작할 진입점 함수를 인자로 전달해줘야한다.
    * `void *restrict arg` : start_rtn의 매개변수

pthread_create 내부에서 `start_rtn(arg)` 형태의 함수를 호출하여 스레드에 인자를 전달한다.

```
[ Main Thread ]
       │
       ▼ pthread_create(..., start_rtn, arg);
       │                       │        │
       │  (실행할 함수 주소 전달) │        │ (넘겨줄 데이터의 주소 전달)
       │                       ▼        ▼
       │             ==============================
       │             [ OS Kernel & pthread Library ]
       │             - 새로운 Worker Thread Stack 할당
       │             - arg 주소값을 새 스레드의 인자 레지스터에 배치
       │             ==============================
       │                                     │
       └─────────────────────────────────────┼───► [ New Worker Thread ]
                                             │         │
                                             │         ▼ CPU 제어권 획득
                                             └─► start_rtn(arg) 런타임 호출!
                                                       │
                                                       ▼ Inside Function
                                                 *(Type *)arg; (역참조하여 복원)
```

#### 종료
프로세스 내의 스레드 중 하나라도 `exit()`, `_Exit()`, `_exit()` 시스템 콜을 호출하거나 특정 스레드에 `SIGKIL`, `SIGSEGV` 등의 시그널이 전달되면 프로세스 전체가 종료된다.

프로세스 전체를 종료하지 않고 단일 스레드만 종료하기 위해서는 다음 방법을 사용할 수 있다.

1. `start_rtn`의 반환(return)

    * 이 때 반환된 값은 `pthread_join()`을 호출한 스레드로 전달됨
2. `pthread_exit()` 호출 (자발적 종료)

    * 프로세스는 유지한 채 해당 스레드만 즉각 종료
    * 이 경우에도 `pthread_join()`을 호출한 스레드로 결과가 전달됨
3. Thread Cancellation (외부 스레드에 의한 강제 종료)

    * `pthread_cancle()` 등으로 강제 종료

```c
void pthread_exit(void *rval_ptr);
```

* `rval_ptr` : Return value pointer

    * 이 포인터는 `pthread_join()`을 호출한 스레드에서 사용 가능함

> **주의**
스레드 내부의 지역 변수들은 스레드 스택에 위치한다. 이를 pthread_exit() 등으로 반환하면 스레드가 종료되면서 주소가 깨지게 된다. 따라서 실제 프로그램에서 반환 값은 동적 메모리 주소에 저장하는 것이 안전하다.

```c
int pthread_join(pthread_t thread, void **rval_ptr);
```
특정 스레드가 종료될 때 까지 기다리고, 종료되면 반환값을 받는다.
(반환값으로는 pthread_exit()의 인자 또는 그 스레드의 리턴 값을 받음)
또한, 종료된 스레드의 리소스를 해제하는 기능도 수행한다.

`잘못된 pthread_exit() 예제`

```c
struct foo { int a, b, c, d; };

void *thr_fn1(void *arg) {
    struct foo foo = {1, 2, 3, 4}; // 지역 변수 -> stack에 저장

    printfoo("thread1:\n", &foo);
    pthread_exit((void *)&foo); // 종료하면서 stack 파괴
}

int main() {
    int err;
    pthread_t tid1, tid2;
    struct foo *fp;
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    err = pthread_join(tid1, (void *)&fp);
    printfoo("parent:\n", fp); // fp는 파괴된 주소를 가리킴: dangling pointer
}
```

#### Joinable vs. Detached
기본적으로 스레드는 joinable 하다.
즉, 다른 스레드가 pthread_join()할 수 있게 하기 위해서 스레드 종료 후 리소스가 바로 해제되지 않는다. 따라서 반드시 pthread_join()으로 해제해줘야한다.

```c
int pthread_detach(pthread_t thread);
```
를 통해서 스레드를 detached 상태로 변경할 수 있다. detached 상태의 스레드는 종료되는 즉시 커널이 개입하여 자동으로 메모리 자원을 정리한다. 

| | pthread_join | pthread_detach |
|-|-|-|
| 스레드 종료 대기 | O | X |
| 반환값 받기 | O | X |
| 리소스 해제 | join 시 | 자동 |
| 사용 목적 | 결과값이 필요할 때 | 백그라운드 작업 |

#### Zombie
joinable 스레드가 종료됐지만, pthread_join()이 호출되지 않은 상태
좀비 스레드가 발생되어도 메인 프로세스가 종료되면 OS에 의해 모든 리소스가 정리된다.

그러나 빨리 종료가 안되고 오래 실행되는 프로그램이라면?
$\rightarrow$ thread resource leak 발생!

* 해결방법

    1. pthread_join(thread, NULL)
    2. pthread_detach(thread) $\rightarrow$ 종료 시 자동 정리

#### Canclellation
스레드가 다른 스레드를 강제로 종료 요청하는 기능

```c
int pthread_calcel(pthread_t thread);
```
특정 스레드에 취소 요청(cancel request)을 보낸다.

* 취소 요청: 즉시 종료 X, 취소 가능한 지점(Cancellation Point)에서 종료해줘.

    * 대표적인 cancellation point

        * sleep()
        * read()
        * write()
        * pthread_join()
        * pthread_cond_wait()

```c
void pthread_testcancel(void);
```
현재 스레드에 취소 요청이 있는지 확인하고, 있으면 그 자리에서 스레드를 종료한다.
Cancellation Point를 직접 만들어줌

* 취소 요청

    * 있다 $\rightarrow$ 즉시 종료
    * 없다 $\rightarrow$ 계속 실행

> **스레드 취소 방식**
1. Deferred Cancellation (Default)

    * 취소 요청 $\rightarrow$ cancellation point 도달 $\rightarrow$ 종료
    * 안전한 리소스 정리 가능
2. Asynchronous Cancellation

    * 취소 요청 $\rightarrow$ 즉시 종료
    * `pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHROUNOUS, NULL);`
    * mutex lock 상태에서 종료 가능함 $\rightarrow$ Deadlock 발생
    * 메모리 누수 문제 있음
    * 따라서 잘 안씀

> **Cancellation 상태 제어**
* PTHREAD_CANCEL_ENABLE: 취소 가능
* PTHREAD_CANCEL_DISABLE: 취소 불가 $\rightarrow$ 요청이 있어도 무시

Critical Section 보호를 위해 취소를 잠시 막을 수단이 필요하기 때문에 사용

```c
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);

// critical section
update_shared_data();

pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
```

| 함수 | 역할 |
|-|-|
| pthread_cancel() | 취소 요청 |
| pthread_setcancelstate() | 취소 가능 여부 설정 |
| pthread_testcancel() | 취소 요청이 있으면 즉시 종료 |
