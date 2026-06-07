### Definition of Programming Language

$$PL\ def. = Syntax + Semantics$$

**구문(Syntax)** $\Rightarrow$ 프로그램의 **형태**에 대한 규정

**의미(Semantics)** $\Rightarrow$ 프로그램의 **동작**에 대한 규정

- 구문 표기법

    - BNF (Backus-Naur Form)
    - EBNF (Extended BNF)
    - CFG (Context-Free Grammar)
    - Static Semantics

        - CFG로 나타낼 수 없는 범위의 구문 규정

- 의미 표기법

    - Axiomatic Semantics
    - Denotational Semantics
    - Operational Semantics

### Translation

**Step 1. Analysis**

- lexical analysis; scanning

    - 프로그램을 단어 단위로 나누고 주석을 제거함

- syntax analysis; parsing

    - 구문 구조를 parse tree로 표현함

- semantic analysis

    - 타입 검사를 포함한 정적 의미 분석

**Step 2. Synthesis**

- code generation

    - parse tree로부터 수행 가능한 코드 생성

- optimization

    - 수행 성능 개선

### BNF(Backus-Naur Form)

- Nonterminal

    - 다른 형태로 치환 가능한 기호(변수) 집합
    - `<>`로 표현

- Terminal

    - 치환 불가능한 기호(상수) 집합
    - 그냥 쓰거나 `""`로 표현

- Start symbol

    - 특별 지정된 하나의 nonterminal

**Rule(productions)**: 각 nonterminal을 바꿔 쓸 수 있는 방법에 대한 규칙

```
(예)
<sentence> ::= <subject><predicate>
<subject> ::= <article><noun>
<predicate> ::= <verb><article><noun>
<verb> ::= ran | ate
<article> ::= the
<noun> ::= boy | girl | cake
```

**Replacement Operator($\Rightarrow$)**: nonterminal을 rule에 따라 치환하는 연산자

**Derivation**
start symbol로부터 replacement operation을 반복 적용하는 과정
Derivation의 결과로 만들어진 terminal sequence $\Rightarrow$ sentence

```
(예)
Rule
1. <sentence> ::= <subject><predicate>
2. <subject> ::= <article><noun>
3. <predicate> ::= <verb><article><noun>
4. <verb> ::= ran | ate
5. <article> ::= the
6. <noun> ::= boy | girl | cake

Derivation
<sentence>
=> <subject><predicate>
=> <article><noun><predicate>
=> the <noun><predicate>
=> the <noun><verb><article><noun>
=> the <noun><verb> the <noun>
=> the boy <verb> the <noun>
=> the boy ate the <noun>
=> the boy ate the cake
```

### EBNF(Extended BNF)

EBNF = BNF + 추가적인 메타 기호

- 메타 기호

    - Optional Elements: `[...]`
    - Alternative Elements: `(...|...|...)`
    - Sequence of Elements: `{...}*`

but, EBNF와 BNF의 표현력은 같음

```
(예)
EBNF: <number> ::= <digits> [. <digits>]
BNF : <number> ::= <digits> | <digits> . <digits>

EBNF: <signed number> ::= (+|-)<number>
BNF : <signed number> ::= +<number> | -<number>

EBNF: <identifier> ::= <letter> { <letter> | <digit> }*
BNF : <identifier> ::= <letter><les>
      <lds> ::= ε | <letter><lds> | <digit><lds>
```

### Syntax Chart(Syntax Diagram)

구문 규칙을 그림으로 표현한 것

- 좌측 nonterminal $\rightarrow$ 처음 화살표 시작 부분
- terminal $\rightarrow$ 동그라미
- nonterminal $\rightarrow$ 네모
- sequence $\rightarrow$ 화살표

![](https://velog.velcdn.com/images/kmwook/post/68edd20d-2041-453e-ab23-e49725513645/image.png)

### Parse Tree

Derivation 과정을 나타낸 트리

```
(예)
Grammar
    B -> 0B | 1B | 0 | 1

Derivation "010"
    B => 0B => 01B => 010
```

**Ambiguity**
하나의 문자열을 유도할 때 두 개 이상의 parse tree가 얻어질 경우
$\Rightarrow$ **모호한 문법(ambiguous grammar)**

```
(예)
Grammar
    S -> SS | (S) | ()
```
![](https://velog.velcdn.com/images/kmwook/post/3fe621c4-33be-48ef-9fc0-19226454d815/image.png)

- 대처법

    1. 문법 변경 G -> G', L(G) = L(G')
    2. 파서 변경

---

\<References>

- Pratt, T. W., & Zelkowitz, M. V. (2001). Programming Languages: Design and Implementation (4th ed.). Prentice Hall.

