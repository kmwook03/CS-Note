## File System

### UNIX File System

모든 주변 장치(터미널, 디스크, ...)도 파일로 취급한다!

### VFS(Virtual File System)

서로 다른 파일 시스템을 공통 인터페이스로 추상화하는 커널 계층

- suberblock: 파일 시스템 전체를 대표하는 구조체

    - 파일 시스템 타입
    - 블록 크기
    - i-node 개수
    - 전체 메타 데이터
    - 파일 시스템 마운트 시 생성

- i-node: 파일 자체를 표현하는 객체

    - 파일 크기
    - 권한
    - UID/GID
    - 디스크 블록에 위치
    - 파일 존재 시 생성

- dentry: 경로와 i-node를 연결하는 객체

    - 예: /home/usr/a.txt를 해당 파일의 i-node와 연결
    - 경로 탐색 성능을 위해 캐시됨
    - 경로 탐색 시 생성

- file: open() 시 생성되는 객체

    - 현재 파일 offset
    - 접근 모드
    - file_operations 포인터
    - file descriptor가 가리키는 것: struct file
    - open 시 생성


### i-node

파일에 대한 메타데이터를 저장하고 관리하는 자료구조

```
    i-node
    +------------+
    | Attributes |
    |------------|               +------------+
    |  Pointers  | ------------> | Data Block |
    +------------+               +------------+

* Attributes: 
  type, permission, ownership, last updated time, created time, ...
```

디스크에서 유지되는 i-node 정보와 메모리에서 유지되는 i-node 정보가 다름

- 디스크/메모리 모두 유지

    - 소유자 uid
    - 파일 유형
    - 접근 허가
    - 접근 시간
    - 링크 수
    - 파일 데이터 주소 목록
    - 파일 크기

- 메모리에서만 유지하는 정보

    - lock/unlock 정보
    - 파일을 포함하고 있는 파일 시스템 장치 번호
    - i-node 번호
    - 메모리 상의 다른 i-node에 대한 포인터
    - 참조 계수

\*주의\* 파일 이름은 저장하지 않음

### 디렉토리 구조

```
    disk block
    +-----------+------+-----------+-+-------+-------+
    |   i-node  |      | directory | | data  |  ...  |
    |   list    |      | block     | | block |       |
    +-----------+------+-----------+-+-------+-------+
    
    i-node list
    +---------+-----+-----------+-----+-----------+-----+
    | inode 0 | ... | inode 222 | ... | inode 432 | ... |
    +---------+-----+-----------+-----+-----------+-----+

    directory block
    +---------------+
    | 222 | .       |   <--- 현재 디렉토리
    | 122 | ..      |   <--- 상위 디렉토리
    | 333 | subdir1 |   <--- 하위 디렉토리1
    | 245 | subdir2 |   <--- 하위 디렉토리2
    | 432 | file 1  |   <--- 파일1
    +---------------+
```

### File table & File descriptor table

**File table**

- **시스템 전역에** 존재
- 구성요소

    - i-node 포인터
    - 파일 offset
    - 파일 상태 플래그
    - 참조 계수

**File descriptor table**

- **프로세스마다 독립적으로** 존재
- 구성요소

    - file table entry 포인터
    - 상태 플래그

```
    +----------+    +------------+    +--------+    +-------+
    | Proc A   |    | Kernel     |    | i-node |    | Data  |
    | fd table | -> | file table | -> | table  | -> | Block |
    +----------+    +------------+    +--------+    +-------+
```

### FILE I/O

UNIX file system function: `open`, `read`, `write`, `lseek`, `close`

위 함수들은 unbuffered I/O임
$\rightarrow$ system call 자주 발생
$\rightarrow$ 느릴 수 있음

**umask()**

- 기능: 파일 생성 시 적용할 마스크 값 설정
즉, 인자로 들어온 권한을 모두 거부
- 리턴: 기존의 마스크 값

- cmask: bitwise OR

    - S_IRUSR, S_IWUSR, S_IXUSR
    - S_IRGRP, S_IWGRP, S_IXGRP
    - S_IROTH, S_IWOTH, S_IXOTH

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    umask(0); // mask 값을 0으로 설정 -> 거부 권한 X
    if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0) {
        perror("Failed to create foo");
        exit(-1);
    }

    // 그룹 읽기, 쓰기/기타 사용자 읽기, 쓰기 거부
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0) {
        perror("Failed to create bar");
        exit(-1);
    }
    
    exit(0);
}
```

```bash
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ./umask 
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ umask
0022  # 기본 umask 값. 적용 시 0755(rwxr-xr-x)로 생성
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ls -al foo bar
-rw------- 1 kmwook kmwook 0 Apr 18 15:47 bar # 소유자 제외 모두 거부
-rw-rw-rw- 1 kmwook kmwook 0 Apr 18 15:47 foo # 모든 권한 요청 허가
```

**dup(), dup2()**

`int dup(int filedes)`

- 기능
    
    - 사용 중인 file descriptor 복사
    - 파일 테이블에서 해당 항목의 참조 계수 1 증가
    - fd 항목의 플래그(`FD_CLOEXEC`)는 초기값(0)으로 설정

`int dup2(int filedes, int filedes2)`

- 기능

    - dup2(fd, STDIN_FILENO): 표준 입력을 fd로 redirection
    - dup2(fd, STDOUT_FILENO): 표준 출력을 fd로 redirection
    - dup2(fd, STDERR_FILENO): 표준 에러를 fd로 redirection

- 리턴

    - `dup()`: 할당 가능한 가장 작은 fd 번호 리턴
    - `dup2()`: filedes2 리턴(fd2는 fd1의 파일 테이블 가리킴)

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1, fd2;

    // 3: testfile.txt
    fd1 = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    printf("Original file descriptor: %d\n", fd1);
    // 파일 디스크립터 복제
    // 4: testfile.txt
    fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("Failed to duplicate file descriptor");
        close(fd1);
        return EXIT_FAILURE;
    }
    printf("Duplicated file descriptor: %d\n", fd2);
    // fd1 -> testfile.txt
    // testfile.txt에 "Hello, World!\n"이 써짐
    write(fd1, "Hello, World!\n", 14);
    // fd2 -> testfile.txt
    // testfile.txt에 "This is a test.\n"이 써짐
    write(fd2, "This is a test.\n", 17);

    // fd1과 fd2가 파일 offset을 공유하기 때문에 append처럼 써짐

    // STDOUT_FILENO -> fd1 -> testfile.txt
    // 이제 터미널 출력이 testfile.txt에 출력됨
    dup2(fd1, STDOUT_FILENO);

    // testfile.txt에 써질 문자열
    printf("This will be written to the file instead of standard output.\n");
    close(fd1);
    close(fd2);
    return EXIT_SUCCESS;
}
```

```bash
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ./mydupTest 
Original file descriptor: 3
Duplicated file descriptor: 4
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ cat testfile.txt 
Hello, World!   # fd1으로 씀
This is a test. # fd2로 씀
This will be written to the file instead of standard output. # STDOUT으로 씀
```
