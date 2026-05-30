## Socket
소프트웨어로 작성된 통신 접속점으로 네트워크 응용 프로그램은 소켓을 통해 데이터를 송수신한다.

```
    +-------------+
    | Application |
    +-------------+ <-------------------- Socket
    |  Transport  | End-to-End  통신 지원(TCP)
    +-------------+
    |   Network   | 논리 주소 기반 데이터 전송(IP)
    +-------------+
    |  Data Link  | 물리 주소 기반 데이터 전송(MAC)
    +-------------+
    |  PHYsical   |
    +-------------+
```

### Socket Descriptor
UNIX는 모든 장치를 파일로 취급한다.
따라서 네트워크 접속을 위해 제공되는 소켓 역시 파일로 취급한다.
$\rightarrow$ 공통된 파일 인터페이스(file descriptor)를 사용함
(UNIX에서는 파일과 소켓이 Descriptor table을 공유한다.)

소켓을 개설하면 파일 기술자와 동일하기 Socket Descriptor가 리턴된다.
응용 프로그램에서 이 소켓을 통하여 목적지 호스트와 연결을 요구하거나 패킷을 송수신할 수 있다.

### Socket 통신에 필요한 데이터
1. 통신에 사용할 프로토콜(TCP 또는 UDP)

    * TCP: 연결형 서비스 (Stream)
    * UDP: 비연결형 서비스 (Datagram)
2. 자신의 IP 주소
3. 자신의 포트(Port) 번호

    * Port number: 컴퓨터에서 수행되는 응용 프로그램을 구분하는 고유 번호

        * 몇 포트는 예약되어 있음

            * 20, 21: FTP
            * 23: Telnet
            * 80: HTTP
            * ...
4. 상대방 IP 주소
5. 상대방 포트(Port) 번호


#### TCP vs. UDP

| | TCP | UDP |
|-|-|-|
| 서비스 타입 | SOCK_STREAM | SOCK_DGRAM |
| 연결성 | Connection-oriented | Connectionless |
| 신뢰성 | Reliable | Unreliable |
| 순서 보장 | O | X |
| 통신 형태 | 1:1 | 1:1, 1:N, N:M 등 |
| 장점 | 데이터 손실이나 순서 바뀜 없는 온전한 통신 보장 | 전송 속도 빠름 |
| 단점 | 전송 속도 다소 느림 | 데이터 유실 발생할 수 있음 |

### Socket Programming
#### 소켓 개설
```c
int socket(
    domain, /* 프로토콜 체계 */
    type, /* 서비스 타입 */
    protocol /* 소켓에 사용될 프로토콜 */
);
```

* 프로토콜 체계

    * PF_INET: 인터넷 시스템
    * PF_UNIX: UNIX 시스템
    * PF_NS: XEROX 네트워크 시스템

* 서비스 타입

    * SOCK_STREAM: 스트림 방식 $\rightarrow$ TCP
    * SOCK_DGRAM: 데이터그램 방식 $\rightarrow$ UDP

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd1, fd2, sd1, sd2;
    fd1 = open("/etc/passwd", O_RDONLY, 0);
    printf("/etc/passwd fd: %d\n", fd1);

    // Stream Socket Open
    sd1 = socket(PF_INET, SOCK_STREAM, 0);
    printf("stream socket sd: %d\n", sd1);

    // Datagram Socket Open
    sd2 = socket(PF_INET, SOCK_DGRAM, 0);
    printf("datagram socket sd: %d\n", sd2);

    fd2 = open("/etc/hosts", O_RDONLY, 0);
    printf("/etc/hosts fd: %d\n", fd2);

    close(fd1);
    close(fd2);
    close(sd1);
    close(sd2);
}
```

```bash
$ ./openSocket
/etc/passwd fd: 3
stream socket sd: 4
datagram socket sd: 5
/etc/hosts fd: 6
```

#### 소켓 주소 구조체

```
       sockaddr          sockaddr_in
    +-----------+       +-----------+
    |  sa_len   |       |  sin_len  |
    +-----------+       +-----------+
    | sa_family |       |  AF_INET  |
    +-----------+       +-----------+
    |           |       |  sin_port |
    |           |       +-----------+
    |  sa_data  |       |  sin_addr |
    |           |       +-----------+
    |           |       |  sin_zero |
    +-----------+       +-----------+
```
```c
struct in_addr {
    in_addr_t s_addr;   // 32-bit IPv4 address
                        // network byte ordered
};

struct sockaddr_in {
    uint8_t         sin_len;        // length of structure
    sa_family_t     sin_family;     // AF_INET
    in_port_t       sin_port;       // 16-bit TCP or UDP port number
    struct in_addr  sin_addr;       // 32-bit IPv4 address
    char            sin_zero[8];    // unused
};
```

#### 서버 동작 절차
* **step 1: 소켓 생성 (`socket()`)**

    * 서버 프로세스는 `socket()` 시스템 콜을 호출하여 소켓 개설
    * $\rightarrow$ socket descriptor 획득

* **step 2: 주소 바인딩 (`bind()`)**

    * 자신의 소켓 번호와 서버의 소켓 주소(IP, 포트 번호) 결합

* **step 3: 연결 요청 대기 (`listen()`)**

    * 클라이언트로부터 연결 요청을 기다리는 수동 대기 모드로 전환

* **step 4: 연결 수락 (`accept()`)**

    * 클라이언트로부터 연결 요청이 왔을 때 처리하기 위해 `accept()` 호출
    * 클라이언트가 `connect()` 시스템 콜을 호출하면 `accept()`에서 처리함

* **step 5: 데이터 송수신 (`send() / recv()`)**

    * 연결 성공 $\rightarrow$ 데이터 송수신

* **step 6: 종료**

    * 소켓 닫고 통신 종료

#### 클라이언트 동작 절차
* **step 1: 소켓 생성 (`socket()`)**

    * `socket()` 시스템 콜로 소켓 개설
    * 클라이언트는 `bind()` 호출이 필요 없는 이유
        
        * 서버에게 바로 연결 요청을 보내면 됨

* **step 2: 연결 요청 (`connect()`)**

    * 접속할 서버의 소켓 구조체를 만들어 `connect()`의 인자로 전달

* **step 3: 데이터 송수신 (`send() / recv()`)**

    * 연결 성공 $\rightarrow$ 데이터 송수신

* **step 4: 종료 (`close()`)**

    * 소켓 닫고 통신 종료

#### TCP 클라이언트 프로그램 작성 절차
```
        TCP Client
            |
            ▼
         socket()           # 소켓 개설
            |
            ▼
      sockaddr_in 구성      # 서버 IP 주소와 포트 번호 지정
            |
            ▼
         connect()         # 서버로 연결 요청
            |
            ▼
          send()           # 데이터 송수신
          recv()
            |
            ▼
         close()
```

`TCP echo client`
```c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_LEN 128
#define PORT 9000

int main(int argc, char *argv[]) {
    int s, n, len_in, len_out;
    struct sockaddr_in server_addr;
    char *haddr;
    char buf[BUF_LEN+1];
    if (argc != 2) {
        printf("Usage: %s ipaddress\n", argv[0]);
        return -1;
    }
    haddr = argv[1];
    // 1. 소켓 생성
    // PF_INET: IPv4 프로토콜을 사용하겠다
    // SOCK_STREAM: TCP를 사용하겠다
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("can't create socket\n");
        return -1;
    }
    // 2. 서버 주소 구조체 설정
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(PORT);

    // 3. 연결 시도
    if (connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("can't connect to server\n");
        return -1;
    }

    // 사용자 입력
    printf("input any string: ");
    if (fgets(buf, BUF_LEN, stdin)) {
        buf[BUF_LEN] = '\0';
        len_out = strlen(buf);
    } else {
        printf("fgets error\n");
        return -1;
    }

    // 4. 데이터 전송
    if (write(s, buf, len_out) < 0) {
        printf("write error\n");
        return -1;
    }
    // 5. 데이터 수신
    printf("Echoed string: ");
    for (len_in = 0; len_in < len_out; len_in += n) {
        if ((n = read(s, &buf[len_in], len_out - len_in)) < 0) {
            printf("read error\n");
            return -1;
        }
    }
    printf("%s", buf);
    // 소켓 닫기
    close(s);
    return 0;
}
```

#### TCP 서버 프로그램 작성 절차
```
        TCP Server
            |
            ▼
         socket()           # 소켓 개설
            |
            ▼
          bind()
            |
            ▼
         listen()
            |
            ▼
         accept()
            |
            ▼
          read()           # 데이터 송수신
        서비스 처리
         write()
            |
            ▼
         close()
```

`TCP echo server`
```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 128

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr, client_addr;
    int server_fd, client_fd;
    int len, len_out;
    int port;
    char buf[BUF_LEN+1];

    if (argc != 2) {
        printf("Usage: %s port\n", argv[0]);
        return -1;
    }
    // 포트 번호 설정
    port = atoi(argv[1]);

    // 1. 소켓 생성
    // PF_INET: IPv4 프로토콜 사용하겠다
    // SOCK_STREAM: TCP 사용하겠다
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("can't create socket\n");
        return -1;
    }

    // 2. 서버 소켓 주소 구조체 설정
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    // 3. 바인딩
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("can't bind to local address\n");
        return -1;
    }
    // 4. 연결 대기
    listen(server_fd, 5);

    // 5. 클라이언트 연결 수락 및 통신
    // 6. 완료 후 클라이언트 소켓 닫기
    while (1) {
        printf("Server: waiting for a connection...\n");
        len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
        if (client_fd < 0) {
            printf("accept error\n");
            return -1;
        }
        printf("Server: client connected\n");
        len_out = read(client_fd, buf, sizeof(buf));
        buf[len_out] = '\0';
        printf("Received string: %s\n", buf);
        write(client_fd, buf, len_out);
        close(client_fd);
    }
    // 7. 서버 소켓 닫기
    close(server_fd);
    return 0;
}
```


