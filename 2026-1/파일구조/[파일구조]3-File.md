## File Organization

### File System

Physical Address $\leftrightarrow$ Logical Address

Disk Formatting = 디스크에 파일 시스템을 설치하는 작업

### i(index)-node

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

디렉토리도 데이터 블록에 저장된 파일로 취급

i-node를 위해 블록은 다음과 같이 구성됨

```
     +---------------+   -----------------------
    0|  Boot Block   |
     +---------------+     Reserved Block
    1|  Super Block  |
     +---------------+   -----------------------
    2|  i-node 1-40  |
     +---------------+
    3|  i-node 41-80 |     Given by formatting
     +---------------+
     |      ...      |
     +---------------+   -----------------------
     |  Data Block   |
     +---------------+
     |  Data Block   |
     +---------------+     User Space
     |      ...      |
     +---------------+
     |  Data Block   |
     +---------------+   -----------------------
```

> i-node 예제

```c
fd = open("/usr/lik/data.txt", O_RDONLY, 0);
Nbytes = read(fd, buf, 100);
```

**Step 1.** 루트 디렉토리(`/`) 부터 `lik` 디렉토리까지 i-node를 통해 찾아와 "data.txt"의 i-node를 찾음
**Step 2.** 파일 소유권과 접근 권한을 검사함
**Step 3.** OpenFileTable에 파일을 등록함
**Step 4.** 파일 소유권과 접근 권한을 검사함
**Step 5.** buf로 100 bytes 읽어옴

### File Organization

Record(Tuple) = $\sum$ Field
Block = $\sum$ Record
File = $\sum$ Block

### Fixed Size Record

레코드 내의 필드 개수와 각 필드의 크기가 고정된 구조
$n^{th}\ record\ address\ -\ (n-1) \times s_r$
하나의 레코드가 두 개의 블록에 걸쳐서 저장되는 것을 방지해야함
레코드를 저장하고 남은 블록의 공간은 버림

- 삭제 처리

    1. 미사용 공간을 빈 공간 리스트(Free Record List)로 관리
    2. 삭제된 공간을 빈 공간 리스트에 연결

### Variable Length Record

레코드 내의 필드 개수나 각 필드의 크기가 가변적인 구조

- 구현 방식

    - Delimiter

        - 파일 끝에 구분자를 저장함
        - 삽입, 삭제가 어려움
    - Slotted Page

        - 블록 시작 부분에 헤더를 둠
        - 헤더 안에 슬롯 디렉토리 저장
        (레코드 수, 빈 공간 끝 포인터, 각 레코드의 메타데이터 기록)
        - 블록 내에서 레코드들을 이동시켜 빈 공간 합치기 가능
