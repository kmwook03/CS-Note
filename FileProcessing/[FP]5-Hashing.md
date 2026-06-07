## Hash

### index vs. hash

**index**

- 추가적인 자료구조 필요
- 탐색 시 디스크 접근 연산 필요
- Primary index 또는 Secondary index로 활용 가능

**hash**

- 별도의 자료구조 필요 없음
- 대신 해시 함수(Hash Function) 필요
- $h(v) = b$
($h$: hash function, $v$: key value, $b$: block number)
- 블록 넘버가 해시 함수에 의해 정해짐 $\rightarrow$ Primary index로만 활용 가능

### Primary index vs. Secondary index

- **Secondary index**

    - Step 1: 레코드를 특정 블록 $b$에 저장
    - Step 2: 키 값 $v$와 블록 넘버 $b$를 함께 B+-Tree에 삽입
    - **블록 넘버가 B+-Tree와 무관하게 결정됨**

- **Primary index**

    - Step 1: 해시 함수 $h(v) = b$를 계산함
    - Step 2: 블록 $b$에 레코드를 저장함
    - **블록 넘버가 해시 함수에 의해 결정됨**

### Static Hash

할당 가능한 블록 수가 고정됨

**장점**

- 구현이 쉬움
- 정적 환경에서 최적의 해시 함수 제공

**단점**

- Block Overflow를 피할 수 없음

**Block Overflow**

- 데이터베이스가 커져서 블록 용량 한계를 초과
- 데이터 분포 쏠림
- 여러 개의 레코드가 같은 키를 중복으로 가짐
- 비균일 해시 함수 사용 

static hash의 구조적 특성 때문에 block overflow를 줄일 순 있어도 없앨 수는 없음

**Overflow Handling**

- 방법 1: 넘친 블록을 linked list로 연결
- 방법 2: Next Block = $B + h(v) + n$

### Dynamic Hash

데이터베이스 크기 변화에 유연하게 대응 가능함
별도의 bucket address table이 필요함

1. $b$ bits(typically $b = 32$)의 해시 값 생성
2. $b$ bits 중 $i$ bits를 prefix로 사용 ($0 \le i \le b$, 초기값 $i = 0$)
3. Bucket address table size = $2^i$
(버킷 공유에 의해 실제로는 더 작을 수 있음)
