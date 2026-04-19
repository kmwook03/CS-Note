## Indexing

### Data Retrieval Time
Phase 1. Search with a condition(predicate)
Phase 2. Data access
$\therefore$ **Data Retrieval Time = Search Time + Data Access Time**

$N_D = N_{record} / B_f$ ($N_D$: 디스크 접근 횟수)

우리는 $N_D$를 낮춰야함 $\rightarrow$ $B_f$를 올려야함

**Blocking Factor : $B_f$**
블록이 담을 수 있는 레코드 수

### Index

$F_{index}: S_{predicate} \rightarrow B$

- $S_{predicate}$ : 조건(predicate)을 만족하는 데이터
- $B$ : 데이터가 위치한 하드 디스크 상의 블록 넘버

\* 인덱스도 자료구조임

**Simple Idea: Inverted File**
키워드를 블록 넘버로 매핑하는 테이블을 만듦

- 한계점: 테이블이 너무 커서 메모리에 안들어가면 디스크에 저장해야함
- 인덱스 접근을 위한 디스크 접근? $\leftarrow$ 바보짓

**Accelerate Searching: Binary Search Tree**
Inverted file을 tree로 재구성함 $\rightarrow \ O(\log{n})$ 탐색

- 한계점: Branching Factor가 2라서 디스크 접근 횟수가 많음

**Disk Access Optimization: m-way Search Tree**
하나의 노드에 하나의 페이지 $\rightarrow$ Disk access $\downarrow$

(예) Page Size = 4KB
구분자 수 저장 공간 = 4bytes (int)
자식 노드를 가리키는 m개 블록 번호(int) 저장 공간 = 4m
구분자 개수 = m-1
구분자 하나 크기 = 8bytes(가정)
구분자 저장 공간 = 8(m-1)

$4 + 4m + 8(m-1) = 4096 \rightarrow m = \lfloor 341.666... \rfloor = 341$

- 한계점: m-way search tree의 탐색 성능은 높이에 의해 결정됨
- 트리가 균형이 맞지 않다면 최악의 경우 $O(n)$의 시간 복잡도를 가짐

### B-Tree: Balanced m-way search Tree

**Upward split**을 통해 항상 균형을 유지하는 트리

- Root Node: 0 또는 두개 이상의 child node
- Internal Node: $\lceil m/2 \rceil$ ~ $m$ 개의 child node
- External Node: Data block number

Number of Nodes to visit = Depth

- 한계점: 범위 탐색(Range Search) 성능이 매우 안좋음

### B+-Tree

모든 원소의 복사본을 Leaf Node에 두고 각 Leaf Node를 Linked List로 연결한 B-Tree
$\Rightarrow$ Range Search 성능 $\uparrow$
(단, 단일 검색 성능 약간 $\downarrow$)

- Internal Node: Leaf까지 가기 위한 이정표
- Leaf Node: 데이터들의 사본

**성능 분석**

깊이 $d = \lceil log_{\lceil m/2 \rceil}{n} \rceil$

- 단일 검색, 단일 삽입(split 없음): $d$개의 page 접근
- 범위 검색: $d + \lceil n_q/B_f \rceil$ ($n_q$: 검색할 레코드 수)
