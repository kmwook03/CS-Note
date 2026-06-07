## Jetpack

### Jetpack Library

구글에서 개발된 Android 앱 개발용 확장 라이브러리 모음
앱 개발에 필요한 권장 아키텍처를 제공

**Androidx** : Jetpack의 대표적인 라이브러리
플랫폼 API에서 제공하지 않는 다양한 기능 제공 (예: 스와이프 화면 전환)
플랫폼 API의 호환성 문제 해결 (예: 구버전에서 Toolbar 사용 불가 현상)

#### Appcompat
이전 버전의 안드로이드(Android 4.x 이상)에서도 최신 기능을 사용할 수 있도록 API 레벨 호환성을 해결해 주는 라이브러리

사용 시 build.gradle에 dependency를 추가하고, Activity 클래스가 AppCompatActivity를 상속받도록 작성

#### Fragment
액티비티처럼 동작하지만, 한 화면 내에서 여러 뷰로 분할하여 동작할 수 있게 해주는 객체
액티비티 클래스 구현의 복잡성을 해결하기 위해 사용

Fragment 클래스를 상속받아 정의하며, onCreateView에서 inflater.inflate를 통해 View를 생성

```kotlin
class OneFragment : Fragment() {
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ):View? {
        return inflater.inflate(R.layout.fragment_bind, container, false)
    }
}
```

#### RecyclerView
여러 가지 항목을 리스트 형태로 나열해 주는 뷰

- 구성 요소

    - ViewHolder: 항목에 필요한 뷰 객체

    - Adapter: 항목 구성 역할

    - LayoutManager: 항목을 가로/세로, 그리드 등 리스트 형태의 출력 방식으로 배치

    - ItemDecoration (옵션): 항목 간의 구분선 등 시각적 요소

#### ViewPager 
스와이프 이벤트(좌우 또는 상하)를 통해 화면 전환 기능 제공

- 구현 방식

    - RecyclerView.Adapter
    - FragmentStateAdapter

#### DrawerLayout
옆에서 스와이프를 통해 밀려 나오는 네비게이션 메뉴 기능
`DrawerLayout` 태그를 최상위 부모로 설정하고, 그 안에 메인 화면용 레이아웃과 드로어용 레이아웃(2개 이상)을 하위 태그로 선언하여 구현
