## Activity

### Component

안드로이드 아키텍처의 가장 중요한 요소이자 앱의 구성 단위
앱 = 여러 컴포넌트의 조합

컴포넌트는 앱 내에서 독립적인 실행 단위이며, main 함수와 같이 애플리케이션의 **고정된 진입 지점이 따로 없음**

- 4대 컴포넌트

    - Activity: 화면을 구성하는 가장 기본적인 컴포넌트
    - Service: 화면(Activity)과 상관없이 백그라운드에서 동작
    - Broadcast Receiver: 시스템 이벤트를 수신하고 반응
    - Content Provider: 앱 사이에 데이터를 공유하기 위한 컴포넌트

### Intent

Component를 실행하기 위해 시스템에 전달하는 메시지
즉, 데이터를 담는 클래스

#### 동작

앱 컴포넌트 클래스는 시스템이 생성하고 실행하므로 개발자가 직접 객체를 생성하여 실행할 수 없음
대신 실행할 타겟 컴포넌트의 정보를 담은 **Intent 객체를 시스템에 전달(전송)** 하면, 시스템이 이를 해석하여 해당 컴포넌트를 실행함

**Intent 예제**
```kotlin
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val btn: Button = findViewById(R.id.btn)
        btn.setOnClickListener{
            val intent = Intent(this, SubActivit::class.java)
            startActivity(intent)
        }
    }
}
```

### Activity

Activity는 Manifest 파일에 등록해야함
Activity 하나당 `<activity>` 태그 하나로 등록함

#### Activity Life Cycle

Activity가 생성되어 소멸하기까지의 과정

- 상태

    - **활성** : Activity 화면이 출력되고 있고 사용자가 이벤트 발생 가능한 상태

        - onCreate(), onStart(), onResume()
    - **일시정지** : Activity 화면은 출력되고 있지만 사용자가 이벤트 발생 불가능한 상태

        - onPause()
    - **비활성** : Activity 화면이 출력되지 않는 상태

        - onStop()
    - **종료**

        - onDestroy()

#### 양방향 Activity

메인 Activity에서 서브 Activity로 데이터를 넘기고, 서브 Activity에서 작업을 마친 후 다시 메인 Activity로 결과 데이터를 돌려주는 과정

- 진행 과정

    - MainActivity: `putExtra()` 메소드로 Intent에 데이터 넣음
    - MainActivity: `startActivityForResult()` 메소드를 통해 인텐트를 전송하며 SubActivity 실행
    - SubActivity: `getExtra()` 메소드로 데이터 받음
    - SubActivity: 처리 후 리턴 값을 `putExtra()`
    - SubActivity: `setResult()`로 데이터 리턴 후 `finish()` 호출하여 종료
    - MainActivity: `onActivityResult()` 오버라이딩하여 `getExtra()`로 데이터 꺼내 사용함
