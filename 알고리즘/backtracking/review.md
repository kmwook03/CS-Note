## 문제: 현대 10차 2번 기출

### 삽질 포인트
1. 겹치는 배터리 셀은 2개만 가능한데 전체 다 겹쳐도 되는 줄 알았음
2. 보드에 음수 가중치가 있을 때는 최종 점수 갱신값을 최소값으로 초기화해야함

### 핵심 전략: Backtracking

```cpp
    for (int d=0; d<4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (0<=nx && nx<N && 0<=ny && ny<M && !visited[nx][ny]) {
            // 결정
            visited[nx][ny] = true;
            current_cells.set(nx*M+ny);
            // 탐색
            dfs(x, y, depth+1, sum+board[nx][ny]);
            dfs(nx, ny, depth+1, sum+board[nx][ny]);
            // 복구
            current_cells.reset(nx*M+ny);
            visited[nx][ny] = false;
        }
    }
```

1. 결정: 현재 위치에서 갈 수 있는 다음 칸
2. 제약 확인: 이미 방문했는지, 경계 밖인지
3. 복구: 탐색 종료 후 갔던 기록 지움

### 테크닉: bitset

bitset을 이용한 교집합 검사는 배열이나 보드판 위 도형, 조합, 방문 상태 등을 다룰 때 유용함

#### 핵심: 2차원 공간(NxM)을 1차원 비트로 평탄화

`(x, y)` -> `(x * M + y)`

3x3 보드에서 두 개의 모듈 A, B가 있다고 할 때

- 모듈 A: 0, 1, 2, 3, 4 칸 차지 -> `000011111`
- 모듈 B: 3, 4, 5, 6, 7 칸 차지 -> `011111000`

두 비트 `&` 연산

```
  000011111
& 011111000
------------
  000011000     -> 3번, 4번 겹침
```

2중 for문으로 배열 비교보다 훨씬 빠르다!

`.count()` -> 1 개수 반환
```cpp
if ((modules[i].cells & modules[j].cells).count() == 2)
```

=> 두 칸 겹칠 경우