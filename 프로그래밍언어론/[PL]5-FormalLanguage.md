## Modeling Language Properties

### Formal Languages (형식 언어론)

규칙에 의해 규정되는 언어와 이를 인식하는 오토마타에 관한 이론

#### Chomsky Hierarchy

**문법 분류**

- **Type 3: 정규 문법 (Regular Grammars)**

    - with Finite Automata

- **Type 2: 문맥 자유 문법 (Context Free Grammars)**

    - with Nondeterministic Pushdown Automata

- **Type 1: 문맥 민감 문법 (Context Sensitive Grammars)**

    - with Linear Bounded Automata

- **Type 0: 무제한 문법 (Unrestricted Grammars)**

    - with Turing Machine

**Regular Grammar**

- 형태

    - 좌변: nonterminal 한개
    - 우변: 정해진 한쪽 끝에만 nonterminal 한개

- 예

    - $Id \rightarrow aX|...|zX|a|...|z$
    - $X \rightarrow aX|...|zX|0X|...|9X|a|...|z|0|...|9$

- 특징

    - $a^n$ 형태의 string을 생성함

- 인식 모델

    - Finite Automata

**Context Free Grammars**

- 형태

    - 좌변: nonterminal 한 개
    - 우변: 제한 X

- 예

    - $E \rightarrow E + T\ |\ T$
    - $T \rightarrow T * F | F$
    - $F \rightarrow n\ |\ (E)$

- 인식 모델

    - Nondeterministic Pushdown Automata

**Context Sensitive Grammars**

- 형태

    - 좌변: nonterminal로 이루어진 문자열
    - 우변: terminal 또는 nonterminal로 이루어진 문자열
    - `<제약> 좌변 길이 < 우변 길이`
    - $\therefore$ 공 문자열($\epsilon$) 생성 불가

- 예

    - $S \rightarrow abc\ |\ aSBc$
    - $CB \rightarrow Bc$
    - $BB \rightarrow bb$
    - $L(G) = \{a^nb^nc^n\ |\ n \ge 1\}$

- 인식 모델

    - Linear Bounded Automata

**Unrestricted Grammars**

- 형태

    - 제한 없음

- 예

    - $S \rightarrow ACaB$
    - $CA \rightarrow aaC$
    - $CB \rightarrow DB$
    - $AE \rightarrow \epsilon$
    - $L(G) = \{a^n\ |\ n=2^m,\ m \ge 1\}$

#### Turing Machine

읽고 쓸 수 있는 무한 길이의 테이프와 유한 제어 장치로 구성된 유효 절차 형식 모델

- Memory(tape): 무한 길이의 배열
- Control: read/write 헤드, 좌우 이동

**Church's Thesis**
"계산 가능한 모든 함수는 튜링 머신으로 계산할 수 있다."
튜링 머신과 동일한 연산 능력 가짐 $\Rightarrow$ Turing-Complete

시간적 공간적 제약이 없을 때에도 튜링 머신으로 일반 해를 찾을 수 없는 문제
$\rightarrow$ **Undecidable Problem**

- 예: Halting Problem

### Language Semantics (언어 의미론)

- Static Semantics (정적 의미론): 구문 분석의 범위를 벗어나는 검사를 처리
- Dynamic Semantics (동적 의미론): 실행 중 프로그램의 동작 의미 파악

    - Abstraction Machine Code $\rightarrow$ Operational Semantics
    - Logical Predicates $\rightarrow$ Axiomatic Semantics
    - Lambda Notations $\rightarrow$ Denotational Semantics

#### Semantic Approaches

**Grammatical Model: Attribute Grammar**
```
Attribute Grammar = Grammar + Evaluation Rules
```
문법의 각 기호에 속성을 부여하고 속성 값을 구하는 평가 규칙을 문법과 함께 제시하여 의미를 표현함

- 속성

    - 종합 속성(synthesized attribute): 파스트리 노드의 속성 값이 자손 노드 속성 값에 의존하는 경우
    - 상속 속성(inherited attribute): 파스트리 노드의 속성이 부모나 형제에 의존하는 경우

**Operational Model: Operational Semantics**
실제 컴퓨터를 추상화한 가상 머신의 동작 상태 변화를 통해 프로그램 의미를 표현함

- 가상 머신

    - State: memory, register, I/O device에 대한 추상화
    - State Transition Mechanism: processor에 대한 추상화

`예`
$<z:=x\ ;\ x:=y\ ;\ y:=z,\ [x \rightarrow 5, y \rightarrow 7, z \rightarrow 0]>$

$\Rightarrow \ <x:=y\ ;\ y:=z,\ [x \rightarrow 5, y \rightarrow 7, z \rightarrow 5]>$

$\Rightarrow \ <y:=z,\ [x \rightarrow 7, y \rightarrow 7, z \rightarrow 5]>$

$\Rightarrow \ <,\ [x \rightarrow 7, y \rightarrow 5, z \rightarrow 5]>$

**Applicative Model: Denotational Semantics**
프로그램의 의미를 함수로 표현

의미 함수(semantic function): 의미 영역(semantic domain)의 값을 다루는 함수

**Axiomatic Model: Axiomatic Semantics**
```
{P} program {Q}
```
프로그램 요소 수행 전의 사전조건(precondition, P)과 수행 후의 사후조건(postcondition, Q)을 통해 의미 표현

**Specification Model: Algebraic Data Types**
특정 타입 데이터에 대해 연관된 함수들이 반드시 만족해야 할 상호관계(specification)를 대수적 공리(algebraic axiom)로 명시하여 표현
