## Elementary Data Type

### Data and Type

**Data** : 숫자, 문자 등 프로그램의 처리 대상
**Type** : 데이터를 분류해둔 것 (`값 집합` + `연산 집합`)

- Abstract Data Type: 연산 구현 방법이 명시되지 않은 데이터 타입

**Data Object**
데이터 값을 포함하는 container 또는 memory location
일반적으로 **변수(variable)** 라고 함

**Data Value**
특정 값을 나타내는 비트 패턴

**Data Attribute**
`Type`, `Location`, `Value`, `Name`, `Scope`, `Lifetime`,`Component` 등

`Component`는 다른 데이터 객체를 가리키는 포인터 값이 될 수 있음

- **상수(Constant)**

    - 본질적으로는 변수의 일종
    - 반드시 초기화(value binding) 되어야하며 한 번 값이 초기화된 후에는 변경할 수 없음

    - 종류

        - Literal: 생긴 형태 자체가 이름이자 값
        - Named constant: 값 이외에 별도의 이름이 있음 (static value binding)

### Data Type

```
Data Type = Set of Values + Set of Operations
```

**Specification of Data Type**
모든 데이터 타입은 이상적으로 명확한 명세(specification)가 주어져야함

- 속성(Attributes) : 해당 타입의 데이터 객체들을 구별 짓는 속성
- 값(Values) : 해당 타입의 데이터 객체가 가질 수 있는 값 집합
- 연산(Operations) : 해당 타입의 데이터 객체를 조작할 수 있도록 정의된 연산 집합

`예`

```c
char s[5];
```

```
specification

- attributes: s의 크기는 5, s의 원소 타입은 signed char
- value set: S = C * C * C * C * C
    - C: signed char의 value set
- operation set:
    - [] : S * I -> C
    - 여기서 I = {0, 1, 2, 3, 4, 5}
```

연산 정의를 어렵게 하는 요인

- 특정 입력에 대해 정의되지 않음 (예: 배열 인덱스 초과)
- 암시적으로 전달되는 인수 (예: 전역 변수)
- 부대 효과(side effect)
- 자기 수정(self-modification; history sensitivity)

#### Subtype

$Subtype \subseteq Subset$

어떤 데이터 타입의 값 집합 일부를 취해서 만든 타입

Subtype 개념이 클래스(Class) 사이로 확장 $\rightarrow$ 상속(Inheritance)

### Declaration

언어 처리기(컴파일러 또는 인터프리터)에 데이터 객체 이름과 타입 정보를 전달

선언문은 수행(execution)된다고 하지 않고 상세화(elaboration) 된다고 함

선언문 위치 및 종류에 따라 데이터 객체의 scope와 lifetime이 결정됨

- 종류

    - 명시적 선언: C 등 일반적인 언어
    - 암시적 선언: FORTRAN, Perl 등 고전 언어, 인터프리터 언어

- 선언의 주요 목적

    - 저장 형태 결정
    - 메모리 관리
    - 다형 연산 지원
    - 타입 검사

### Type Checking

연산자나 서브 프로그램에 대해 적절한 개수의 인수와 적절한 타입을 사용하는지 검사함

- 검사 시기에 따른 분류

    - Static type checking: 컴파일 타임에 검사
    - Dynamic type checking: 런 타임에 검사

- Typeless Languages
    
    - Dynamic type checking을 수행하는 언어 중 선언문도 없고 변수의 타입도 없이 유동적인 언어
    - 장점

        - 유연한 데이터 처리
        - 낮은 학습 곡선
        - 짧은 코드
    - 단점

        - 런타임 에러 발생 가능성 높음
        - 가독성 저하로 인한 디버깅 어려움
        - 런타임에 타입 검사 및 변환이 이루어져 발생하는 성능 저하

**Strong Typing**: 타입 오류가 있는 경우 항상 이를 검출할 수 있는 타입 검사

- 검사 조건

    - type safe function f: S $\rightarrow$ R에서 f를 수행한 결과 R 이외의 값은 나올 수 없어야함

Strong Typing을 수행하는 언어 $\rightarrow$ **강형 언어(strongly-typed language)**

대부분의 언어가 강형언어라고 주장하지만 그렇지 않은 경우가 더 많음
(예: c의 `union`, `void *`, `type casting 연산` 등)

### Type Inference

정적 타입 검사를 수행하는 언어 중 명시적 선언이 필요 없는 언어가 있음
이런 언어들은 타입 추론이 필요함

대표적인 예시: ML

- 모호하지 않은 경우 타입 선언 생략 가능
- 언어 자체에서 이런 경우에 대해 타입 정보를 추론해내는 기능을 제공함
- 예1: fun times10(x) = 10*x;

    - 반환 타입과 인자 x의 타입은 int로 추론
- 예2: fun area(length, width) = length * width;

    - binary \* 는 int, real 모두에 정의되어있기 때문에 추론 불가

### Type Conversion & Coercion

서로 다른 타입(mixed mode)의 데이터를 하나의 연산자로 연산하려고 할 때 필요

- 타입 변환 연산자의 유무에 따른 분류

    - 명시적(explicit): 타입 변환 연산을 명시적으로 나타냄 (type casting)
    - 암시적(implicit): 타입 변환 규칙이 정해져 있음(type coercion)

- 정보 손실의 유무에 따른 분류

    - 확장 변환(widening): 정보 손실 없음
    - 축소 변환(narrowing): 정보 손실 가능성 있음

```pascal
var A: real;
    B: integer;

A := B // 암시적, 확장 변환

B := A // 축소 변환 불가(데이터 손실 유발)
       // 형 변환을 위한 함수 제공 -> 명시적 변환
       // B := round(A)
       // B := trunc(A)
```

### Assignment

**L-value**: 객체의 위치 (box)
**R-value**: 변수의 내용 (contents)

```pascal
A := B + C;

(*
 1. B의 위치에 있는 내용을 가져옴
 2. C의 위치에 있는 내용에 B의 내용을 더함
 3. A의 주소에 결과를 저장함
*)
```

- address-of $\rightarrow$ L-value
- contents-of $\rightarrow$ R-value

#### Assignment Issue

**Side Effect of the Operation**
데이터 객체에 바인딩 된 값을 변경한다는 점에서 연산 자체가 Side effect임

**Cascading Assignments**
할당 연산자의 반환 값에 따라 연속 지정 지원 여부가 결정됨

- Pascal Assignment

    - (:=) : integer $\times$ integer $\rightarrow$ void
    - `A := B := C;` 불가능

- C Assignment

    - (=) :  integer $\times$ integer $\rightarrow$ integer
    - `A = B = C;` 가능

**Kinds of Assignment**

- Scalar Assignment: 값 복사 (예: 정수, 실수 등 단일 데이터)
- Pointer Assignment: 포인터 복사
- Record Assignment: 비트 단위 복사, 필드 단위 복사 (예: 복합 데이터 할당)

#### Scalar Data and Composite Data

**Scalar Data**
하나의 데이터 객체는 하나의 값만 나타냄 (예: 정수)
하드웨어를 통해 직접 구현

**Composite Data**
하나의 데이터 객체가 여러 정보를 포함함 (예: 문자열)
소프트웨어의 도움을 받아 지원됨

### Numeric Data Type

#### Integers

- Set of Values

    - MinInt ~ MaxInt 형태
    - 일반적으로 2's complement로 구현

- Operations

    - 산술연산
    - 관계연산
    - 대입연산
    - 비트연산

- Implementation

    - 통상 descriptor 없음
    - but, dynamic type checking을 위해서는 descriptor 필요

#### Floating-Point Real Numbers

- Set of Values

    - -MaxNum ~ +MaxNum 형태

- Operations

    - 정수형의 모든 연산
    - 언어에 따라 나머지 연산 포함
    - 소수점 이하 처리 연산
    - 기타 수학 함수: sin, maximum, absolute, ...

- Implementation

    - IEEE Standard 754 (Sign, Exponent, Mantissa)

### Enumerations

이산적인 값들의 순차 목록
가독성을 높이고 타입 검사가 가능하도록 한다

```c
enum StudentClass {Fresh, Soph, Junior, Senior};
enum StudentClass level;
level = Junior;
level = 10; // c++에서는 type error가 발생하지만 c에서는 발생 안함
// c에서 enum은 내부적으로 int로 취급되기 때문
```

### Booleans

True, False를 나타내기 위한 데이터 타입

- Set of Values

    - {true, false}

- Operations

    - and: Boolean $\times$ Boolean $\rightarrow$ Boolean
    - or: Boolean $\times$ Boolean $\rightarrow$ Boolean
    - not: Boolean $\rightarrow$ Boolean

- Implementation

    - Pascal, Ada의 경우 enumeration의 특수한 경우로 구현
    - 이외에는 두 가지 형태로 구현

        - 특정 패턴: 0 = false, 1 = true
        - 0과 기타: 0 = false, else = true

### Characters

문자를 나타내기 위한 데이터 타입

- Set of Values

    - ASCII, UNICODE 등 문자 집합

- Operations

    - 타입 변환 연산자
    - collating sequence에 의한 문자 변환 연산자

- Implementation

    - 특정 character set 지정
    - collating sequence: character set에 따라 결정되는 문자 순서
    - 확장 가능한 다른 타입을 제공하는 언어도 있음

### Composite Data Types

여러 정보를 포함하는 데이터를 나타내기 위한 타입
본 문서에서 다루는 composite data type은 elementary data type에 해당함

- Composite data: 여러 데이터 $\rightarrow$ 한 단위의 데이터
- Derived type: 기존 데이터 타입 $\rightarrow$ 새로운 데이터 타입

#### Character Strings

primitive data type의 문자들로 이루어진 문자열
문자열 자체를 primitive data type으로 제공하는 언어도 있음

- Fixed length
    
    - `char A[10];` (C)
    - `DCL B CHAR(10)` (PL/I)
    - `var C : packed array [1..10] of char` (Pascal)

- Variable length

    - DCL D CHAR(20) VARYING (PL/I - 0 to 20 characters)
    - E = "ABC" (SNOBOL4 - any size, dynamic)
    - F = "ABCDEFG" (C - any size, programmer defined)

- Operations

    - Concatenation, Substring, Reverse, ...
    - 제공 방법: language-defined operators, library functions

#### Pointers

다른 데이터 객체를 가리키기 위한 데이터 타입
$\Rightarrow$ 주소(address) 저장을 위한 데이터 타입

Recursive data structure를 만들기 위해 필요함
