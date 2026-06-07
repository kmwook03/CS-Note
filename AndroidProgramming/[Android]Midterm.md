### 🚨 1. Android 운영체제 구조 (밑에서부터 위로 순서 암기)
**[출제 경향: 구조 계층 순서 및 특징 연결 문제]**
*   **Li**nux Kernel: 운영체제의 핵심, 하드웨어 제어 및 드라이버 제공.
*   **HAL** (Hardware Abstraction Layer): 프레임워크에서 하드웨어 기능을 이용할 수 있게 하는 표준 인터페이스.
*   **Na**tive Libraries: C/C++ 기반 라이브러리 (Webkit, Media Framework 등).
*   **A**ndroid Runtime (ART): 앱에 대한 전체 실행 주관 (5.0 이전의 Dalvik 역할).
*   **F**ramework: Java로 구현된 API 툴킷, 앱이 직접 사용하는 계층.

### 🚨 2. Android 4대 컴포넌트 빈칸 채우기
**[출제 경향: 각 컴포넌트의 역할 키워드 매칭]**
컴포넌트는 앱 내부의 독립적인 실행 단위입니다.
*   **A**ctivity (액티비티): 주로 **UI(화면)** 를 구성하고 담당.
*   **S**ervice (서비스): 화면에 표시되지 않고 **백그라운드**에서 실행 (네트워크 통신, 음원 재생 등).
*   **C**ontent Provider (콘텐츠 프로바이더): 다른 앱과 **데이터**를 공유/제공.
*   **B**roadcast Receiver (브로드캐스트 리시버): 시스템 **이벤트**(부팅, 배터리 방전 등) 발생 시 실행.

### 🚨 3. 액티비티 생명주기 (Lifecycle) 빈칸 채우기
**[출제 경향: 순서도 빈칸 및 상태 매칭]**
*   **생성 및 시작:** `onCreate()` ➔ `onStart()` ➔ `onResume()` (이후 앱 활성 상태).
*   **종료 및 숨김:** `onPause()` (일시정지) ➔ `onStop()` (비활성/완전가려짐) ➔ `onDestroy()` (완전 종료).
*   *주의:* 다른 Activity가 전면에 나오면 `onPause()`가, 시스템이 메모리를 요구하면 프로세스가 중지될 수 있습니다.

### 🚨 4. Intent & Button 동작 코드 채우기
**[출제 경향: 양방향 통신 흐름과 View 제어 코드 빈칸]**
**👉 암기 공식: 인텐트는 "Put - Start - Set - Finish - Get" / 버튼은 "Find - Listener"**
*   **양방향 Intent 흐름:**
    1.  **메인:** `putExtra()`로 데이터 담고 ➔ `startActivityForResult()`로 전송.
    2.  **서브:** `getExtra()`로 데이터 받고 ➔ 반환할 데이터 담아 `setResult()` ➔ `finish()`로 창 닫기.
    3.  **메인:** `onActivityResult()` 함수가 자동 실행되며 결과를 받음.
*   **Button 위젯 연결 및 동작:**
    1.  객체 연결: `findViewById<타입>(R.id.아이디명)`.
    2.  이벤트 실행: `setOnTouchListener` 또는 `setOnClickListener` 호출.
    3.  가시성 제어: `visibility` (VISIBLE: 보임, INVISIBLE: 영역 유지+안보임, GONE: 영역 삭제+안보임).

### 🚨 5. 위젯 배치 보고 레이아웃 이름 적기
**[출제 경향: 화면 구조 이미지나 XML 속성을 보고 Layout 종류 맞추기]**
**👉 암기 공식: "방향은 Linear, 기준은 Relative, 겹치면 Frame, 바둑판은 Grid"**
*   **LinearLayout (선형):** `orientation` (수평/수직) 속성이 필수이며, `layout_weight`(가중치)로 비율 여백을 채움.
*   **RelativeLayout (상대적):** 특정 뷰의 `id` 선언이 필수이며 이를 기준(`layout_toRightOf` 등)으로 정렬.
*   **FrameLayout (프레임):** 추가한 순서대로 위에 **겹쳐서** 배치됨. 코드에서 visibility를 조절해 특정 순간 하나만 보여줄 때 사용.
*   **GridLayout (그리드):** 행(`rowCount`)과 열(`columnCount`)로 테이블 화면 구성.

### 🚨 6. Coroutine (코루틴) 동작 과정
**[출제 경향: 스레드, ANR, 스코프/빌더 개념 주관식 또는 빈칸]**
**👉 암기 공식: "비동기 3대장 (Main/IO/Default)과 빌더 (launch/async)"**
*   **동작 원리:** 스레드 차단 없이 루틴 수행이 가능하며, 5초 이상 무응답 시 발생하는 **ANR(Application Not Responding) 에러를 방지**하는 비동기 프로그래밍 기술.
*   **Dispatcher (스레드 할당자):**
    *   `Main`: UI 갱신, Toast 등 가벼운 작업.
    *   `IO`: 네트워크 통신, DB 접근 등 백그라운드 작업.
    *   `Default`: 크기가 큰 변수나 필터링 등 무거운 연산.
*   **Builder:** `launch`(결과 반환 안함) vs `async`(이후 결과값을 `await()`로 반환받음).

### 🚨 7. 주어진 코드 보고 실행 결과 적기 (Kotlin 문법 위주)
**[출제 경향: 함정이 있는 반복문, 변수형, 고차함수 예측 (T/F형 포함)]**
*   **var vs val:** `val`은 불변(값 변경 불가, Java의 final과 비슷), `var`는 가변(값 변경 가능). val에 값을 재할당하는 코드가 있다면 "Error"가 정답입니다.
*   **반복문 범위 (매우 주의):**
    *   `1 .. 5`: 1부터 5까지 포함 (5회 반복).
    *   `1 until len`: len은 **포함하지 않음**.
    *   `5 downTo 1 step(2)`: 5부터 1까지 2씩 감소 (5, 3, 1).
*   **컬렉션 필터:** `list.filter { 조건식 }`을 거치면 결과가 참인 요소만 추출되어 **List 타입의 배열로 반환**됩니다.
*   **흐름 제어:** `break`는 반복 차수를 완전히 종료/탈출, `continue`는 해당 차수만 건너뛰고 다음 반복으로 진입.
*   **Null 안전성:** `?`가 붙으면 Null 허용. `?.`(세이프콜)은 Null이면 실행 안 함, `?:`(엘비스 연산자)는 Null일 경우 오른쪽 값을 선택.

### 💡 (보너스) 기타 라이브러리 및 T/F 대비용 핵심 문장
*   **Androidx:** 플랫폼 API의 호환성 문제를 해결하고 확장 기능을 제공하는 Jetpack의 대표 라이브러리. (Appcompat, Fragment, RecyclerView 등)
*   **RecyclerView 필수 요소:** ViewHolder, Adapter, LayoutManager.
*   **Cloud Firestore:** 테이블과 행이 없고, **컬렉션(Collection)** 으로 정리되는 **문서(Document)** 에 키-값 쌍으로 데이터가 저장되는 NoSQL.
