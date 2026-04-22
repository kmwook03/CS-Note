## Structured Data Type

Program = Algorithms + Data Structures

- Encapsulation

    - Data와 Operation을 하나의 캡슐로 묶는 장치

### User-Defined Data Types

언어가 기본 제공하는 데이터 타입만으로 해결할 수 없다면 새로운 타입을 만들어야함

- Four Basic Mechanisms

    1. Structured Data: 복합 데이터를 만드는 기능
    2. Subprograms: 새로운 연산을 정의하는 기능
    3. Type Declarations: 데이터와 연산을 하나로 묶어 새 타입을 정의하는 기능
    4. Inheritance: 기존 타입의 기능을 포함 및 확장하는 기능

위 메커니즘 중 1, 2번은 필수 기능이고 3, 4번은 고급 기능임

#### Structured Data

**Data Structure**
다른 데이터 객체를 원소(elements)나 요소(components)로 하여 구성된 데이터 객체

- Issues

    - 요소 선택 방법
    - 메모리 관리 방법

**Specification**

- 요소 개수
- 요소 타입
- 요소 선택 방법
- 최대 요소 개수
- 구성 방법

**Operations**

- 데이터 구조에 관한 연산

    - 요소 선택 (임의/순차)
    - 전체 구조에 대한 연산
    - 요소 삽입/삭제
    - 데이터 구조 생성/소멸

**Implementation**

- 저장공간 형태

    - 연속 형태 (sequential)
    - 연결 형태 (linked)
- 연산 구현

    - 연속 selection: base-address + offset
    - 연결 selection: head-address + following links
- 저장공간 관리

    - 객체의 lifetime
        
        - lifetime: storage binding이 유지되는 시간
    - 저장공간 관리의 문제점

        - Garbage: 참조 경로를 잃은 객체
        - Dangling Reference: 해제된 공간을 가리킴

**Type Checking**

- selector를 통해 선택한 요소가 실제로 존재하는가 검사
- 선택된 요소의 타입도 다시 고려

### Arrays (Vectors)

같은 타입의 개체가 일렬로 나열된 **동형 구조(Homogeneous)**

- Attributes

    - 요소 개수
    - 요소 타입
    - 첨자(subscript)

- Operations

    - Component Operations

        - Selector: 첨자 연산으로 처리
        - Modifier: 첨자 연산으로 처리
        - Insert/Delete: 가변 길이 벡터에서만 허용됨
    - Whole Array Operations

        - size
        - array assignment
        - inner product
        - cross product
        - Whole Array Operation은 중간 결과를 저장할 공간이 필요함


#### Implementation (1차원 배열)

**참조 공식(accessing formula)**

- 할당된 첫 요소 주소 a, 요소 크기 E

I 번째 요소의 주소 lvalue(A[I])
= a + (I - LB) $\times$ E
= (a - LB $\times$ E) + I $\times$ E
= K + I $\times$ E

K: 정적 시간에 결정 가능한 **Virtual Origin(VO)**

**Dope Vector** `(VO, LB, UB, E)`
참조가 범위를 벗어나지 않았는지 검사하기 위해 가상 원점(VO), 하한값(LB), 상한값(UB), 요소 크기(E) 등의 정보를 모아둔 디스크립터

#### Implementation (2차원 배열)

- row-major: 행들의 1차원 배열 (대개 row-major로 구현됨)
- column-major: 열들의 1차원 배열

(C는 2차원 배열이 없어서 배열의 배열로 지원)

**참조 공식(accessing formula)**

lvalue(A[I,J])
= a + (I - LB$_1$) \times S + (J - LB$_2$) \times E
= a - LB$_1$ $\times$ S - LB$_2$ $\times$ E + I $\times$ S + J $\times$ E
= VO + I $\times$ S + J $\times$ E

- a = base address
- S = 한 행 크기 = (UB$_2$ - LB$_2$ + 1) $\times$ E
- VO = a - LB$_1$ $\times$ S - LB$_2$ $\times$ E

Dope Vector (VO, LB$_1$, UB$_1$, LB$_2$, UB$_2$, E)

#### Multi-Dimensional Array

- Multipliers

    - m$_n$ = e
    - m$_i$ = (U$_{i+1}$ - L$_{i+1}$ + 1) $\times$ m$_{i+1}$ for n-1 >= i >= 1

- Virtual Origin

    - VO = $\alpha$ - $\sum_{i=1}^{n} (L_i \times m_i)$

- Address of Elements

    - lvalue(A[$s_1, ..., s_n$]) = VO + $\sum_{i=1}^{n}(s_i \times m_i)$

**Slices**: 그 자체가 배열인 배열의 하부 구조

- Column slice
- Row slice
- Multidimensional slice

#### Associative Arrays

이름을 첨자로 사용하는 배열
(key, value)로 이루어진 참조 표(lookup table) 또는 사전(dictionary)으로 참조

- Operations

    - add: 새로운 (key, value) 추가
    - reassign: 기존 key의 value를 바꿈
    - remove: 기존 (key, value) 삭제
    - lookup: 특정 key와 연관된 값 참조

### Records

다른 타입의 정해진 수의 요소들을 하나로 모은 데이터 타입
$\Rightarrow$ Heterogeneous aggregation

- Attributes

    - 요소 개수
    - 요소 타입
    - 요소 선택자

- Operations

    - MOVE CORRESPONDING: 이름이 같은 필드끼리 한 번에 복사

`예`
```c
struct A { ... }; // 여기서 A는 tag임
typedef struct A A; // 여기서 오른쪽 A는 type임
```

#### Variant Records

하나의 타입에 여러 다른 타입이 올 수 있지만, 동시에 여러 값을 갖지는 않는 데이터 타입

모든 필드의 좌측값이 같은 단순히 공간 효율만을 위해 존재하는 타입

- 문제점: Type Checking

- 구분자(discriminator) 여부에 따른 분류

    - free-union
    - discriminated-union

`예`
```c
typedef union {
    int X;
    float Y;
    char Z[4];
} B;
B P;
```
새 데이터 객체의 L-value가 같기 때문에 타입 검사를 못함

### Lists

데이터의 순차 목록

- 배열과 차이점

    - 고정 길이가 아님
    - 동형 요소가 아닐 수 있음
    - 암시적 선언을 사용하는 경우가 많음

- Operations

    - nil: 빈 리스트
    - cons: 리스트에 특정 요소 접합
    - head: 리스트의 첫 번째 요소
    - tail: 첫 요소를 제외한 나머지 리스트

### Sets

서로 다른 값의 무순 모음

- Operations

    - 요소 검사(membership)
    - 요소 추가/삭제
    - 합집합, 교집합, 차집합

- Implementation

    - bitmap of enumerations: 집합 크기 제한됨
    - hashing: collision 해결 필요

        - rehashing
        - sequential scan
        - bucketing
