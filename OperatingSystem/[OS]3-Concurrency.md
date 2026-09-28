## Thread & Concurrency

### 1. Thread의 등장 배경

* 프로세스의 한계
    
    * 단일 프로세스는 Multi-cores의 이점을 누릴 수 없다.
    * 협력하는 여러 프로세스를 작성하는 것은 번거롭다.
    * 새로운 프로세스 생성 비용이 비싸다.
    * 프로세스 간 통신(IPC) 및 Context Switch 오버헤드가 크다.

**Solution: Thread(스레드)**

### 2. 기술 분석: Thread

**Thread란?**
    
* 단일 실행 프로세스를 위한 새로운 추상화 모델
* 단일 프로세스 내에서 독립적인 여러 실행 흐름을 생성할 수 있게 하여 동시성 문제를 해결

병렬 처리를 통해 Throughput(처리량)과 Responsiveness(응답성)를 높이고, 멀티코어 아키텍처를 온전히 활용하기 위해 필요하다.

주로 웹 서버처럼 동시 다발적인 이벤트를 처리해야 하거나, 대규모 연산을 병렬로 분할 처리해야 할 때 사용한다.

**동작 원리**
    
* 각 Thread는 자신만의 Thread ID, PC(Program Counter), SP(Stack Pointer)를 포함한 Register 상태, 그리고 Stack을 별도로 가진다.
* 여러 스레드는 동일한 Address Space를 공유한다. 따라서 Code, Data, Heap Segment는 공유되지만, 함수의 지역 변수나 반환 값 등이 저장되는 **Stack Segment는 thread마다 독립적으로 할당** 된다.
* Thread 간 Context Switch가 일어날 때, 커널은 Address Space를 그대로 유지한 채 TCB(Thread Control Block)에 기존 스레드의 레지스터 상태를 저장하고, 새 스레드의 상태를 복원한다.

```text
[Multi-threaded Address Space]
High Address
+---------------------------+
|      Stack (Thread 2)     | ↓ (Grows downward)
|        (free space)       |
|      Stack (Thread 1)     | ↓ (Grows downward)
+---------------------------+
|        (free space)       |
+---------------------------+
|           Heap            | ↑ (Grows upward)
+---------------------------+
|           Data            | (Global variables, Shared)
+---------------------------+
|           Code            | (Instructions, Shared)
+---------------------------+
Low Address
```

### 3. Processes vs. Threads 비교

| 비교 항목 | Process(프로세스) | Thread(스레드) |
| :--- | :--- | :--- |
| **바인딩** | 실행의 컨테이너 (정적 엔티티) | 단일 프로세스에 종속됨 (동적 엔티티) |
| **자원 공유** | 독립적인 주소 공간 사용, 데이터 공유가 비쌈 | 주소 공간을 공유하여 데이터 공유가 저렴함 |
| **스케줄링 단위** | (과거 운영체제의) 스케줄링 기본 단위 | 현대 운영체제 스케줄링의 기본 단위 |
| **컨텍스트 스위치** | 주소 공간 변경을 동반하므로 오버헤드 큼 | 주소 공간을 유지하므로 오버헤드 작음 |

*참고: 프로세스는 PID, 파일 디스크립터 등을 담는 컨테이너 역할을 하며, 스레드는 그 안에서 실제로 실행되는 흐름이다.*

### 4. 스레드 구현 방식: Kernel-level vs User-level

| 특성 | Kernel-level Threads(커널 수준 스레드) | User-level Threads(사용자 수준 스레드) |
| :--- | :--- | :--- |
| **관리 주체** | OS 커널이 스레드와 프로세스 모두 관리 | 런타임 시스템(스레드 라이브러리)이 관리 |
| **운영체제 인지**| OS가 각 스레드의 존재를 인지함 | OS는 프로세스만 인지하며, 스레드는 보이지 않음 |
| **연산 방식** | 스레드 생성/관리가 System Call(시스템 콜)로 이뤄짐| Procedure Call(함수 호출)로 처리되어 오버헤드가 없음 |
| **속도** | 모드 전환이 필요하여 상대적으로 무겁고 느림 | 커널 개입이 없어 커널 스레드보다 10~100배 빠름 |
| **블로킹 이슈** | 한 스레드가 I/O로 블로킹되어도 다른 스레드 실행 가능| 한 스레드가 블로킹 System Call(시스템 콜)을 호출하면 프로세스 전체가 블로킹됨 |
| **멀티코어 활용**| 멀티코어 CPU의 이점을 온전히 활용 가능 | 커널이 스레드를 모르므로 멀티코어 활용 불가 |

---

## Process Synchronization

### 1. The Problem of Concurrency
동일한 변수(예: `counter = counter + 1`)를 갱신하는 두 스레드를 실행할 때, 우리는 `counter`가 2 증가하기를 기대한다.

하지만 실행 결과는 매번 다르며 틀린 값을 반환하는 Non-deterministic(비결정적)인 양상을 띤다.

이는 `counter + 1` 연산이 고급 언어에서는 한 줄이지만, 어셈블리어 수준에서는 

`1) 메모리에서 레지스터로 로드(mov)`<br>`2) 레지스터 값 1 증가(add)`<br>`3) 레지스터 값을 메모리에 저장(mov)`

이라는 세 개의 명령어로 나뉘기 때문이다.

이 명령어들 사이 임의의 시점에 Timer Interrupt로 인해 Context Switch가 발생하면, 데이터 무결성이 깨지게 된다. 

### 2. 기술 분석: Critical Section & Mutual Exclusion

**Critical Section**

* 공유 자원(변수나 자료구조)에 접근하는 코드 조각.

**Mutual Exclusion**
* 한 스레드가 임계 구역을 실행 중일 때 다른 스레드의 진입을 막는 보장 속성입니다.

위 기술들로 여러 스레드가 동시에 공유 데이터를 조작할 때 실행 타이밍에 따라 결과가 달라지는 Race Condition을 방지한다.

**Goal: Atomicity for Critical Section**


**동작 원리** 

* Lock(락) 변수 도입
* 진입 전 락을 획득(`lock()`)하고 빠져나올 때 락을 반환(`unlock()`)하도록 코드 주변을 감싼다.
 
```
1. 스레드가 `lock(&mutex)`를 호출하여 락 획득을 시도
2. 락이 Available이면 획득, Critical Section에 진입
3. 다른 스레드들은 첫 번째 스레드가 락을 쥐고 있는 동안 진입이 차단됨
4. 작업을 마친 스레드가 `unlock(&mutex)`을 호출
5. 락은 다시 Available 상태가 됨
```

---

## Implementing Locks

우수한 Lock(락)은 다음 세 가지 요구사항을 충족해야 합니다.
1. **Correctness(정확성):** Mutual exclusion(상호 배제), Progress(진행, 데드락 방지), Bounded waiting(제한된 대기, 기아 상태 방지).
2. **Fairness(공정성):** 모든 스레드가 락을 획득할 동등한 기회를 가져야 함.
3. **Performance(성능):** 경합이 없거나 많을 때의 시간 오버헤드가 적어야 함.

### 1. Controlling Interrupts
임계 구역 진입 전 하드웨어 인터럽트를 비활성화(`DisableInterrupts()`)하여 타이머 인터럽트에 의한 Context Switch(문맥 교환)를 원천 차단하는 가장 단순한 방법이다.

**한계**

* 악의적이거나 버그가 있는 프로그램이 CPU를 독점할 수 있음
* Multi-processors 환경에서는 작동하지 않음
* 현대 CPU에서 인터럽트 제어 명령어는 속도가 느림

### 2. Software Approach: Peterson’s Solution
하드웨어의 도움 없이 LOAD/STORE의 원자성만을 가정하고 구현한 소프트웨어 솔루션.

두 프로세스(또는 스레드) 간의 동기화만 지원한다.

```c
// Peterson's Solution
int flag; // 프로세스의 임계 구역 진입 의사를 나타냄
int turn;    // 락을 획득할 차례를 나타냄 (tie-breaking 용도)

void lock() {
    int other = 1 - self;
    flag[self] = 1;      // 1. 내 진입 의사를 밝힘
    turn = other;        // 2. 다른 프로세스에게 차례를 양보함
    // 3. 상대방이 진입 의사가 있고, 상대방 차례라면 Spin-wait(회전 대기)
    while ((flag[other] == 1) && (turn == other)); 
}
```
*의미:* 두 프로세스가 동시에 진입하려 해도 `turn` 변수는 하나만 가질 수 있으므로 Mutual Exclusion(상호 배제)을 보장하며, 락을 해제할 때 `flag`를 내리므로 Progress(진행)도 보장한다.

### 3. 기술 분석: Hardware Atomic Instructions
소프트웨어 방식은 한계가 명확하다.

$\Rightarrow$ 현대 OS는 **하드웨어 수준에서 지원하는 원자적 명령어** 를 통해 Lock 구현

메모리 읽기(Test)와 쓰기(Set)를 단일 하드웨어 명령어로 묶어 원자적으로 수행하는 CPU 명령어 세트를 제공한다.

단순 변수 갱신(소프트웨어 락) 시 `flag` 확인과 갱신 사이에 발생하는 Context Switch로 인해 Mutual Exclusion이 깨지는 문제를 하드웨어 레벨에서 해결한다.

**순수 소프트웨어 기반 락의 한계**

* 복잡하고 느림
* 멀티프로세서 확장에 취약함
* 변수를 읽고 갱신하는 과정 자체가 분리되어 있어 본질적인 Race Condition의 원인이 됨

**핵심 메커니즘**
**1. Test-And-Set**
`TestAndSet(ptr, new)`는 `ptr`이 가리키는 기존 값을 반환함과 동시에 그 위치를 `new` 값으로 업데이트한다.
이 과정이 끊어지지 않고 원자적으로 수행된다.

**2. Compare-And-Swap**
메모리 값이 예상(expected) 값과 일치할 때만 새로운 값으로 원자적 갱신을 수행한다.

**3. Load-Linked & Store-Conditional**
`LoadLinked`로 값을 읽고, 이후 다른 스레드의 개입이 없었을 경우에만 `StoreConditional`이 갱신에 성공(1 반환)한다.

**적용 형태 (Spin Lock)**
이 명령어들을 `while` 루프의 조건문에 넣어, 락 획득에 성공할 때까지 무한정 루프를 도는 Spin Lock(스핀 락)을 구현할 수 있다.

*예제: Ticket Lock (티켓 락)*
`FetchAndAdd` 명령어를 이용해 구현하며, 스레드가 큐 번호표(ticket)를 뽑고 자신의 차례(turn)가 올 때까지 대기합니다. 스핀 락에 Fairness(공정성)를 보장하여 기아 상태를 해결합니다.

### H2: 4. Spin-waiting(스핀 대기)의 비효율성 극복
Spin Lock(스핀 락)은 락을 기다리는 동안 타임 슬라이스 전체를 소모하여 CPU를 낭비하는 치명적 단점(Spin-waiting)이 있습니다.

1. **Just Yield (양보하기):** 스핀 대기 중일 때 `yield()` 시스템 콜을 호출해 강제로 CPU를 반환하고 Running(실행) 상태에서 Ready(준비) 상태로 전환합니다. 하지만 컨텍스트 스위치 오버헤드가 누적되며 기아 상태를 해결하지 못합니다.
2. **Using Queues (큐와 수면):** OS 지원을 받아 명시적인 큐를 유지합니다. 락 획득 실패 시 큐에 스레드 ID를 넣고 `park()`를 호출해 Sleep(수면) 상태로 만듭니다. 락 반환 시 `unpark(ID)`를 통해 대기 중인 특정 스레드만 깨워 CPU 낭비를 원천 차단합니다. 이 과정에서 큐 상태 자체를 보호하기 위해 또 다른 하드웨어 락(`guard`)이 필요합니다.

---

## H1: Advanced Synchronization Mechanisms (고급 동기화 메커니즘)

단순한 Lock(락)만으로는 해결할 수 없는 복잡한 흐름 제어를 위해 고안된 구조입니다.

### H2: 1. 기술 분석: Condition Variables (조건 변수)

- **what?**
  - **이것이 무엇인가:** 스레드가 원하는 상태(Condition)가 충족될 때까지 자신을 스스로 큐에 넣고 대기(Sleep)할 수 있도록 돕는 동기화 기법입니다.
  - **어떤 문제를 해결하는가:** 부모 스레드가 자식 스레드의 종료를 기다리는(`join()`) 등 실행 순서(Ordering)가 중요한 상황을 해결합니다.

- **why?**
  - **왜 이 기술이 필요한가:** 상태 변화를 무한정 Spin-waiting(회전 대기)하며 확인하는 것은 비효율적이므로, 상태가 바뀔 때까지 잠들게 하고 상태가 바뀌면 깨우는 명시적 메커니즘이 필요합니다.

- **how?**
  - **동작 원리:** 대기 중인 큐(Explicit queue)를 관리합니다.
  - **데이터 흐름 및 처리 과정:** 
    1. 조건이 거짓이면 스레드는 락을 해제하고 `wait()`을 호출하여 수면 상태에 들어갑니다.
    2. 다른 스레드(예: 자식 스레드)가 작업을 완료하여 상태 변수를 변경한 후 `signal()`(또는 `post()`)을 호출합니다.
    3. 수면 중이던 스레드가 깨어나 다시 락을 획득한 후 작업을 이어갑니다.

### H2: 2. 기술 분석: Semaphore (세마포어)

- **what?**
  - **이것이 무엇인가:** 초기값을 가진 정수형 변수로, `wait()`와 `post()`라는 오직 두 개의 원자적 연산을 통해서만 조작 가능한 추상적 자료구조입니다. (Edsger Dijkstra 고안)

- **why?**
  - **왜 이 기술이 등장했는가:** Lock(락)과 Condition Variable(조건 변수)의 기능을 하나의 추상화된 정수 변수로 통합하여 제공하기 위해 등장했습니다.
  - **어떤 상황에 사용하는가:** 임계 구역 상호 배제(Binary Semaphore, 초기값 1)나 유한한 개수의 자원 관리 및 조건 대기(Counting Semaphore, 초기값 N)에 모두 사용됩니다.

- **how?**
  - **동작 원리:** 내부적으로 큐를 가집니다.
  - **데이터 흐름 및 처리 과정:**
    - `sem_wait()`: 정수값을 1 감소시킵니다. 감소 후 값이 음수(`S < 0`)가 되면, 호출한 스레드는 큐에 들어가 수면(Sleep) 상태가 됩니다. (음수의 절댓값 = 대기 중인 스레드 수).
    - `sem_post()`: 정수값을 1 증가시킵니다. 하나 이상의 스레드가 대기 중이라면 큐에서 하나를 꺼내 깨웁니다(Wake).

### H2: 3. Classical Synchronization Problems (고전적 동기화 문제)

이러한 세마포어를 활용하여 해결하는 대표적 문제들입니다.

#### Bounded-Buffer Problem (생산자-소비자 문제)
- **개념:** 한정된 버퍼(N개)를 두고 생산자(Producer)는 데이터를 넣고(`put()`), 소비자(Consumer)는 데이터를 꺼냅니다(`get()`). 웹 서버의 요청 큐 처리가 대표적 예시입니다.
- **해결 로직 (3개의 세마포어 사용):**
  1. `empty (초기값 N)`: 생산자는 빈 공간이 있는지 `wait(&empty)`로 확인하고, 소비자는 소비 후 `post(&empty)`로 빈 공간을 늘립니다.
  2. `full (초기값 0)`: 소비자는 채워진 공간이 있는지 `wait(&full)`로 대기하고, 생산자는 생산 후 `post(&full)`로 채워진 개수를 늘립니다.
  3. `mutex (초기값 1)`: 여러 생산자와 소비자가 동시에 버퍼 배열 인덱스에 접근하지 못하도록, 상호 배제용으로 `put()` 및 `get()`을 감쌉니다.

```c
// 생산자 로직 구조
void *producer(void *arg) {
    for (i = 0; i < loops; i++) {
        sem_wait(&empty); // 빈 버퍼가 있을 때까지 대기
        sem_wait(&mutex); // 임계 구역 진입
        put(i);           // 공유 버퍼에 데이터 삽입
        sem_post(&mutex); // 임계 구역 탈출
        sem_post(&full);  // '채워짐' 상태 증가시킴 -> 소비자 깨움
    }
}
```

#### Reader-Writer Problem (독자-작성자 문제)
- **개념:** 자료구조에서 `Lookup`(단순 읽기)은 여러 스레드가 동시에 진행해도 무방하지만, `Insert`(쓰기)는 오직 단 하나의 스레드만 락을 소유해야 하는 상황의 락을 구현합니다.

### H2: 4. Semaphore Problems (세마포어 문제점)
- **Deadlock(교착 상태):** 서로가 서로의 자원을 기다리며, 대기 중인 프로세스 중 하나만이 이 이벤트를 발생시킬 수 있어 영원히 블로킹되는 현상입니다.
- **Priority Inversion(우선순위 역전):** 우선순위가 높은 프로세스가 필요한 락을 우선순위가 낮은 프로세스가 쥐고 있어 스케줄링이 꼬이는 문제입니다.
  - *해결책:* **Priority Inheritance Protocol(우선순위 상속 프로토콜)** - 높은 우선순위 프로세스가 락을 요청하면, 락을 쥐고 있는 낮은 우선순위 프로세스의 우선순위를 일시적으로 높여(상속) 빠르게 작업을 끝내고 락을 반환하도록 유도합니다.

---

## 전반적 흐름 요약 (Overall Summary)
운영체제에서 단일 프로세스의 연산 병목을 극복하고자 멀티코어 환경에 적합한 Thread(스레드)가 등장했으나, 공유 주소 공간으로 인해 Race Condition(경쟁 상태)이라는 치명적인 Concurrency(동시성) 문제가 발생했습니다. 이를 제어하기 위해 코드 실행의 원자성을 보장하는 Critical Section(임계 구역)과 상호 배제(Mutual Exclusion) 개념이 도입되었습니다. 초기 인터럽트 제어나 소프트웨어 알고리즘의 한계를 극복하고자 하드웨어 차원의 원자적 명령어(Test-And-Set 등)가 등장하여 Lock(락)을 구현할 수 있게 되었습니다. 나아가, 스핀 대기로 인한 CPU 낭비를 막고 실행 순서를 정교하게 제어하기 위해 큐를 활용한 Condition Variables(조건 변수)와 이를 일반화한 Semaphore(세마포어) 메커니즘이 발전하여, Bounded-Buffer와 같은 복잡한 고전적 동기화 문제들을 현대 OS(Linux 등)에서 안전하게 처리할 수 있게 되었습니다.