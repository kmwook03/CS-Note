## Axiomatic System

**Axiom(공리)**
조건 없이 참이라고 전제된 명제 또는 올바르다고 간주되는 선언(assertion)
가정과 결론의 형태를 갖는 공리 = 규칙(Rule)

**Axiomatic System**
정리(Theorems)를 유도할 수 있는 임의의 공리 집합

### The Weakest Precondition

주어진 사후조건(postcondition, Q)에 대해 가장 제한이 덜 한 사전조건(precondition, P)

- wp(P, Q): 프로그램 P를 수행한 후 Q 조건을 만족하기 위한 가장 약한 사전조건

    - {wp(P,Q)} P {Q}

`예`
```
{P} sum := 2*x + 1 {sum > 1}
- wp(P, Q): x > 0
```

wp가 프로그램의 입력 명세로부터 추론 가능하고 주어진 사후조건이 원하는 출력 명세라면 Correct Program이 입증됨

### Axioms and Rules

**Assignment Axiom (할당 공리)**
```
{Q[E/x]} x := E {Q}

- Q[E/x]: Q에서 자유 변수 x를 모두 E로 치환한 것
```

`예`
```
{P} a := b/2 - 1 {a < 10}

wp(a := b/2 - 1, a < 10)
= (a < 10)[(b/2 - 1) / a]
= b/2 - 1 < 10
= b/2 < 11
= b < 22
```

**The Rules of Consequences (결과 규칙)**

- Weakening the Postcondition: 사후조건 약화

    - {P} S {Q}, Q $\Rightarrow$ R // {P} S {R}
- Strengthen the Precondition: 사전조건 강화

    - R $\Rightarrow$ P, {P} S {Q} // {R} S {Q}

- 종합

    - P$^\prime\ \Rightarrow$ P, {P} S {Q}, Q $\Rightarrow$ Q$^\prime$ // {P$^\prime$} S {Q$^\prime$}

**The Rule of Composition (합성 규칙)**
{P} S1 {Q}, {Q} S2 {R} // {P} S1 ; S2 {R}

`예`
```
{P} y := 3*x + 1 ; x := y + 3 {x < 10}
Let
    Q = wp(x := y + 3, x < 10) = y < 7
then
    P = wp(y := 3*x + 1, Q) = wp(y := 3*x + 1, y < 7) = x < 2
according to the rule of composition
```

**The Rule of Selection (선택 규칙)**

$\{P \wedge  B\} S1 \{Q\}, \{P \wedge \neg B\} S2 \{Q\}$
// `{P} if B then S1 else S2 {Q}`

`예`
```
{P} if (x > 0) then y := y - 1 else y := y + 1 {y > 0}

wp(y := y - 1, y > 0) = y > 1
wp(y := y + 1, y > 0) = y > -1
(y > 1) ∧ (x > 0) => y > 1
(y > -1) ∧ (x <= 0) => y > -1
Therefore P = (y > 1) (더 엄격한 조건)
(y > 1 ∧ x > 0) y := y - 1 (y > 0)
(y > 1 ∧ x <= 0) y = y + 1 (y > 2) => (y > 0)
```

**The Rule of Iteration (반복 규칙)**

$\{I \wedge  B\} S \{I\}$
// {I} while B do S {I $\wedge\ \neg$B}

- Loop Invariant **$I$**

    - 반복문 수행 전 중 후 모두 True인 조건

`예1`
```
Find the weakest precondition P

{P}
while y != x do
    y := y + 1
{y = x}

Guess I
i. {y=x} skip {y=x}
ii. {y=x-1} y := y + 1 {y=x}
iii. {y=x-2} y := y + 1 {y=x-1}
.
.
.
I: y <= x

Verify I
loop 종료 조건 I ∧ B'
= (y <= x) ∧ (y != x)'
= (y <= x) ∧ (y = x)
= (y = x)

wp(S, I) 검사
wp(y := y + 1, y <= x)
= (y <= x)[y+1/y] 
= y+1 <= x

x, y는 정수이므로 y < x 이고
(y < x) = (y <= x ∧ y != x) = I ∧ B

따라서 I = y <= x

루프 진입 전에 y = x인 경우에도 postcondition을 만족하므로
P = (y <= x)
```

`예2`
```
{?}
while s > 1 do
    s := s/2
{s = 1}

Guess I
i. {s=1} skip {s=1}
ii. {s=2} s := s/2 {s=1}
iii. {s=4} s := s/2 {s=2}
iv. {s=8} s := s/2 {s=4}
.
.
.
I: (s = 2^n) ∧ (n >= 0)

Verify I
loop 종료 조건 I ∧ B'
= ((s = 2^n) ∧ (n >= 0)) ∧ (s > 1)'
= ((s = 2^n) ∧ (n >= 0)) ∧ (s <= 1)
= (s = 2^n) ∧ (n = 0)
= (s = 1)

wp(S, I) 검사
wp(s := s/2, (s = 2^n) ∧ (n >= 0))
= ((s = 2^n) ∧ (n >= 0))[(s/2) / s]
= (s/2 = 2^n) ∧ (n >= 0) = (s = 2^(n+1)) ∧ (n >= 0)
= ((s = 2^n) ∧ (n >= 1))
= ((s = 2^n) ∧ (n >= 0)) ∧ ((s > 1))
= I ∧ B

따라서 I = (s = 2^n) ∧ (n >= 0)
루프 진입 전에 s = 1인 경우에도 postcondition을 만족하므로
wp(while s > 1 do s := s/2, s = 1) = (s = 2^n) ∧ (n >= 0)
```

`큰 예제`
```
{B >= 0}
a := A
b := B
y := 0
while b > 0 do
    begin
        y := y + a
        b := b - 1
    end
{y = AB}

Guess I
{y = AB} skip {y = AB}
{y = AB-a} y := y + a {y = AB}
{y = AB-2a} y := y + a {y = AB-a}
.
.
.
(y+xa = AB) ∧ (x >= 0)
x를 b로 고치면
I: (y+ab = AB) ∧ (b >= 0)

Verify I
loop 종료 조건 I ∧ B'
= ((y+ab = AB) ∧ (b >= 0)) ∧ (b > 0)'
= ((y+ab = AB) ∧ (b >= 0)) ∧ (b <= 0)
= (y+ab = AB) ∧ (b = 0)
= (y = AB)

wp(b := b - 1, (y+ab = AB) ∧ (b >= 0))
= ((y+ab = AB) ∧ (b >= 0))[b-1 / b]
= (y+a(b-1) = AB) ∧ (b-1 >= 0)
= (y+a(b-1) = AB) ∧ (b >= 1)

wp(y := y + a, (y+a(b-1) = AB) ∧ (b >= 1))
= ((y+a(b-1) = AB) ∧ (b >= 1))[y+a / y]
= (y+a+a(b-1) = AB) ∧ (b >= 1)
= (y+ab = AB) ∧ (b >= 1)
= ((y+ab = AB) ∧ (b >= 0)) ∧ (b > 0)
= I ∧ B

따라서 I = (y+ab = AB) ∧ (b >= 0)

wp(y := 0, (y+ab = AB) ∧ (b >= 0))
= (y+ab = AB) ∧ (b >= 0)[0 / y]
= (ab = AB) ∧ (b >= 0)

wp(b := B, (ab = AB) ∧ (b >= 0))
= ((ab = AB) ∧ (b >= 0))[B / b]
= (aB = AB) ∧ (B >= 0)

wp(a := A, (aB = AB) ∧ (B >= 0))
= ((aB = AB) ∧ (B >= 0))[A / a]
= (AB = AB) ∧ (B >= 0)
= (B >= 0)
```

### Impact of Program Verification

- Impact on the Language Design

    - 프로그램 검증을 어렵게 하는 기능은 언어에 포함되어서는 안된다 (예: aliasing)
    - assertion 첨가 기능의 도입

- Static Checkers의 발전

    - 프로그램이 만족해야 할 조건을 검사하는 프로그래밍 도구
    - 예: Spec#, Boogie

- Modeling Language와의 결합

    - OCL = UML + constraints
    - JML(Java Modeling Language), ESC/Java(Extended Static Checker for Java)
