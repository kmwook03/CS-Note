### Machine Architecture

>**Computer:** 
integrated set of algorithms and data structures capable of storing and executing programs.

프로그래밍 언어 관점에서 컴퓨터
$\Rightarrow$ 프로그램을 저장하고 실행할 수 있는 알고리즘과 자료 구조의 집합

**Major Components**

- **Data**: 자료와 자료구조
	
    - 프로그램이 조작하고 상태를 저장하는 대상
    - (구현) `int`, `float`, `char`, ...
    
- **Primitive Operations**: 기본 연산
	
    - 더 이상 쪼갤 수 없는 단위의 처리 명령
    - (구현) `+`, `-`, `*`, `/`, `AND`, `OR`, `=`, ...
    
- **Sequence Control**: 흐름 제어 메커니즘
	
    - 기본 연산들이 어떤 순서로 실행될지 결정
    - (구현) `조건문`, `반복문`, `함수 호출 및 반환`, `예외처리`, ...
    
- **Data Access**: 자료 제어 메커니즘
	
    - 연산에 필요한 데이터를 어떻게 찾고 접근하는가
    - (구현) `스코프`, `바인딩`, `포인터`, `참조`, ...
    
- **Storage Management**: 메모리 할당 제어
	
    - 프로그램 실행 중에 데이터와 코드가 로드될 메모리 공간을 어떻게 확보하고 해제할 것인가
    - (구현) `정적 할당`, `스택을 이용한 지역 변수 관리`, `힙을 이용한 동적 할당`, ...
    
- **Operating Environment**: 외부환경과 통신 메커니즘
	
    - OS, 사용자, 네트워크와 상호작용
    - (구현) `표준 입출력`, `파일 읽기/쓰기`, `네트워크 소켓 통신`, ...

위 구성 요소를 갖춘 컴퓨터의 Machine Cycle

![](https://velog.velcdn.com/images/kmwook/post/9c62c724-22f8-4dd4-b2e4-a621ab864b80/image.png)

**Firmware Computer**

- 이론적 기반

    정확하게 정의된 알고리즘 또는 자료구조는 하드웨어로 구현될 수 있다.

Firmware Computer = Hardware + microprogram

마이크로프로그램을 소프트웨어적으로 흉내내는 것 $\rightarrow$ 에뮬레이션(Emulation)

### Translator

고수준(High-level) 언어로 작성된 프로그램을 기계어(machine language) 설계에 관계 없이 컴퓨터에서 실행시키기 위한 방법

1. **Translation; Compilation**
	고급 언어로 작성된 프로그램을 실제 컴퓨터에서 동작하는 기계어로 변환하도록 설계
    
2. **Software simulation; Interpretation**
	다른 컴퓨터에서 실행되는 프로그램을 이용하여 동작(simulate)시킴

전형적인 언어 구현 구조

![](https://velog.velcdn.com/images/kmwook/post/5c4c44d5-4783-47ed-96bf-17649a5a5e72/image.png)

프로그래밍 언어를 구현할 때 컴퓨터의 정의
$\Rarr $프로그램 실행 시에 사용하는 **알고리즘과 자료구조**

언어 구현에 의하여 정의된 컴퓨터: **virtual computer**
virtual computer의 기계어 $\rightarrow$ 언어 번역기에 의해 실행 가능한 프로그램

$\Rightarrow$ **구현된 프로그래밍 언어는 그 자체로 virtual computer**

virtual computer 관점에서 다음의 이유로 언어 구현에 차이가 생길 수 있다.

1. virtual computer에 대한 개념적 차이
언어가 제공해야 할 virtual computer를 구현자마다 다르게 이해할 수 있음
2. 구현 플랫폼 차이
언어가 구현될 하드웨어 플랫폼이 다를 경우 하드웨어에서 지원하는 기능 차이로 인해 언어 구현이 달라질 수 있음
3. 구현 방법 차이
언어가 구현될 하드웨어가 같더라도 언어 기능 제공을 위한 구현 방법이 다를 수 있음

**바인딩(Binding)**
프로그램 구성 요소(program constructs)와 속성(properties)의 묶음

- 바인딩 시각

    1. 언어 정의 시점 (Language definition)
    2. 언어 구현 시점 (Language implementation)
    3. 프로그램 번역 시점 (Compile time)
    4. 링크 시점 (Link edit)
    5. 로드 시점 (Load)
    6. 프로그램 수행 시점 (Run time)

바인딩 시각은 정확한 정보량과 관련이 있다.
- Static Binding (Early Binding): 1 ~ 5
	
    - 번역 전에 파악 가능한 정보가 많음
    - 실행 파일 효율 향상을 위한 번역 가능
    - Compilation 방법과 궁합 좋음

- Dynamic Binding (Late Binding): 6
	
    - 프로그래머의 선택의 중요성이 높아짐
    - 유연한 프로그래밍 가능
    - Interpretation 방법과 궁합 좋음

---

\<References>

- Pratt, T. W., & Zelkowitz, M. V. (2001). Programming Languages: Design and Implementation (4th ed.). Prentice Hall.
