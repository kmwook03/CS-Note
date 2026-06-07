## Firebase & Google Map

### Firebase

구글의 모바일 앱 개발을 위한 통합 개발 플랫폼
서버 기능을 함수 형태로 구현하는 Serverless 컴퓨팅을 가능하게 하며, 웹서버와 유사하게 데이터를 저장하고 조회할 수 있음

### Cloud Firestore

**NoSQL 데이터베이스** 로서 테이블과 행이 없고, **컬렉션(Collection)으로 정리되는 문서(Document)** 에 데이터를 저장

- key-value 쌍 저장

**데이터 저장**

- `CollectionReference` 객체 필요
- `FirebaseFirestore.getInstance()`를 사용해 접근
- 콜백 리스터(`addOnSuccessListener`, `addOnFailureListener`)로 결과 확인

**데이터 업데이트**

- `set()` : 문서 전체 덮어쓰기
- `update()` : 특정 필드 값만 업데이트
- `mapOf()` : 여러 필드 한 번에 변경

**데이터 불러오기**

- collection 지정 후 `get()` 호출
- 단일 문서를 가져오려면 `document()` 메서드에 식별값으로 문서 지정

```kotlin
val db: FirebaseFirestore = Firebaseirestore.getInstance()

val user = mapOf(
    "name" to "kkang",
    "email" to "a@a.com",
    "avg" to 10
)

val colRef: CollectionReference = db.collection("users")
val docRef: Task<DocumentReference> = colRef.add(user)
docRef.addOnSuccessListener { documentReference ->
    Log.d("kkang", "DocumentSnapshot added with ID : " + "${documentReferenceid}")
}
docRef.addOnFailureListener { e ->
    Log.w("kkang", "Error adding document", e)
}

val user2 = User("lee", "lee@a.com", 30, true, true)
db.collection("users")
    .document("ID01")
    .set(user2)

db.collection("users")
    .document("ID01")
    .update("email", "lee@b.com")

db.collection("users")
    .document("ID01")
    .update(mapOf(
        "name" to "lee01",
        "email" to "lee@c.com"
    ))

db.collection("users")
    .get()
    .addOnSuccessListener{ result -> 
        for (document in result) {
            Log.d( ... ) 
        }
    }
    .addOnFailureListener{ exception -> 
        Log.d( ... )
    }
```

### Google Map 

**위치 제공자**

- GPS: GPS 위성 이용
- Network: 이동 통신망 이용
- Wifi: 와이파이 이용
- Passive: 다른 앱에서 사용한 마지막 위치 정보 이용

사용자의 위치를 얻기 위해 `getSystemService(Context.LOCATION_SERVICE)`를 호출하여 `LocationManager`를 사용

`LocationManager`의 `getLastKnownLocation()` 메서드를 사용하면 `Location` 객체(정확도, 위도, 경도, 획득시간 포함)를 반환받을 수 있음
계속 위치를 가져와야 한다면 `LocationListener`를 이용

- 구글 위치 라이브러리
`FusedLocationProviderClient`(위치 정보 획득)와 `GoogleApiClient`(위치 제공자 준비 등 다양한 콜백 제공)를 핵심 요소로 사용