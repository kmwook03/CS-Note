## Branch and Bound

### Why?
0-1 Knapsack Problem이나 TSP(Traveling Salesperson Problem)와 같은 최적화 문제(Optimization Problem)를 해결하기 위해 등장

* **기존 방식의 한계**

    * 모든 경우의 수를 전부 탐색하는 Brute-Force는 상태 공간 트리(State Space Tree)의 크기가 입력에 따라 지수적으로 증가함
        
        * 0-1 Knapsack Problem: $O(2^n)$
        * TSP: $O(n!)$
    * 아이템 개수 $n$이 증가하면 트리의 노드 수가 기하급수적으로 폭발하는 조합 폭발(Combinatorial Explosion)이 발생하며 시간 내에 최적해를 찾을 수 없음
    * Dynamic Programming의 경우 가방의 용량 $W$가 비정상적으로 커지면 메모리와 시간 초과가 발생함(Pseudo-polynomial Time)

### Core Idea
가능한 모든 조합을 체계적으로 분기(Branch)하며 탐색하되, 유망하지 않은(Nonpromising) 경로는 조기에 배제(Bound & Prune)하여 효율적으로 최적해를 탐색

* **기반 관찰(Observation)**

    * 탐색 중인 특정 서브 트리에서 도달할 수 있는 이론상 최대 가치(Upper Bound)가 이미 확보한 현재까지의 최적해(Maxprofit)보다 작거나 같다면 그 서브트리는 더 이상 탐색할 가치가 없음
* **왜 이 전략이 문제를 해결할 수 있는가?**

    * 상태 공간 트리를 완전히 생성하지 않고도 최적해를 놓치지 않음을 보장할 수 있음
    * 상한선(Bound)이 완벽한 조건식을 갖추었기 때문에 가지치기(Pruning) 당한 경로에는 절대 정답이 없다는 것을 논리적으로 확신할 수 있음

### Algorithm1
`Base Strategy` **Breadth-First Search**

1. **Preprocessing**

    * 모든 아이템을 단위 무게당 가치$(p_i/w_i)$를 기준으로 내림차순 정렬
2. **Initialization**

    * 대기열 `Q`를 빈 큐로 초기화
    * `maxprofit = 0`
3. **탐색 Loop**

    * `Q`가 빌 때까지 다음을 반복

        * `Q`에서 노드 `v` 꺼냄
        * `v`의 자식 노드 `u`들을 순회 (Branch)
4. **Bound & Prune**

    * `value(u) > maxprofit && weight <= W` $\rightarrow$ `maxprofit = value(u)`
    * `bound(u) > maxprofit` $\rightarrow$ `Q`에 삽입

### Algorithm2
`Base Strategy` **Best-First Search**

1. **Preprocessing**

    * 모든 아이템을 단위 무게당 가치$(p_i/w_i)$를 기준으로 내림차순 정렬
2. **Initialization**

    * Priority Queue(`PQ`)를 생성하고 Root Node 삽입
    * `maxprofit = 0`
3. **탐색 Loop**

    * `PQ`가 빌 때까지 다음을 반복

        * `PQ`에서 가장 높은 Bound 값을 가진 Node `v`를 꺼냄 (Best-First)
        * 만약 `v`의 `bound`가 `maxprofit`보다 작거나 같다면 버림 (Pruning)
        * 다음 아이템을 포함하는 자식 Node `u1`과 포함하지 않는 자식 Node `u2`를 생성 (Branching)
4. **Bound & Prune**

    * 생성된 자식 Node의 `weight`와 `profit` 계산
    * `weight <= W && profit > maxprofit` $\rightarrow$ `maxprofit = profit`
    * 자식 Node의 `bound`를 계산
    * `bound > maxprofit` $\rightarrow$ `PQ`에 삽입

### Complexity

* **Time Complexity**

    * Worst Case: $O(2^n)$
    * Average Case: $O(2^n)$보다는 빠름
* **Space Complexity**

    * $O(2^n)$
* **Time Complexity of Bound Calculation**

    * 각 노드 생성 시 $O(n)$

### Bound Formula

$bound = (profit + \sum_{j=i+1}^{k-1}p_j) + (W - totweight) \times p_k/w_k$

0-1 Knapsack의 제약 조건을 이완(Relaxation)하여 아이템을 쪼개 넣을 수 있는 Fractional Knapsack으로 문제를 변경함

* **Invariant :** 이완된 문제의 최적해는 원본 문제의 최적해보다 항상 크거나 같다
* **Greedy Choice Property**

    * 무게당 가치가 높은 것부터 배낭의 남은 용량만큼 꽉 채우는 탐욕적 선택이 이완된 문제의 최적 부분 구조(Optimal Substructure)를 만족함
    * $\therefore$ 이 수식은 원본 문제의 Upperbound로 작용함

```cpp
float bound(node u) {
    int j, k;
    int totweight;
    float result;

    if (u.weight >= W)
        return 0;
    else {
        result = u.profit;
        j = u.level + 1;
        totweight = u.weight;
        // profit + ∑(p_j)
        while (j <= n && totweight + w[j] <= W) {
            totweight = totweight+ w[j];
            result = result + p[j];
            j++;
        }
        k = j;
        if (k <= n)
            result = result + (W - totweight)*p[k]/w[k];
        return result;
    }
}
```

### Comparison

| 알고리즘 | 특징 | 장점 | 단점 | 사용 불가 상황 |
|-|-|-|-|-|
| DFS (Backtracking) | LIFO 기반 가지치기 | 메모리 사용량 매우 적음 | 최적해 갱신이 늦어져 가지치기 효율 떨어짐 | 트리의 깊이가 비정상적으로 깊은 경우 |
| BFS | FIFO 기반 가지치기 | 레벨 단위 탐색으로 일관성 보장 | 메모리가 큐에 과도하게 쌓임 | 상태 공간 트리의 너비가 넓은 경우 |
| Best-First Search | Priority Queue 기반. 유망한(Promising) 노드 우선 탐색 | 최적해를 가장 빠르게 찾아내어 타 분기들을 조기에 무더기로 잘라낼 수 있음 | Priority Queue 유지 비용($O(\log Q)$)과 메모리 폭발(Memory Bound) 위험이 큼 | 메모리가 매우 제한된 임베디드 시스템 |
| DP | 하위 문제의 결과를 메모이제이션 | $O(nW)$의 일관된 수행 시간 보장 | 배낭 용량 W가 클 경우 메모리 초과 (Pseudo-polynomial) 발생 | $W$가 수십억 단위로 매우 큰 경우 |

### Implementation : Breadth-First

```cpp
void breadth_first_search(tree T) {
    queue_of_node Q;
    node u, v;
    initialize(Q);
    v = root of T;
    enqueue(Q, v);
    best = value(v);
    while (!empty(Q)) {
        dequeue(Q, v);
        for (each child u of v) {
            if (value(u) is better than best)
                best = value(u);
            if (bound(u) is better than best)
                enqueue(Q, u);
        }
    }
}
```

### Implementation : Best-First

* Priority Queue 설정

    * 최대 힙을 사용해야 하므로 bound 값을 정렬 기준으로 세워야함
* Bound Calculation 버그 주의

    * Float Division 연산

        * `(W - totweight) * (p[k] / w[k])` 계산 시 정수 나눗셈으로 인한 손실이 없도록 꼼꼼한 `float` 캐스팅 필요
    * Index Overflow

        * `k` 인덱스가 배열 범위를 벗어나지 않도록 `if (k <= n)` 조건 반드시 체크
* End Case

    * 배낭 용량(`W`)이 모든 아이템 무게 총합보다 큰 경우, 알고리즘 시작 전에 미리 예외처리하여 바로 $\sum p_i$를 리턴하도록 처리하면 연산 낭비를 막을 수 있음

```cpp
void best_first_branch_and_bound(state_space_tree T, number best) {
    priority_queue_of_node PQ;
    node u, v;
    initialize(PQ);         // PQ를 빈 대기열로 초기화
    v = root of T;
    best = value(v);
    insert(PQ, v);
    while (!empty(PQ)) {
        remove(PQ, v);      // 최고 한계값을 가진 branch 제거
        if (bound(v) is better than best) { // branch가 유먕한지 점검
            for (each child u of v) {
                if (value(u) is better than best)
                    best = value(u);
                if (bound(u) is better than best)
                    insert(PQ, u);
            }
        }
    }
}
```
