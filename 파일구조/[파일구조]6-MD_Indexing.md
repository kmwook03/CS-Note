## Multi-Dimensional Index

### Multi-Attributes Query

여러 개의 속성을 조건으로 검색함
각 속성이 차원

### Processing Method

**Method 1**: B+-Tree 하나만 사용

Step 1. 조건 A에 대해 B+-Tree 적용
Step 2. Step 1의 결과 안에서 조건 B 검색

- 한계점: 조건 적용 순서에 따라 성능 차이 발생

**Method 2**: B+-Tree 두개 사용

Step 1. 조건 A에 대해 B+-Tree 적용 $\rightarrow$ Result$_1$
Step 2. 조건 B에 대해 B+-Tree 적용 $\rightarrow$ Result$_2$
Step 3. Result$_1$ $\cap$ Result$_2$ $\rightarrow$ Result

- 한계점: 두 조건을 동시에 만족하는 학생이 극소수일 경우 비효율적임

**Method 3**: Unified Index 사용

Unified Index = 여러 개의 속성에 대한 하나의 인덱스

- Approach

    - Extending B+-Tree
    - Extending Dynamic Hashing

### Extending Dynamic Hashing : Grid Approach

다차원 공간을 고정 크기 또는 가변 크기의 그리드로 나누고 디렉토리를 통해 해당 격자 공간 내의 객체들이 저장된 블록 포인터를 가리킴

- 한계점: 객체가 없는 빈 공간(**Dead Space**)이 발생함
- 해결책: 실제 객체들이 존재하는 영역만 MBR(Minimum Bounding Rectangle)로 감싸서 dead space 탐색을 줄이고 디스크 접근을 최소화함

### Extending B+-Tree : R-Tree

다차원 구간을 다루는 B+-Tree

각 노드는 MBR이고 Leaf Node를 linked list로 연결하지 않음

- Leaf Node: 실제 다차원 객체 저장
- Internal Node: 자식 노드들을 감싸는 MBR과 자식 노드 포인터 저장

overlapping은 피할 수 없음

**Splitting Strategy : Line sweeping**
Cost-X와 Cost-Y를 비교하여 분할 선(Splitting line)을 결정하고 새로운 MBR을 생성함

- Good Split

    - 각 MBR 들이 가능한 한 COMPACT 하게
    - 객체들 간 공간적 인접성(spatial proximity)이 최대한 보존되게

### R*-Tree

오버플로우 발생 시 단순 노드 분할은 필연적으로 MBR overlapping을 유발함

$\Rightarrow$ 오버플로우가 발생한 노드의 일부 객체를 삭제 후 다시 넣자!

삭제 후 재삽입 $\rightarrow$ Compact $\uparrow$
