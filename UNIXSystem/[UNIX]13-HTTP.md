## HTTP Protocol
웹 브라우저(Client)와 웹 서버(Server) 간에 데이터를 주고 받기 위한 통신 프로토콜

Hyper **Text** Transfer Protocol $\rightarrow$ **Text** 기반
```
(주의) 이 설명은 HTTP/1.1까지만 통하는 설명임
HTTP/2 이후는 Binary Framing 기반
```
Request - Response 구조로 동작하며 HTML 문서 뿐만 아니라 다양한 형태의 데이터를 전송할 수 있다.

### Request
Client $\rightarrow$ Server
```
GET /index.html HTTP/1.1

-> HTTP/1.1 프로토콜을 사용하여 /index.html 파일을 보내라
```

* HTTP Method

    * `GET`: 데이터 요청
    * `POST`: 데이터 전송
    * `PUT`: 수정
    * `DELETE`: 삭제

### Response
Server $\rightarrow$ Client
```
HTTP/1.1 200 OK
Content-Type: text/html
...
```

* Status Code

    * `200 OK`: 요청이 성공적으로 처리됨
    * `404 Not Found`: 요청한 자원 찾을 수 없음
    * `500 Internal Server Error`: 서버 내부 오류로 인해 요청 처리 불가
    * ...

### 동작 과정
```
[요청: Client -> Server]
    Browser (Client) 
       | write() / send()
       ▼
  Client TCP Buffer 
       | ========== (Network) ==========▶ 
                                      Server TCP (Socket) Buffer
                                           | read() / recv()
                                           ▼
                                      Server Application (buffer[])

[응답: Server -> Client]
                                      Server Application (response[])
                                           | write() / send()
                                           ▼
                                      Server TCP (Socket) Buffer
  Client TCP Buffer  ◀==== (Network) ======= 
       | read() / recv()
       ▼
    Browser (Client)
```

### HTTP Server
#### fork 기반
클라이언트가 접속할 때마다 자식 프로세스를 생성하여 동시에 여러 사용자를 처리한다.

* 장점

    1. 메모리 독립에 의한 높은 안정성
    2. 메모리 독립에 의한 동기화에서의 자유

* 단점

    1. 높은 프로세스 생성 및 소멸 오버헤드
    2. 높은 context switching 오버헤드
    3. 메모리 독립에 의한 높은 메모리 소모

#### thread 기반
클라이언트가 접속할 때마다 pthread_create() 등을 통해 새로운 스레드를 생성하여 동시에 여러 사용자를 처리한다.
스레드끼리 Thread Stack을 제외한 메모리 영역을 공유한다.
`(주의) client_fd는 Heap에 저장해야함`

* 장점

    1. 메모리 공유에 의한 효율적인 자원 사용
    2. 빠른 context switching
    3. 쉬운 데이터 공유

* 단점

    1. 메모리 공유에 의한 취약한 안정성
    2. 메모리 공유에 의한 동기화 부담

그렇다면, thread 기반 서버는 자원 고갈에서 자유로운가?
**그렇지 않다**
thread-per-client로 사용자를 처리한다면?
10000명의 사용자 $\rightarrow$ 10000개의 스레드
$\Rightarrow$ stack memory 증가 + context switching 증가 + scheduler 부하

**Solution: thread pool**
Worker thread 8개만 고정하고 클라이언트 요청은 queue에 넣어 처리함

#### select 기반
여러 소켓을 동시에 감시하는 가장 오래된 I/O multiplexing 방식

```
            select
        ┌─────┴─────┐
        │     │     │
      소켓A  소켓B  소켓C
        │     │     │
       [ ]   [O]   [ ]
              │
       select가 B 반환함
```

`select()`가 중요한 이유

* thread 1개로 여러 socket 감시가 가능해졌다.
* $\Rightarrow$ 동시 처리 good

```
서버 흐름

    socket()
    bind()
    listen()
    FD_SET()
    select()
    accept()
    read()
    write()
```

```c
int select(
    int 		maxfdp1,    /* 최대 fd 번호 크기 */
    fd_set 	*readfds,   /* 읽기 상태 변화 감지할 소켓 지정 */
    fd_set 	*writefds,  /* 쓰기 상태 변화 감지할 소켓 지정 */
    fd_set 	*exceptfds, /* 예외 상태 변화 감지할 소켓 지정 */
    struct timeval *tvptr      /* select() 시스템 콜 대기 시간 */
);
```

* 중요한 특징
    
    * `select(maxfd + 1, ...)`
    * `[0, maxfd1]` 범위만큼 검사하기 때문에 최대 fd 번호 + 1로 설정한다.

* 한계

    * $O(n)$ 검사
    * fd 개수 제한
    * 매번 fd_set 복사(커널 $\leftrightarrow$ 유저 복사)


#### epoll 기반
리눅스의 고성능 I/O 이벤트 처리 시스템인 epoll을 활용하여 클라이언트 요청을 처리한다.

`Goal: 수천-수만 개 소켓을 적은 수의 thread/process로 처리하자`

* Why epoll?

    * fork(): 100,000 client $\rightarrow$ 100,000 fork
    * thread: 100,000 client $\rightarrow$ 100,000 thread
    * 공통된 문제

        * context switching $\uparrow$
        * 메모리 사용량 $\uparrow$
        * scheduler overhead

epoll을 사용하면 8개 정도의 thread만으로 100,000명의 client를 처리할 수 있다.

>`Key Idea` : **이벤트 기반 처리**
클라이언트가 접속하거나 데이터를 보낼 때만 깨어나서 해당 작업을 처리하자

감시해야할 소켓 목록을 커널이 직접 관리 $\rightarrow$ 상태 변화를 빠르게 감지

* 장점

    * 자원 효율성
    * context switching overhead 최소화
    * Scalability
* 단점

    * 구현 복잡성
    * CPU-bounded task에 치명적
    * OS 종속성 - 리눅스 이외에 사용 불가
        
        * Mac/BSD: `kqueue`
        * Windows: `IOCP`

* 핵심 함수

    * epoll_create1()
        
        * epoll instance 생성 $\rightarrow$ 커널 내부 event manager 생성
    * epol_ctl()

        * 이 socket 감시해줘
    * epol_wait()

        * 이벤트 발생하기 전까지 sleep
        * 발생하면 커널이 깨워줌

`HTTP 서버 구현 정리`

| 방식 | 특징 |
|-|-|
| select | 오래됨 |
| poll | fd 제한 감소 |
| epoll | 리눅스 고성능 |
| kqueue | BSD/macOS |
| IOCP | Windows |
