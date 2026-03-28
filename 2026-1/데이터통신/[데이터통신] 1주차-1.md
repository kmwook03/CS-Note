# 프로토콜 아키텍처 (Protocol Architecture)

## 핵심 컨셉 : Divide and Conquer with LAYERs -> Layered Architecture

API: 응용프로그램을 프로그래밍하기 위한 **인터페이스**

Problem -> Abstraction -> Generalization

**Abstraction(추상화)**
인터페이스(Interface)와 구현(Implementation)을 분리하라

### 큰 그림은 구현보다 인터페이스 정의에 있다.

**Protocol: 통신 규칙 집합**
각 레이어마다 프로토콜이 필요하므로 프로토콜은 계층적으로 존재한다 -> **Layered Protocol Architecture**

각 레이어는 오직 바로 아래 레이어에만 의존하여 동작한다.
즉, 각 레이어의 API는 바로 위 레이어에만 기능을 제공한다.

- Protocol Entity:
    
    - 특정한 프로토콜 계층을 구현하는 네트워크 노드 내부의 동적 요소
    - Peer Entity: 다른 시스템의 같은 계층에 존재하는 엔티티
    - SAP(Service Access Points): 상위 계층에 제공하는 인터페이스

- 통신 프로토콜의 집합 -> Stack 또는 Suite

    - 예: Internet Protocol Stack, TCP/IP Protocol Suite

- Key Elements of Protocol

    1. **Syntax** : 누가 무엇을 어디로 보내는가
    2. **Semantics** : 데이터가 어떤 의미를 가지는가
    3. **Timing** : 동기화와 흐름 제어

PDU(Protocol Data Unit): peer entity들 간에 전송되는 정보의 단일 단위
SDU(Service Data Unit): 프로토콜에 의해 서비스되는 페이로드, 타겟 데이터
PCI(Protocol Control Information): 프로토콜 헤더(Header)

**PDU = PCI + SDU**

```
* H : Header
                      +-------------------+
Layer 3               | H_n+1 |  SDU_n+1  |
                      +-------------------+
                +-----+-------------------+
Layer 2         | H_n | H_n+1 |  SDU_n+1  |
                +-----+-------------------+
        +-------+-----+-------------------+
Layer 1 | H_n-1 | H_n | H_n+1 |  SDU_n+1  |
        +-------+-----+-------------------+
```

### Standardized Protocol Architecture

- **TCP/IP protocol suite: De Facto Standard**
가장 많이 사용되는 사실상 표준
- **ISO OSI (Open System Interconnection) Reference Model: De Jure Standard**
ISO에서 개발된 국제 표준

**7-Layered Protocol Architecture by ISO OSI**
```
    +--------------+                      +--------------+
    | Application  |                      | Application  |
    +--------------+                      +--------------+
    | Presentation |                      | Presentation |
    +--------------+                      +--------------+
    | Session      |                      | Session      |
    +--------------+                      +--------------+
    | Transport    |                      | Transport    |
    +--------------+   +--------------+   +--------------+
    | Network      |   | Network      |   | Network      |
    +--------------+   +--------------+   +--------------+
    | Data Link    |   | Data Link    |   | Data Link    |
    +--------------+   +--------------+   +--------------+
    | PHYsical     | - | PHYsical     | - | PHYsical     |
    +--------------+   +--------------+   +--------------+
```

- **Physical - PHY**

    - 물리적 매체를 통한 비정형 비트 스트림 전송 담당
    - 물리 매체 접근을 위해 기계적, 전기적, 기능적, 절차적 특성을 다룬다.

- **Data Link**

    - 물리적 링크를 통해 신뢰할 수 있는 정보를 제공
    - 동기화, 오류 제어, 흐름 제어를 완료한 데이터 블럭을 제공한다.

- **Network**

    - Common Logic Layer
    - 시스템 연결에 사용되는 기술로부터 상위 계층에 독립성을 제공

- **Transport**

    - end system 간의 데이터 교환 담당
    - 데이터가 유실되지 않도록 오류 제어 및 흐름 제어 수행
    - 포트 번호를 통해 어떤 애플리케이션으로 전송할지 결정

- **Session**

    - 통신하는 두 시스템 간의 연결을 관리
    - 통신 중 연결이 끊어지지 않도록 동기화점을 설정하여 오류 발생 시 동기화점 부터 데이터를 다시 전송

- **Presentation**

    - 데이터 포맷과 인코딩
    - 데이터 압축
    - 암호화

- **Application**

    - 애플리케이션이 OSI 환경에 접근하기 위한 방법
    - 유저 인터페이스
