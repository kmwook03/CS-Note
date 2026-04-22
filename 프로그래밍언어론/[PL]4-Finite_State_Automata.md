## Grammar & Automata

### Finite State Automata

Grammar $\rightarrow$ 언어 **생성기**
Automata $\rightarrow$ 언어 **인식기**

**Finite Automaton**: 유한 개의 상태로 문자열을 인식하는 자동 기계

- Finite State Machine의 일종
- 초기 상태($q_0$)로부터 시작하여 입력 기호를 보고 상태 전이
- 최종 상태($F$)에 도달하면 문자열 인식
- FA $M=(Q, \Sigma, \delta, q_0, F)$
- FA $M$이 인식하는 언어 $L(M)=\{w\ |\ \delta(q_0, w) \in F\}$

**Deterministic Finite Automata**
어떤 상태에서 입력 기호에 따라 전이될 수 있는 상태가 단 하나인 오토마타

**Nondeterministic Finite Automata**
어떤 상태에서 입력 기호에 따라 전이될 수 있는 상태가 여러 개인 오토마타
여러 경로 중에서 하나라도 최종 상태에 도달하면 문자열을 인식한 것으로 판별함

- 모든 DFA는 NFA의 일종임

모든 NFA $M$은 DFA $M^{\prime}$으로 변환 가능
$$L(M)=L(M^{\prime})$$

![](https://velog.velcdn.com/images/kmwook/post/6ee6db0e-036c-44ac-ac7a-c96f149bd0b1/image.png)

NFA에서 갈 수 있는 모든 상태의 집합을 DFA의 상태로 간주하여 변환함

1. 원본 NFA의 상태가 3개이므로 이를 조합해 만들 수 있는 DFA의 최대 상태 개수는 $2^3=8$ 개

2. 각 상태 집합에서 입력을 받았을 때 전이 방향은 합집합($\cup$) 연산으로 계산

3. 원본 NFA에서 $q_2$ 가 종결 상태였으므로 $q_2$ 를 포함하는 집합은 모두 종결 상태로 간주 

![](https://velog.velcdn.com/images/kmwook/post/104663a3-3abd-4497-9c86-d4e0226b358f/image.png)

4. 도달 불가능 상태 제거

![](https://velog.velcdn.com/images/kmwook/post/409cb18e-d5fb-4c8e-a212-03036bb21d50/image.png)

### Regular Grammar


특수한 형태의 생성 규칙으로만 이루어진 문법

**규칙**
```
<nonterminal> ::= <terminal> <nonterminal> | <terminal>
```
(예) A $\rightarrow$ 0A | 1A | 0

nonterminal 기호는 우변의 특정 위치에 하나만 올 수 있음

- **Left** Linear: 우변의 **좌측** 끝에만 nonterminal이 올 수 있음
- **Right** Linear: 우변의 **우측** 끝에만 nonterminal이 올 수 있음

!주의! 하나의 정규 문법 안에는 한 가지 방향만 사용해야 함

### Regular Expression

정규 언어가 만족해야할 패턴을 간단한 식으로 정의하는 방법

- 기본 정규식

    - 단말기호: terminal
    - 공문자열: $\epsilon$
    - 공집합: $\emptyset$

a와 b가 정규식이면, 이를 조합한 (a|b), (ab), (a*) 역시 정규식임

| 이름 | 역할 |
|-|-|
| Relgular Language | 프로그래밍 언어의 어휘 패턴을 나타내기에 충분한 언어 |
| Regular Expression | 어휘의 패턴을 나타내는 방법 |
| Finite Automata | 어휘를 인식하는 기계 $\rightarrow$ 어휘분석기 |

문법 = 언어에 대한 설계도, 문자열 생성기
오토마타 = 문자열 및 패턴 인식기

프로그램을 구성하는 identifier, number, keyword, special symbol들은 정규 문법으로 정의할 수 있고 정규 문법은 FA로 매핑이 가능함

$\therefore$ 어휘 분석 파이프라인 = 정규식 $\rightarrow$ NFA $\rightarrow$ DFA

### Pushdown Automata

**FA의 한계**
FA는 상태가 유한하고 메모리가 없음 $\rightarrow$ 입력된 문자 개수를 셀 수 없음

$\therefore$ $a^nb^n$과 같이 앞뒤 문자의 짝이나 개수를 맞춰야하는 패턴 인식 불가

**Stack의 도입**
위 FA의 한계를 극복하기 위해 FA에 Stack 메모리를 추가
$\Rightarrow$ **Pushdown Automata (PDA)**

- PDA 동작 방식

    1. 입력 기호(current input symbol)와 스택 기호(stack top) 읽음
    2. 상태 전이 및 스택 변경 (push | pop)
    3. 입력 문자열을 모두 읽음 && (stack empty || 최종 상태 도달) $\rightarrow$ 문자열 인식

**PDA 예시**

- 상태 = {$q_1,q_2,q_3$}
- 입력 알파벳 = {a, b}
- 스택 알파벳 = {A, B, C}
- 초기 상태 = $q_1$
- 초기 스택 기호 = C
- 최종 상태 = {$q_3$}
- 전이 함수(상태, 남은 입력, 스택 기호):

    - move($q_1$, a, C) = ($q_1$, AC)
    - move($q_1$, a, A) = ($q_1$, AA)
    - move($q_1$, b, A) = ($q_2$, $\epsilon$)
    - move($q_2$, b, A) = ($q_2$, $\epsilon$)
    - move($q_2$, $\epsilon$, C) = ($q_3$, $\epsilon$)
    
입력 문자열 = aabb

($q_1$, aabb, C)
$\vdash$ ($q_1$, abb, AC)
$\vdash$ ($q_1$, bb, AAC)
$\vdash$ ($q_2$, b, AC)
$\vdash$ ($q_2$, $\epsilon$, C)
$\vdash$ ($q_3$, $\epsilon$, $\epsilon$)

**Nondeterministic PDA (NDPDA) & Deterministic PDA (DPDA)**

NDPDA와 DPDA가 인식하는 언어 범위는 다름

- 팰린드롬 예시

    - DPDA: $S \rightarrow 0S0\ |\ 1S1\ |\ 2$ (2라는 명확한 중간점이 존재)
        
        1. 0과 1은 읽을 때마다 스택에 push
        2. 2를 읽으면 다른 상태로 이동
        3. 스택 기호를 pop 하면서 입력과 비교

    - NDPDA: $S \rightarrow 0S0\ |\ 1S1\ |\ 0\ |\ 1$ (중간점이 없음)

        중간 문자 예측 필요

        - (예) 011010110
        - `(stack, guess, match reminder)`
        - (, 0, 11010110)
        - (0, 1, 1010110)
        - (01, 1, 010110)
        - (011, 0, 10110)
        - (0110, 1, 0110) <-- 옳게 추측한 경우
        - (01101, 0, 110)
        - (011010, 1, 10)
        - (0110101, 1, 0)
        - (01101011, 0, )

### Parsing

#### LR Parsing

DPDA가 인식하는 언어는 LR(k) 문법으로 표현 가능함

**LR(k)**

- **L**eft-to-right scan : 입력 문자열을 왼쪽에서 오른쪽으로 읽음
- generating **R**ight parse : 우측 유도의 역순으로 파스 트리 생성
- with **k** simbol lookahead : 상태 전이 결정을 위해 k 개의 입력 기호를 미리 봄

LR(k) 파서 종류

- CLR(k) : Canonical LR
- SLR(k) : Simple LR
- LALR(k) : Lookahead LR

**YACC**: LALR(1) 파서 생성기. 일상적인 프로그래밍 언어 파싱 가능.

#### Recursive Descent Parsing

문법과 파서 구조가 동일한 top-down 구문 분석 방법
nonterminal에 해당하는 재귀적 프로시저들로 구성됨

**구성 원리**

1. 각 생성규칙의 우변을 따라하는 프로시저 구성
2. nonterminal을 만나면 프로시저 호출
3. terminal을 만나면 lookahead와 일치 검사
4. 일치 $\rightarrow$ skip, 불일치 $\rightarrow$ syntax error

**구성 예**

- BNF Rule

```
<expression> ::= <term>{(+|-)<term>}*
```

- Expression Procedure

```pascal
(* Pascal Style *)
procedure Expression;
begin
    Term; (* Call Term to find first Term *)
    while ((nextchar = '+') or (nextchar = '-')) do
    begin
        nextchar := getchar; (* Skip over operator *)
        Term
    end
end
```

```c
/* C style */
void Expression() {
    Term(); // Call Term to find first Term
    while (nextchar == '+' || nextchar == '-') {
        nextchar = getchar(); // Skip over operator
        Term();
    }
}
```

- 위 코드로 Postfix 생성 프로그램 작성

```c
/* C style */
void Expression() {
    Term(); // Call Term to find first Term
    while (nextchar == '+' || nextchar == '-') {
        plusType = nextchar; // Save the operator
        nextchar = getchar(); // Skip over operator
        Term();
        output(plusType);
    }
}
```
