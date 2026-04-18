## Standard I/O Library

### Stream

Standard I/O Library를 사용한 FILE I/O에서는 파일 디스크립터(FILE Descriptor) 위에 씌운 **파일 스트림(FILE Stream)** 추상화를 사용

- Stream

    - 프로그램과 파일 사이의 자료 흐름에 대한 표현
    - 표준 입출력 함수는 stream을 매개로 파일에 접근

**FILE** : 하나의 스트림을 다루기 위한 정보를 포함한 구조체
스트림 개방(`fopen()`) -> `FILE` 구조체 포인터 반환
표준 입력/출력/에러도 FILE 포인터로 정의됨

### Buffering

사용 목적: read(), write() 호출 최소화

**Fully Buffered** : 버퍼가 꽉 찼을 때 Flush

- 첫 I/O를 수행하는 시점에 `malloc`으로 버퍼 할당
- 디스크 파일 입출력이 일반적으로 Fully Buffered

**Line Buffered** : 개행 문자(newline)를 만나면 Flush

- 터미널 입출력(`stdin`, `stdout`)은 Line Buffered

    - `stdin`, `stdout`이 터미널을 가리키지 않으면 Fully Buffered
- buffer size가 고정이기 때문에 newline이 없어도 buffer가 가득차면 Flush

**Unbuffered** : 버퍼 없이 바로 출력

- Standard I/O Library는 Unbuffered 상태일 때 character를 곧바로 커널로 전송함
- 표준 에러(`stderr`)는 Unbuffered

### Buffering Change

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char buf[1000] = {0};
    setbuf(stdout, buf);
    printf("Hello, ");
    sleep(1);
    printf("UNIX!\n");
    sleep(1);

    setbuf(stdout, NULL);
    printf("How ");
    sleep(1);
    printf("are ");
    sleep(1);
    printf("you?\n");
    return 0;
}
```

```
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ./setbufTestSleep 
Hello, UNIX!   <--- 2초 후 한 번에 출력됨
How are you?   <--- 1초 간격으로 하나씩 출력됨
```

`void setbuf(FILE *fp, char *buf)` : 버퍼 사용을 ON/OFF

- 버퍼를 사용하려면 `buf`가 특정 버퍼 공간을 가리키도록 해야함

    - (예) `char buf[1000] = {0}; setbuf(stdout, buf);`

### Open Stream

**FILE \*fopen(const char \*pathname, const char \*type)**
pathname 파일의 스트림을 열고 버퍼를 할당함
성공하면 `FILE*`, 실패하면 `NULL` 반환
FILE 구조체의 각 필드들을 초기화한 후 open() 호출

`type`
- "r", "rb" : O_RDONLY
- "w", "wb" : O_WRONLY | O_CREAT | O_TRUNC
- "a", "ab" : O_WRONLY | O_APPEND | O_CREAT
- "r+", "r+b", "rb+" : O_RDWR
- "w+", "w+b", "wb+" : O_RDWR | O_CREAT | O_TRUNC
- "a+", "a+b", "ab+" : O_RDWR | O_APPEND | O_CREAT

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;

    if ((fp = fopen("testfile.txt", "r")) == NULL) {
        perror("Failed to open file");
        exit(-1);
    }
    printf("Success!\n");
    printf("Opening \"testfile.txt\" in \"r\" mode!\n");
    fclose(fp);

    return 0;
}
```

```
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ./fopen 
Success!
Opening "testfile.txt" in "r" mode!
```

**FILE \*freopen(const char \*pathname, const char \*type, FILE \*fp)**
`fp`가 가리키는 스트림으로 파일 열기
성공하면 `FILE*`, 실패하면 `NULL` 반환

- `fp`는 일반적으로 `stdin`, `stdout`, `stderr` 등과 같이 미리 정의된 스트림

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char *fname = "testfile.txt";
    int fd;

    printf("First printf is on the screen.\n");
    if ((fd = freopen(fname, "w", stdout)) == NULL) {
        perror("Failed to open file");
        exit(-1);
    }
    printf("Second printf is in the file.\n");
    fclose(stdout);
    return 0;
}
```

```
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ./freopen 
First printf is on the screen.
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ cat testfile.txt 
Second printf is in the file.
```

**FILE \*fdopen(int filedes, const char \*type)**

이미 열려있는 파일 디스크립터에 대해 표준 입출력 스트림과 연결
`fopen()`으로 개방할 수 없는 파일에 대해서 수행

### Close Stream

**int fclose(FILE \*fp)**
`fp`가 가리키는 스트림과 파일 분리, 파일 닫음
성공하면 0, 실패하면 `EOF`(-1) 반환
출력 버퍼에 있는 모든 자료는 파일에 저장되고 입력 버퍼에 있는 모든 자료는 버려짐
이후 버퍼 해제

프로세스가 정상 종료한 경우 닫히지 않은 모든 표준 입출력 스트림에 fclose() 수행

### I/O Functions

**문자 단위**

- 입력
    
    - `getc()`, `fgetc()`, `getchar()`

        - 지정된 파일에서 한 문자를 읽어오는 함수
        - 성공하면 읽은 문자, 실패하거나 파일 끝이면 `EOF` 반환
        - 속도: `getc()` > `fgetc()` (매크로 > 함수)
        - `getchar()` == `getc(stdin)`
    - `ungetc()`

        - 지정된 문자를 스트림 맨 앞으로 반환
        - 성공하면 당긴 문자, 실패하면 `EOF` 반환
        - 조건 검사를 위해 하나의 문자를 읽은 후 원상태 복원을 위해 사용
    
- 출력
    
    - `putc()`, `fputc()`, `putchar()`

        - 지정된 파일에 한 문자를 쓰는 함수
        - 성공하면 쓴 문자, 실패하면 `EOF` 반환
        - 속도: `putc()` > `fputc()` (매크로 > 함수)
        - `putchar()` == `putc(c, stdout)`

**줄 단위**

- 입력

    - `fgets()`

        - 주어진 스트림으로부터 입력
        - `\n`이 나올 때 까지 입력 받아 `\n`까지 포함하여 버퍼에 저장
        - 문자열 길이가 n-1을 초과하면 n-1개만 돌려주고 나머지는 버퍼에 남아있음
        - 버퍼는 항상 `\0`로 끝남
    - `gets()`

        - gcc에서 사용하지 않도록 권장함 (C11 표준에서는 삭제됨)
        - 버퍼 영역을 넘어선 입력이 가능 -> 버퍼 오버플로우
        - `\n`을 버퍼에 저장하지 않음
- 출력
    
    - `fputs()`

        - `\0`로 끝나는 문자열을 `\0` 빼고 스트림에 씀
    - `puts()` 

        - `\0`로 끝나는 문자열을 `\0` 빼고 표준 출력에 씀
        - 표준 출력에 `\n`을 덧붙임
    

**이진(binary)**

구조체 전체를 읽거나 쓰려고 할 때

1. `getc()`, `putc()` 등을 사용
    
    구조체 전체를 순환하면서 한 문자씩 처리

2. `fgets()`, `fputs()` 등을 사용

    `fgets()` : 구조체 중간에 `\0` 문자나 `\n`이 있는 경우 처리 불가
    `fputs()` : 구조체 중간에 `\0` 문자가 있으면 처리 불가

즉, 원하는 크기 만큼의 데이터를 읽고 쓸 수 있는 함수가 필요함
$\Rightarrow$ Binary I/O

- 입력
    
    - `size_t fread(void *ptr, size_t size, size_t nobj, FILE *fp)`

        - 지정된 스트림에서 이진 구조체를 읽음
        - 입출력 객체 개수 반환

            - if (`ret` < `nobj`) `Error` or `EOF`

- 출력
    
    - `size_t fwrite(const void *ptr, size_t size, size_t nobj, FILE *fp)`

        - 지정된 스트림에 이진 구조체를 씀
        - 입출력 객체 개수 반환

- 인자 정리

    - ptr: 버퍼 공간
    - size: 객체 크기
    - nobj: 입출력 수행할 객체 수

```c
#include <stdio.h>

struct student {
    int sno;
    char name[10];
    int point;
};

int main() {
    struct student s1, s2;
    FILE *fp;

    if ((fp = fopen("student.dat", "w")) == NULL) {
        perror("Failed to open file");
        return -1;
    }
    printf("Input SNO >> ");
    scanf("%d", &s1.sno);
    printf("Input Name >> ");
    scanf("%s", s1.name); // Not recommended
    printf("Input Point >> ");
    scanf("%d", &s1.point);

    // 구조체를 binary로 씀
    if (fwrite(&s1, sizeof(struct student), 1, fp) != 1) {
        perror("Failed to write to file");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    if ((fp = fopen("student.dat", "r")) == NULL) {
        perror("Failed to open file");
        return -1;
    }

    // 구조체를 binary로 읽음
    if (fread(&s2, sizeof(struct student), 1, fp) != 1) {
        perror("Failed to read from file");
        fclose(fp);
        return -1;
    }

    printf("\n NO        Name      Point\n");
    printf("============================\n");
    printf(" %d        %s        %d\n", s2.sno, s2.name, s2.point);
    fclose(fp);
    return 0;
}

```
```
kmwook@kmwookgram:~/advUNIX/StandardIOTest$ ./binaryIO
Input SNO >> 20
Input Name >> Park
Input Point >> 90

 NO        Name      Point
============================
 20        Park        90
```

**포맷(formatted)**

- 입력: `scanf()`, `fscanf()`
- 출력: `printf()`, `fprintf()`
