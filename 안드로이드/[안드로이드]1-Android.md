## Android introduction

### Android

Linux Kernel을 기반으로 제작된 모바일 운영체제
2008년에 google에서 출시하여 모바일 플랫폼 시장의 7-80%를 차지함

- 애플리케이션 개발 언어

    - Java
    - Kotlin

- 라이선스
    
    - Apache v2.0

- 특징

    - Open Source Software Stack

### OS Architecture

**Linux Kernel** : 운영체제의 핵심 기능 수행, 하드웨어 제어 및 드라이버 제공

**HAL(Hardware Abstraction Layer)** : 안드로이드 프레임워크에서 하드웨어 기능을 사용할 수 있도록 하는 표준 인터페이스

**Native Libraries** : C/C++ 라이브러리(Webkit, Media Framework 등) 제공

**Android Runtime (ART)** : 앱에 대한 실행 주관

**Android Framework** : Java로 구현된 API 프레임워크

**Apps** : Android OS에 기본적으로 설치되어있는 앱 + 사용자가 설치한 앱

### App Components

**4대 컴포넌트**

- **Activity** : 화면 구성, UI 담당

- **Service** : 화면에 표시되지 않는 백그라운드 작업 처리

- **Content Provider** : 앱 내의 데이터를 다른 앱에 제공하는 기능 표준화

- **Broadcast Receiver** : 시스템 이벤트 발생 시 실행

**실행 특징**

- 각 컴포넌트는 앱 내부의 독립적인 실행 단위임

- 새로운 컴포넌트 실행 시 안드로이드 시스템을 호출하여 실행함

- 실행 시점이 다양함

- 다른 애플리케이션을 라이브러리 처럼 이용 가능함

### Android Resource & Project Architecture

- **Android Resource** : 코드에서 사용되는 추가 파일과 정적인 콘텐츠

    - 독립적인 유지관리를 위해 코드에서 외부화하여 분리함

- Project Files Components

    - manifests (`AndroidManifest.xml`) : 앱 구성에 관한 필수 정보 포함
    - java : 소스 코드 파일(`Java`/`Kotlin`) 포함
    - res : 레이아웃, 문자열, 이미지 등 코드가 아닌 모든 리소스 포함
    - Gradle Scripts : 프로젝트 빌드 및 라이브러리 설정

### Develop Workflow

**Step 1. Setup**
Android studio 설치, 프로젝트 생성

**Step 2. Write**
Android studio에서 제공하는 도구와 기능을 활용하여 앱 작성

**Step 3. Build & Run**
디버그 가능한 APK 패키지로 프로젝트 빌드, 실행

**Step 4. Iterate (Debugging, Profiling, Test)**
버그 제거와 앱 성능 최적화에 중점을 두고 앱 수정

**Step 5. Publish**
앱 버전 관리, Android App Bundle 빌드, 키 서명과 같은 사항을 고려하여 앱 출시
