# 운영체제 개요

우리가 컴퓨터에서 프로그램을 실행시키면 일반적으로 다음(1~4) 싸이클을 반복한다.

0. Load: CPU는 명령어를 오직 메모리에서만 가져올 수 있기 때문에 실행 될 프로그램은 반드시 메모리에 올라가있어야 한다.
1. Fetch: 프로세서는 메모리로부터 명령어를 가져온다.
2. Decode: 가져온 명령어를 해석한다.
3. Execute: 명령어를 실행한다.
4. Store(필요할 경우): 명령 수행 결과 저장이 필요할 경우에는 메모리 또는 레지스터에 저장한다.

이는 폰 노이만 모델의 기본이다.

### 운영체제는 
- **여러 개의 프로그램이 동시에 쉽게 실행될 수 있도록** 만들고
- 그 프로그램들이 **메모리를 공유하고** 
- **장치에 접근**할 수 있도록 해야할 책임을 가진다.

즉, 운영체제는 시스템이 **사용하기 쉬운 방식**으로 **올바르고 효율적으로** 작동하는지 확인하는 역할을 담당한다.

> **키 아이디어**
> - Virtualization(가상화): 물리적 자원들을 관리하고 사용자 프로그램들에 제공하는 방법
> - Consistency(일관성): 다수의 프로그램들이 동시에 실행될 때 일관성을 보장할 수 있는 방법
> - Persistence(영속성): 데이터를 안정성을 보장하는 방법

### 가상화 (Virtualization)

운영체제는 물리적 자원을 가상의 형태로 변환한다. 이를 **가상화**라고 한다.
가상화된 형태의 자원은 더 범용적이고 강력하며 사용하기 쉽다.
운영체제는 CPU, 메모리, 디스크 같은 자원을 관리해야 한다.
그 말은 즉, 많인 프로그램들이 위 자원을 공유해야한다는 말이다.

**CPU 가상화**
시스템은 아주 많은 수의 가상 CPU를 가진다.
하나의 CPU도 무한한 개수의 CPU 처럼 보이게 만들고, 다수의 프로그램들이 동시에 실행되는 것 처럼 보이게 만든다.

**메모리 가상화**
물리적인 메모리는 바이트의 배열이다. 프로그램은 자신의 모든 자료 구조들을 메모리에 저장한다.
많은 프로그램이 동시에 실행되기 위해 운영체제는 각 프로세스들에게 마치 자신이 주소 공간을 독점하는 것 같은 환상(illusion)을 보여줘야 한다.
각 프로세스는 자신의 가상 주소 공간(virtual address space)에 접근하기 때문에 프로세스 내에서의 메모리 참조가 다른 프로세스에 영향을 주지 않는다.

### 일관성 (Consistency)

**병행성(Concurrency) 문제**
운영체제는 많은 것을 동시에 저글링 해야한다. 또한 현대의 멀티 스레드 프로그램(multi-threaded program) 또한 병행성 문제를 나타낸다.

> 병행성 문제 예시
```C
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"

volatile int counter = 0;
int loops;

void *worker(void *arg)
{
    int i;
    for (i = 0; i < loops; i++) { counter++; }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);

    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("Final value : %d\n", counter);
    return 0;
}
```
위 프로그램은 두 개의 스레드가 루프를 돌면서 전역 변수 counter를 하나씩 증가 시킨 후 최종 counter 값을 출력하는 프로그램이다.

```bash
kmwook@kmwookgram:~/OSTEP$ ./thread 1000
Initial value : 0
Final value : 2000
```
예상대로라면 위 결과 처럼 1000번의 루프를 두 프로세스가 돌았으니 최종 counter 값은 2000이 나와야 한다.

```bash
kmwook@kmwookgram:~/OSTEP$ ./thread 100000
Initial value : 0
Final value : 169011
```
그러나 100,000번의 루프를 돈 결과 예상 결과 200,000보다 작은 값이 출력 되었다.

**왜 그럴까?**
공유된 counter 변수를 증가시키기 위해 다음 세 명령어가 필요하다.

1. counter를 메모리에서 레지스터로 로드한다.
2. counter 값을 증가시킨다.
3. 증가된 counter 값을 메모리에 다시 저장한다.

하지만 이 명령어들은 원자적으로(atomically) 실행되지 않는다.
이 때 병행성 문제가 발생한다.

두 프로세스가 값이 0인 counter를 참조하였다면, 증가시킨 결과는 2가 아닌 1이 된다.

    counter: 0 ------------------------> counter(1) --> counter(1)
    t1 counter(0) 접근 -> counter++(1) -> 메모리에 씀
        t2 counter(0) 접근 -> counter++(1) -> 메모리에 씀

운영체제는 이런 병행성 문제를 제어하며 데이터의 일관성을 유지하여야 한다.

### 영속성 (Persistence)

시스템의 메인 메모리인 DRAM은 데이터를 휘발성으로 저장한다.
즉, 전원이 차단되면 저장된 데이터가 사라진다.

데이터를 영속적으로 저장하려면 이를 위한 하드웨어와 소프트웨어가 필요하다.

- Hardware: HDD, SSD와 같은 입출력 장치
- Software: File System

운영체제는 디스크에 파일을 쓰기 위해 새로운 데이터가 위치할 영역을 찾고 저장 장치에 I/O 요청을 발행한다.

파일 시스템은 쓰기 중 충돌을 Journaling 또는 copy-on-write 방식으로 처리한다.

### 운영체제 설계 목표

- 추상화 구축: 시스템을 편리하고 사용하기 쉽도록 만든다.
- 고성능 제공: 운영체제의 오버헤드를 최소화한다.
- 애플리케이션 보호: 애플리케이션이 다른 애플리케이션과 운영체제에 피해를 주지 않도록 격리한다.
- 높은 신뢰성: 운영체제가 멈추지 않고 실행될 것을 보장한다.
- 기타(에너지 효율성, 보안, 유동성 등)

Remzi Arpaci-Dusseau and Andrea C. Arpaci-Dusseau. (2023). _Operating System: Three Easy Pieces (version 1.10)_. Arpaci-Dusseau Books

