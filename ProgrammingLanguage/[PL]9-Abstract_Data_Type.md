## Abstract Data Type

### Abstraction
복잡한 시스템에서 불필요한 세부사항을 숨기고, 현재 관심 있는 핵심적인 특징과 동작에만 집중하여 모델링하는 기법

#### Information Hiding & Encapsulation

* Information Hiding: 시스템을 모듈화할 때 변경 가능성이 높거나 복잡한 설계 결정 사항을 외부 클라이언트로부터 숨기는 설계 원칙(Design Principle)
* Encapsulation: 데이터와 그 데이터를 조작하는 메서드를 하나의 단위로 묶는 언어적 기능(Language Facility)

(주의) Encapsulation $\neq$ Information Hiding

| | Encapsulation | Information Hiding |
|-|-|-|
| 개념적 본질 | 언어가 제공하는 기능적/문법적 도구 <br> (Language Facility) | 소프트웨어를 설계하는 철학 및 원칙 <br> (Design Principle) |
| 핵심 목적 | 데이터와 연산을 하나의 단위로 번들링 | 어려운 설계 결정이나 변경 가능한 구현 세부 사항의 은폐 |
| 관계성 | 캡슐화가 되었다고 해서 반드시 데이터가 은닉되는 것은 아님 | 정보 은닉을 안전하게 구현하기 위한 수단 중 하나로 캡슐화 문법을 활용할 수 있음 |

### Abstract Data Type (ADT)

`Type = Set of Values + Set of Operations`

연산의 세부 구현(Behavior)과 값의 실제 저장 형태(Data Structure)까지 모두 캡슐화되어 외부로 드러나지 않는 타입

* Algebraic Data Type
적용 가능한 연산자들 사이에 수학적 대수 법칙(Axioms)이 완벽히 만족하도록 정의된 데이터 타입 모델

`Example` 정수 스택 ADT operation
$
push: stack \times integer \rightarrow stack \\
pop: stack \rightarrow stack \\
top: stack \rightarrow integer \cup \{undefined\}
empty: stack \rightarrow Boolean \\
size: stack \rightarrow integer \\
newstack: \rightarrow stack
$

`Example` Axioms in Algebraic Data Type
$
pop(newstack) = newstack \\
pop(push(S,I)) = S \\
top(newstack) = undefined \\
top(push(S,I)) = I \\
empty(newstack) = true \\
empty(push(S,I)) = false \\
size(newstack) = 0 \\
size(push(S,I)) = size(S)+1
$

## Subprogram
사용자가 정의한 연산을 수행하는 코드블록

* type

    * 함수(function) : User-defined operators
    * 프로시저(procedure) : User-defined statements
