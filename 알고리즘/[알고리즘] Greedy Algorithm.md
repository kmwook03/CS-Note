## Greedy Algorithm

시퀀스 내에서 매 판단 순간에 과거의 판단이나 미래를 고려하지 않고 **"best"** 로 보이는 데이터를 선택하는 알고리즘이다.
최적해를 보장하지는 않는다.

빈 집합에서 시작하여 집합이 해를 표현할 때 까지 원소를 추가한다.
각 반복에는 다음 동작을 수행한다.

- 선택 절차(selection procedure)
- 타당성 확인(feasibility check)
- 해 확인(solution check)

### 동전 교환 문제

> 특정 액수 $n$ 을 주어진 동전 집합 $C = \{c_1, c_2, ..., c_d\}$를 사용해서 만드는 방법을 찾는다.

$C = \{25, 10, 5, 1\}$

**추상화**
a, b, c, d를 각 동전의 개수라고하면
$n = 25a+10b+5c+d$

**그리디 알고리즘**
```c
coinGreedy(n) {
    if (n >= 25) {
        s = coinGreedy(n-25);
        s.a++;
    } else if (n >= 10) {
        s = coinGreedy(n-10);
        s.b++;
    } else if (n >= 5) {
        s = coinGreedy(n-5);
        s.c++;
    } else {
        s = (a=0, b=0, c=0, d=n, sum=n);
    }
    s.sum++;
    return s;
}
```

**최적 해를 보장하지 못하는 경우**
$n = 7$
$C = \{1, 3, 4, 5\}$

Greedy solution: 3 coins (5+1+1)
Optimal solution: 2 coins (3+4)



---
<Reference\>
- Neapolitan, R. E. (2015). Foundations of Algorithms (5th ed.). Jones & Bartlett Publishers.


