## Storage Media

### Goal of File System

1. 크고 복잡한 데이터를 저장하기 위한 효율적인 **자료구조(Data Structure)** 를 제공함
2. 빠른 탐색을 위한 **접근 방법(Access Method)** 을 제공함
3. **쿼리 프로세싱 방법(Query Processing Method)** 을 제공함
4. 견고한 **트랜잭션(Transaction) 관리** 를 제공함
5. **분산 환경(Distributed Environment)** 지원을 제공함 (DBMS)

### Memory Hierarchy

대용량 데이터를 메인 메모리에 모두 담을 수 없음
$\Rightarrow$ 접근 속도, 비용, 신뢰성에 따라 **계층을 나누어 관리**

```
         +-------+
         | Cache |              빠르고, 작고, 비싸다
         +-------+
      +-------------+
      | Main Memory |
      +-------------+
    +------------------+
    | Secondary Memory |        느리고, 크고, 싸다
    +------------------+
```

### HDD (Hard Disk Drive)

Spindle, Platter, Actuator Arm, Head, Cylinder로 구성된 대표적인 기계적 Secondary Memory

Sector $\rightarrow$ Track $\rightarrow$ Platter

Disk access time = $t_S+ t_R + t_T$

- $t_S$: Seek Time

    - 헤드를 올바른 트랙으로 재배치하는 데 걸리는 시간
    - 보통 4~10ms
- $t_R$: Rotational Latency

    - 원하는 섹터가 헤드 아래로 올 때 까지 플래터가 회전하는 시간
- $t_T$: Transfer Time

    - 데이터 전송 시간

### SSD(Solid State Drive)

하드디스크를 대체하는 Secondary Memory로 기계적 구동부가 없어 성능이 뛰어남

- Aging Problem: Write/Delete에 대한 사이클 횟수(물리적 제한)가 존재
- Asymmetric Read/Write Speed: Write가 Read보다 더 느림

    - SSD는 Overwrite 불가능 $\rightarrow$ **Erase-before-write**
    - R/W는 페이지 단위로 이루어지지만 Erase는 블록 단위로 이루어짐

### Sequential Read vs. Random Read

> **HDD의 경우**

**Sequential Read**: 연속된 디스크 블록들에 대한 데이터 요청

- 순차적 블록은 대개 같은(또는 인접한) 트랙에 위치함
- $\Rightarrow$ 첫 번째 블록에 접근할 때만 Seek 작업 필요
- Seek time 최소화 $\rightarrow$ 데이터 전송률 $\uparrow$

**Random Read**: 무작위 위치의 디스크 블록들에 대한 데이터 요청

- 위치가 무작위 $\rightarrow$ 매 접근마다 Seek 발생
- $\Rightarrow$ 데이터 전송률 $\downarrow$

중요한 차이: **Seek 발생 빈도**

> **SSD의 경우**

SSD는 Seek Time이 없지만 **I/O 초기화 오버헤드** 가 존재함
$\Rightarrow$ Random read를 하게 되면 이 오버헤드가 매 접근마다 발생
또한, SSD에서 Sequential Read 수행 시 여러 플래시 채널을 동시에 사용하여 데이터를 병렬로 읽어올 수 있지만 Random Read는 어려움
