# Functional Requirements

## Functional Requirements Analysis

```text
기능 요구사항
    ↓
Use Case Model
- Actor
- Use Case
- Association
- include / extend / generalization
    ↓
Use Case Specification
- Scenario List
- Precondition
- Postcondition
- Flow of Events
    ↓
설계·구현·테스트의 기준
```

Use Case Model: 시스템이 누구에게 어떤 기능을 제공하는지 표현
Use Case Specification: 각 기능이 어떤 조건에서 어떤 순서로 동작하는지 상세히 서술

### Use Case Model

#### Actor

시스템과 직접 상호작용하는 개발 범위 외부 엔티티가 수행하는 역할

Actor 대상:

* 사람: 사용자, 관리자, ...
* 하드웨어 장치: 센서, 제어기, ...
* 외부 시스템: 서버, ...
* 타이머
  
  * Timer Actor: 특정 시점이나 일정한 주기로 시작되는 기능의 Triggering Actor

주의할 점:

* Actor는 특정 사람이나 장치 자체보다 그 대상이 **수행하는 역할**
* 시스템 내부 컴포넌트는 Actor가 아님
* System Context Model의 External Entity와 일관되어야 함

#### Use Case

사용자 관점에서 시스템이 제공하는 **기능 단위**

* 시스템이 수행하는 일련의 동작
* 기본 동작과 변형된 시나리오
* Actor에게 가치 있는 관찰 가능한 결과

내부 처리 단계가 아닌 **사용자가 얻는 최종 결과를** 나타내야 함

(e.g.) `카드 판독`, `모터 제어` $\rightarrow$ `출금`, `목적지로 이동`

좋은 이름 기준

* Actor 관점에서 작성
* 시스템이 제공하는 궁극적인 결과 표현
* 동사를 포함한 간결한 구문
* 구체적이되 내부 구현은 드러내지 않음

Use Case를 병합해야 하는 경우

* 내부 처리 단계를 각각 UC로 만든 경우
* 동일 기능의 여러 시나리오인 경우
* 동일 Actor의 CRUD인 경우

Use Case를 분리해야 하는 경우

* 사용자에게 명확히 구분되는 기능인 경우
* 반드시 연속해서 수행되지 않는 독립 기능인 경우
* 다른 Actor가 시작하는 기능인 경우

#### Association

Actor와 Use Case 사이 실제 입출력 또는 통신 경로

Association이 있다는 것은

* Actor와 시스템 사이에 실제 상호작용이 있음
* Actor와 Use Case가 메시지를 보내거나 받을 수 있음
* 해당 Actor가 그 Use Case에 참여함

Association 방향은 데이터가 전달되는 방향이 아니라 해당 Actor와 Use Case 사이의 **최초 Interaction 방향으로** 결정함

잘못된 Association

* UC 사이의 일반 Association(순서 표현 목적 등)
* Actor 사이의 Association
  
  * Actor 간 상호작용은 시스템 기능이 아니므로 표현하지 않는게 원칙

Association 종류

* `include`: 여러 Use Case에서 반복되는 **공통 기능**
* `extend`: 일부 제품이나 환경에서만 제공되는 **추가 기능**

#### Generalization

Actor끼리 또는 UC 끼리 공통 특성을 상속 및 일반화
