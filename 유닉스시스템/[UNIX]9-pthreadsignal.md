## Signal

### Mutex Sharing among process
UNIX에서 mutex는 기본적으로 프로세스 간 공유가 안된다.
하지만 mutex를 공유 메모리(shm, mmap)에 위치시키면 가능하다.

### pthread signal
> signal: OS가 프로세스에 보내는 비동기적인 알림(소프트웨어 인터럽트)

시그널은 비동기적으로 스레드의 실행 흐름을 끊고 실행되기 때문에 thread-safe 하지 못한 방식이다.

`위험한 시그널 핸들러 예제`
```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void handler(int sig) {
    pthread_mutex_lock(&lock);
    printf("handler\n");
    pthread_mutex_unlock(&lock);
}

int main() {
    signal(SIGINT, handler); // SIGINT의 핸들러로 handler 지정
    while(1) {
        pthread_mutex_lock(&lock); // main이 lock 잡음
        printf("main working...\n");
        sleep(1000); // 이 때 SIGINT가 들어오면?
        pthread_mutex_unlock(&lock);
    }
    return 0;
}
```

main이 sleep 중에 SIGINT가 들어오면, handler()가 실행된다.
이 때 handler 함수는 lock을 요청하게 되는데 이미 main이 lock을 잡고 있으므로 얻을 수 없어 handler는 대기한다.
$\rightarrow$ DEADLOCK 발생

#### 안전한 시그널 사용
```c
pthread_sigmask(SIG_BLOCK, &set, NULL);
```
block할 시그널을 설정하는 함수

```c
sigwait()
```
현재 스레드에서 block된 시그널을 동기적으로 기다렸다가 반환하는 함수
$\rightarrow$ block된 시그널만 처리한다.

```
        signal 발생
            |
            ▼
         block 됨
            |
            ▼
    pending queue에 저장
            |
            ▼
    sigwait()가 꺼내서 처리  
```
또한 sigwait()는 핸들러를 우회하기 때문에 signal()이나 sigaction()이 필요 없다.
단, block된 시그널이 없다면, sigwait()는 시그널을 받을 수 없다.
