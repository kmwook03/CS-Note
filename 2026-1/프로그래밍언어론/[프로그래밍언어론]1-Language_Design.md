### Programming Language?
**Programming Language** => 기계를 제어할 수 있는 표현

![](https://velog.velcdn.com/images/kmwook/post/300369cb-aa6f-44b3-a006-45f8ff517690/image.png)


### 분류

**Problem domain: 언어의 목적**
	
   - Business
   - Scientific
   - System
   - AI
   - Web

**Programming paradigm: 프로그래머의 사고 방식**
	
   - Procedural Programming(절차적 프로그래밍)
    	
       - 예) Fortran, Pascal, C, ...
        
   - Functional Programming(함수형 프로그래밍)
    	
       - 예) LISP, Scheme, ML, Haskell, ...
        
   - Object Oriented Programming(객체지향 프로그래밍)
    	
       - 예) Smalltalk, C++, Ada, Java, ...
        
   - Declarative Programming(선언적 프로그래밍)
    	
       - 예) Prolog, ...
        
   - Modular Programming(모듈 프로그래밍)
    	
       - 예) Modula-2, Ada, ...
   - Generic Programming(제네릭 프로그래밍)
    	
       - 예) Ada, ML, C++, ...
        
**Computational model: 언어의 이론적 뿌리**
	
   - Imperative Language(명령형 언어): 폰 노이만 구조 기반
   - Functional Language(함수형 언어): 순환 함수 이론 기반
   - Logical Language(논리 언어): 연역 논리 기반
   

### 좋은 언어

>**1. Clarity, Simplicity, Unity**
>**2. Orthogonality**
>**3. Language features**
>**4. Support for abstraction**
>**5. Ease of verification**
>**6. Programming environment**
>**7. Program portability**
>**8. Cost of use**

**Clarity, Simplicity, Unity**
간단하고 명확해야 배우기 쉬움

**Orthogonality: 직교성**
몇 개의 다른 기능을 임의로 예외 없이 조합할 수 있음 
$\Rarr$ **기능들의 독립성이 보장됨**

>부족한 직교성의 예시 (`C`)

```c
// 1. 일반 원시 타입의 대입 (가능)
int a = 10;
int b;
b = a; // 정상 동작

// 2. 구조체(사용자 정의 타입)의 대입 (가능)
struct Point { int x; int y; };
struct Point p1 = {1, 2};
struct Point p2;
p2 = p1; // 정상 동작 (값 복사됨)

// 3. 내장 배열의 대입 (불가능 - 예외 발생!)
int arr1[3] = {1, 2, 3};
int arr2[3];
arr2 = arr1; // 컴파일 에러 발생!
```

> 높은 직교성의 예시 (`Javascript`)

```js
// 숫자 데이터를 다루는 방식
const num = 10;                // 변수에 할당
const numList = [10, 20, 30];  // 배열의 요소로 사용
function returnNum() { return 10; } // 함수의 반환값으로 사용

// 함수를 다루는 방식 (숫자와 완전히 동일함 - 직교성 높음)
const sayHello = function() { console.log("Hello"); }; // 변수에 할당
const funcList = [sayHello, Math.max];                 // 배열의 요소로 사용
function returnFunc() { return sayHello; }             // 함수의 반환값으로 사용
```

**Language features: 응용 분야 지원**
필요한 기능을 지원하고, 없다면 만들 수 있음

**Support for abstraction: 추상화 지원**
Algorithms + Data Structures = Programs

Algorithm $\rarr$ Control Abstraction
Data Structure $\rarr$ Data Abstraction

**Ease of verification: 테스트 용이성**

**Programming environment**
잘 정리된 문서와 개발 환경, 테스트 도구가 있음

**Program portability**
지원하는 플랫폼이 다양해야함

**Cost of use**
PL Cost $\Rarr$ 프로그래밍 언어를 이용하여 프로그램을 개발하고 관리하는 데 드는 비용

- cost of program execution (실행 비용)
- cost of program translation (번역 비용)
- cost of program creation (개발 비용)
- cost of program maintenance (유지보수 비용)

과거에는 컴퓨터가 비쌌음 $\rarr$ 실행 비용 중요도 $\uarr$
현대는 컴퓨터가 비교적 쌈 $\rarr$ 개발 비용, 유지 비용 중요도 $\uarr$

### Programming Paradigm

paradigm $\Rarr$ 한 시대를 지배하는 총체적인 틀 또는 개념

programming paradigm $\Rarr$ 문제 해결을 위한 범용적 모델

계산 모델과 프로그래밍 패러다임은 밀접한 관계가 있지만, **정확히 일대일 대응하지 않음**

![](https://velog.velcdn.com/images/kmwook/post/d973de2d-4e46-418d-b6bb-69b9f19af994/image.png)

\* 객체 지향 패러다임은 대부분 명령형 언어로 지원하지만, 함수형 언어로도 지원 가능함

**Imperative/Procedural Language**

- 계산 모델: state transition machine
	
    - 입력은 초기 상태에 있고 연속된 전이 끝에 최종 상태에 원하는 출력이 있음
    
- 특징
	
    - 상태를 변경하는 명령문 중심
    - 구문: s1; s2; s3;
    - 예) FORTRAN, COBOL, C, Pascal, ...

**Functional/Applicative Language**

- 계산 모델: 입력 값을 받아서 출력 값을 반환하는 함수
	
    - 출력값과 입력값은 연관성 X
    
- 특징
	
    - 함수 합성(function composition) 중심
    - 자신을 자신에 합성 $\rarr$ 재귀 함수
    - 구문: P1(P2(P3(X)))
	- 예) LISP, Scheme, ML, Haskell

**Logic/Rule-Based Language**

- 계산 모델: 논리 규칙에 입각한 추론
	
    - 입력: 명제의 조합 
    - 출력: 추론 결과 얻은 명제 또는 명제의 일부

- 특징
	
    - 문제의 특성을 논리 규칙으로 설정하는 것이 주요 작업
    - 구문: 'Goal $\larr$ Hypotheses' 목록
    - 예) Prolog

**Object Oriented Language**

- 계산 모델: 객체(Object)
	
    - 특정 계산 모델을 가정하지는 않음
    - 주로 명령형 언어에 구현됨

- 특징
	
    - 유일한 identity를 갖는 객체들로 프로그램 구성
    - 객체 = 속성(property) + 행동(behavior)
    - 속성 $\rarr$ data
    - 행동 $\rarr$ method
    - 클래스의 실체(instance) = 객체
    - 클래스는 IS-A 관계를 통해 계층을 이룸
    - 예) Smalltalk, C++, Java

### Structed Programming

프로그램의 제어 흐름을 체계적으로 구조화하는 프로그래밍 패러다임

**등장 배경**

무분별한 `GOTO`문 사용 $\rarr$ 실행 흐름 복잡해짐

**이론적 기반**

- 흐름 제어 구조(Böhm-Jacopini Theorem)

    - 순차 구조(sequence structure)
    - 선택 구조(selection structure)
    - 반복 구조(repetition structure)
- 하향식 설계(top-down design) 방법
- 프라임 프로그램(prime program): Single Entry Single Exit

    - 모든 제어 구조는 시작 지점과 끝나는 지점이 하나여야 함

### Language Standard

- Standard: Document

    - 담당 기구: ISO, IEEE, ANSI

- Implementation: Compiler, Interpreter

### Programming Environment

프로그래밍 작성, 테스트에 사용되는 환경
프로그래밍 환경 $\neq$ 수행 환경

**분리 컴파일(seperate compilation)**
하나의 거대한 프로그램 $\rarr$ 여러 개의 소스 코드
독립적으로 컴파일 $\rarr$ link $\rarr$ 실행 파일

분리 컴파일을 지원하기 위해서는

1. 필요한 것 다시 선언 가능하도록 해야함 $\rarr$ 독립 컴파일
2. 특정 순서로 컴파일되도록 해야함(specification이 먼저 오도록)
3. 관련 정보를 라이브러리 형태로 참조 가능해야함

**테스트 및 디버깅(test and debugging)**

지원 방법

1. 실행 순서 따라가기(execution trace)
2. 중단점(breakpoint) 설정

    - 수행 순서가 명확한 명령형 언어에서 사용

3. 조건 검사(assertion)

    - 프로그램 수행 도중 만족해야할 조건 검사
    - 배포 버전에는 제거됨

---
\<Reference\>
- Pratt, T. W., & Zelkowitz, M. V. (2001). Programming Languages: Design and Implementation (4th ed.). Prentice Hall.