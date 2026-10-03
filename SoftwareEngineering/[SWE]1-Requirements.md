# Software Requirement Analysis intro

## Software Dev Process

1. 이해관계자(Stakeholder)가 요구사항을 말함.
2. 요구분석(Requirement Analysis)을 거쳐 Software Requirements Specification(SRS)을 작성함.
3. 요구 검증 및 확인(Verification & Validation, V&V)
4. 모델을 설계(Design)함.
5. 구현(Implementation) 후 제품(Product or System)을 출시함.

Stakeholder의 요구사항은 대체로 모호하기 때문에 요구분석이 중요함.

### Requirement Analysis

시스템은 상호작용하는 External Entity가 존재함.

* Interface requirements: 시스템과 External Entity간 입출력에 대한 요구사항.
  * 이름, 목적, 유형, 데이터 형식, 유효 범위, 정확도, 허용 오차, 측정 단위, 타이밍, 다른 입출력과 관계
* Functional requirements: 시스템에 주어진 입력에 따른 동작(기능) 요구사항.

  * Usecase Model: 액터(Actor)와 각 Usecase의 관계를 나타내는 다이어그램
* Quality requirements: 성능, 보안, 안정성, 가용성 등 시스템 품질 요구사항.
* Constraints: 시스템 개발 중 비즈니스적인 또는 기술적인 제한 사항.

  * Technical Constraint
  * Business Constraint

#### ISO/IEC 25010 System and Software Quality Model

* Functional Suitability: 필요한 기능의 완전성, 정확성

  * Functional Completeness, Correctness, Appropriateness
* Performance Efficiency: 시간, 자원, 처리용량

  * Time behavior, Resource Utilization, Capacity
* Compatibility: 다른 시스템과 공존, 연동

  * Co-Existence Interoperability
* Usability: 배우고 조작하기 쉬운 정도

  * Appropriateness recognizability, Learnability, Operability, User error protection, User interface aesthetics, Accessibility
* Reliability: 장애 상황에서 서비스 유지

  * Maturity, Fault Tolerance, Availability, Recoverability
* Security: 인증, 무결성, 기밀성 등

  * Confidentiality, Integrity, Non-repudiation, Accountability, Authenticity
* Maintain Ability: 분석, 수정, 시험 용이성

  * Modularity, Reusability, Analyzability, Modifiability, Testability
* Portability: 다른 환경으로 이식 가능성

  * Adaptability, Installability, Replaceability

#### QA Scenario

1. Source: 자극 발생 주체
2. Stimulus: 발생한 사건이나 요청
3. Artifact: 영향 받는 시스템 또는 구성 요소
4. Environment: 사건 발생 조건
5. Response: 시스템 반응
6. Response Measure: 반응 평가 측정 기준

### Requirement vs Design

```text
Requirement = WHAT
Design      = HOW
```

* 요구사항

  * 외부에서 관찰 가능한 동작
  * 필요한 기능과 품질
  * 달성해야할 결과

* 설계

  * 내부 구조, 컴포넌트
  * 알고리즘, 데이터 저장 방법
  * 계층 구조
  * 구체적인 구현 기술

### Requirements Specification

좋은 요구사항 명세의 조건

* 명확성: 한 가지 의미로만 해석될 것
* 정확성: 실제 이해관계자의 요구를 정확히 반영할 것
* 완전성: 필요한 조건, 예외, 동작이 누락되지 않을 것
* 일관성: 다른 요구사항과 충돌이 없을 것
* 필요성: 비즈니스 또는 시스템 목적 상 필요할 것
* 구현가능성: 기술, 일정, 비용, 규제상 실현 가능할 것
* 검증가능성: 충족 여부를 시험하거나 측정 가능할 것
* 추적가능성: 설계, 구현, 테스트 산출물까지 연결될 것

#### 서술 방법

```text
[Condition] 조건
[Subject] 주체
[Action] 수행해야 하는 행동
[Constraint of Action] 행동의 범위·시간·순서·정확도

(e.g.)
호출 요청이 수신되면,
시스템은
운행 가능한 엘리베이터를 선정하고
2초 이내에 선정 결과를 관리자 화면에 표시해야 한다.
```

* 요구사항의 주체를 명시
* 능동태를 사용
* 요구되는 동작을 긍정문으로 작성
* 중요도에 맞는 표현을 일관되게 사용
* 조건과 측정 기준을 포함
* 하나의 문장에 과도하게 많은 요구를 섞지 않음

보다 구체적(Concrete)이고 세부적(Specific)으로 작성해야한다.
