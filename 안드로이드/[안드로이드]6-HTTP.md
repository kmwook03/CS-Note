## Network & HTTP

### Coroutine

안드로이드의 **비동기 프로그래밍(동시성 프로그래밍)** 을 작성하기 위한 기능으로, Jetpack 라이브러리에 포함되어 있음

스레드 차단 없이 루틴 수행이 가능하며, 단일 스레드에서 여러 Coroutine을 수행할 수 있음

- **ANR 방지**
메인 스레드가 5초 이상 사용자 이벤트에 무반응할 때 발생하는 ANR(Application Not Responding) 에러를 방지
네트워크 요청 후 **대기하면서 다른 코루틴을 수행** 하다가 **응답이 오면 다시 원래 작업을 수행** 하는 방식으로 스레드 차단을 막음

- **Scope**
Coroutine의 실행 범위 지정 (Global/ViewModel/LifeCycle)

- **Context**

    - Main: 메인스레드 UI 갱신, Toast 등 가벼운 작업
    - IO: 네트워크 통신, 내부 DB 접근 등 백그라운드 작업
    - Default: 크기가 큰 변수나 필터링 등 무거운 연산 수행
    - Job: Coroutine에 할당할 인스턴스

        - Dispatcher.Main + Job()

- **Builder**

    - launch: 현재 스레드를 차단하지 않고 새 coroutine 실행
    - async: 수행 이후 결과값을 await()로 받음

### HTTP

- Volley
2013년 구글이 공개한 라이브러리로 쉬운 HTTP 통신 구현이 가능
서버에 요청을 보내는 `RequestQueue`와 결과를 받는 `XXXRequest` 객체로 구성

- Retrofit
스퀘어(Square)에서 개발한 라이브러리로 코드 가독성이 뛰어나고 동기/비동기 구현이 가능
Annotation 기반으로 서비스 인터페이스가 동작하며, JSON 데이터를 객체로 변환해 주는 DTO(Data Transfer Object), HTTP CRUD 메소드를 정의하는 Interface, 통신 인스턴스를 초기화하는 Builder로 구성
