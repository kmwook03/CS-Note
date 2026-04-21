## View

앱 실행화면에서 사용자가 인식하고 상호작용할 수 있는 요소들

실행화면: **View 구성 및 배치의 결과**

### View 종류

**Widget**

- 시각적인 요소
- ImageView, TextView, Button, ...

**ViewGroup**

- 영역적인 요소
- Layout, container, ...

### View 요소 배치

구조 표현 언어 **XML**로 수행됨

- 모든 View 요소는 태그 형태로 명시됨

    - `<시작태그>`~`</끝태그>` 또는 `<약식태그/>` 형태
- 모든 View 요소는 Layout 태그 내에 포함됨

    - 최상단 태그: 선언태그, Layout 태그

```xml
<?xml version="1.0" encoding="utf-8"?> <!--선언태그-->
<LinearLayout xmlns:android=
    "https://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical"
    android:weightSum="2"
    tools:context=".MainActivity">

    <LinearLayout 
        android:layout_weight="1"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:background="@color/purple_200"> <!--시작태그-->
        <Button
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:text="Button"/> <!--약식태그-->
    </LinearLayout> <!--끝태그-->
```

#### View 속성

View 요소에 부여하는 특징 및 참조 정보

- 속성 = "속성값"

**크기 속성은 필수임**

- match_parent: 상위 요소 공간 범위 참조
- wrap_content: 본인 및 하위 요소 텍스트 문자 크기 참조
- 지정 값: 값과 단위로 View 요소 크기 지정

    - widget: `dp`
    - text: `sp`

#### View 영역

- Contents, Padding, Margin

    View의 간격은 Padding과 Margin 속성으로 설정

- Padding: Widget 경계선으로부터 내부 요소가 멀어지도록
- Margin: Widget 경계선 밖으로 부모태그로부터 Widget이 멀어지도록

#### View 시각 표현

하나의 Layout에 여러 개의 View 배치 가능

- 색상: `android:backgroundTint`
- 회전: `android:rotation`
- 가시성: `android:visibility` (visible/invisible)
- 활성화: `android:enabled` (true/false)

### Widget

구성된 알고리즘을 시작하는 트리거 역할
터치 등으로 사용자와 상호작용

#### 연결 및 객체 생성

1. XML 태그에 `android:id`로 식별자 등록
2. kotlin에서 `lateinit var`로 객체 선언
3. `findViewById` 메소드를 호출하여 xml 태그와 kotlin 객체를 연결함

버튼 예제
```kotlin
btnAdd.setOnTouchListener{View, motionEvent ->
    num1 = edit1.text.toString()
    num2 = edit2.text.toString()
    result = Integer.pareInt(num1) + Integer.parseInt(num2)
    textResult.text = result.toString()
}
```

### Layout

View를 배치하는 클래스, 규칙

#### 종류

- LinearLayout: 선형 배치

    - `android:orientation = ` "horizontal" / "vertical"
    - `android:layout_weight = ` View 가중치 -> 각 컴포넌트 크기 조절
    - `android:gravity`, `android:layout_gravity`

        - 이 속성이 없으면 좌측 상단 배치가 디폴트
        - 값에 따라 영역 정렬
- RelativeLayout: 상대 위치 배치
- FrameLayout: 겹쳐서 배치

    - 추가한 순서대로 위에 겹쳐짐
    
- GridLayout: 표 형태 배치
- ConstraintLayout: 계층 구조 배치  
