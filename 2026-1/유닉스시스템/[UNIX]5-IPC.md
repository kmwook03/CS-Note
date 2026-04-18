## IPC

### IPC: Shared Memory

여러 프로세스가 동일한 물리 메모리를 매핑해서 사용하는 공간

- 특징

    - 커널 개입 최소 $\rightarrow$ 매우 빠름
    - 데이터 복사 없음
    - 동기화 문제 발생 가능

- POSIX Shared Memory

    - `shm_open()`
    - `mmap()`
    - `shm_unlink()`

### IPC: Semaphore

여러 프로세스/스레드가 공유 자원을 안전하게 사용하도록 제어하는 **동기화** 도구

즉, 순서를 제어하여 race condition을 방지하기 위함

- Counting Semaphore (0 ~ N)
- Binary Semaphore (0 or 1)

**Key idea** : 사용 가능한 자원의 개수를 관리하는 변수(`sem`)로 생각

**기본 연산**

- P 연산 (wait)

    - `sem_wait(&sem);` : 자원 요청
    - if (sem > 0) then sem--
    - else if (sem == 0) then wait(block)

- V 연산 (signal)

    - `sem_post(&sem);` : 자원 반납
    - sem++ 후 대기 중인 스레드를 하나 깨움

- 동작 예시 (`sem = 2`)

    - Thread A $\rightarrow$ sem_wait $\rightarrow$ sem-- (`sem = 1`)
    - Thread B $\rightarrow$ sem_wait $\rightarrow$ sem-- (`sem = 0`)
    - Thread C $\rightarrow$ sem_wait $\rightarrow$ sem == 0 $\rightarrow$ `block`
    - Thread A $\rightarrow$ sem_post $\rightarrow$ sem++ (`sem = 1`)
    - Thread C wakeup $\rightarrow$ sem_wait $\rightarrow$ sem-- (`sem = 0`)
    - ...

### POSIX Semaphore

**Unnamed semaphore** : pthread + sem_t

- sem_wait() $\rightarrow$ 자원 없으면 BLOCK
- sem_post() $\rightarrow$ 자원 증가 + 다른 스레드 깨움

**IPC using Semaphore** : shared memory + sem_init

- pshared = 1
- `sem_init(&sem, 1, 1)`

    - 두 번째 parameter: 1 -> 프로세스 간 공유
    - 세 번째 parameter: 초기값
- 반드시 **공유 메모리(mmap)** 에 세마포어가 있어야 함

**Named semaphore** : 파일 이름으로 공유

- `sem_t *sem = sem_open("/mysem", O_CREAT, 0644, 1)`
- `sem_unlink("/mysem")`

**핵심 차이점**

- unnamed semaphore: 세마포어 객체가 메모리 상의 변수임
- named semaphore: 세마포어 객체가 가상 파일 시스템 상의 파일임
