## Packet Delivery Procedure

```
TCP Protocol Layer

    +-------------+
    | Application |
    +-------------+
    |  Transport  | End-to-End  통신 지원(TCP)
    +-------------+
    |   Network   | 논리 주소 기반 데이터 전송(IP)
    +-------------+
    |  Data Link  | 물리 주소 기반 데이터 전송(MAC)
    +-------------+
    |  PHYsical   |
    +-------------+
```

Data link 레이어는 한 노드에서 다음 인접한 노드로 프레임을 전송하는 역할을 한다.
$\Rightarrow$ Node-to-Node Delivery

Network 레이어는 최초 출발지(Source)에서부터 최종 목적지(Destination)까지 패킷(Packet)이 누락 없이 배달되도록 보장한다.
$\Rightarrow$ Source-to-Destination Delivery

### Source-to-Destination Delivery
최종 목적지까지 가기 위해 데이터는 여러 중간 시스템(라우터 등)을 거치게 된다.

* Hop-to-hop delivery (노드 간 전달)

    Data Link 레이어와 Physical 레이어가 담당한다.
    바로 인접한 옆 장치로 데이터를 물리적으로 안전하게 넘겨주는 단위 작업이다.

* Source-to-Destination delivery (종단 간 전달)

    Network 레이어가 담당한다.
    수많은 hop-to-hop을 라우팅을 통해 논리적으로 연결하여 결과적으로 최초 출발지에서 최종 목적지까지  패킷이 전달될 수 있도록 최적의 경로를 찾아주는 역할을 한다.

### Network Address & Physical Address

* 출발지 노드

    * 네트워크 주소: A
    * 물리 주소: 10

* 목적지 노드

    * 네트워크 주소: P
    * 물리 주소: 95

우리는 물리적 경계(LAN)가 다른 두 장치 간에 데이터를 안전하게 전달해야 한다.

물리 주소는 오직 자신이 속한 로컬 네트워크 내에서만 효력을 가지기 때문에, 두 장치가 서로 다른 네트워크에 있을 때는 물리 주소 만으로는 데이터를 보낼 수 없다.

LAN의 경계를 넘어 데이터가 이동하려면 전 세계 어디서나 통용될 수 있는 범용 주소가 필요하다.
$\Rightarrow$ 논리 주소(`e.g.` IP 주소)

데이터 전송 중 패킷에 저장된 출발 논리 주소와 도착 논리 주소는 변경되지 않는다. 변경되는 것은 매 Hop 장치의 물리주소이다.

| 구분 | Network Address (논리 주소) | Physical Address (물리 주소) |
|-|-|-| 
| 예시 | IP 주소 | MAC 주소 |
| 담당 계층 | Network Layer (3계층) | Data Link Layer (2계층) |
| 전달 범위 | Source-to-Destination (종단 간 전달) | Node-to-Node / Hop-to-Hop (노드 간 전달) |
| 변경 여부 | 패킷 이동 중 변경되지 않음 (단, NAT 환경 제외) | 매 라우터(Hop)를 지날 때마다 변경됨 |

$\Rightarrow$ 라우터는 수신한 프레임의 Data Link 헤더를 벗겨내어(역캡슐화) 최종 IP 주소를 확인하고, 다음 경로(Hop)로 보내기 위해 새로운 물리 주소(MAC)를 씌워(캡슐화) 다시 전송한다.
