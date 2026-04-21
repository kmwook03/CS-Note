## Kotlin introduction

### Kotlin

JVM(Java Virtual Machine)에서 동작하는 프로그래밍 언어
2017년 구글에서 Android 공식 언어로 지정함
객체 지향과 함수형 프로그래밍 스타일 지원

#### 안정성

앱 비정상 종료의 원인이 되는 Null Pointer Exception을 완화하기 위한 **Null Safe** 지원

- Null Safe: 객체의 Null 상태를 컴파일러가 자동으로 해결

높은 안정성을 기반으로 앱의 알고리즘 파트를 구현함

```kt
package com.example.myapplication

class FirstClass constructor() {
    fun print() {
        println("Hello world")
    }
}

fun main(args : Array<String>) {
    var first_object : FirstClass = FirstClass()
    first_object.print()
}

```

#### 변수 선언

`val` : **불변** 타입 변수
`var` : **가변** 타입 변수

#### 함수 선언

```kt
fun <function_name>(<params>) : <return_type> {}
```

#### 컬렉션

**Collection Data Type** : 연관된 데이터를 하나의 변수로 관리하는 자료형

- 종류: `Array`, `List`, `Set`, `Map`
- 활용: 선언 & 초기화 -> 사용 -> 수정

**Array**

- `plus()` 함수: 선언한 배열에 값을 추가하여 새로운 배열을 만들어 반환함

**List**

- 읽기 전용: `List`
- 읽기쓰기 : `MutableList` + `add()`

```kt
var list1: Array<Int> = arrayOf(1, 2, 3, 4, 5, 6, 7, 8)
var list2: List<Int> = listOf(1, 2, 3, 4, 5, 6, 7, 8)
var list3: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5, 6, 7, 8)

list1 = list1.plus(9) // 1, 2, 3, 4, 5, 6, 7, 8, 9
list2 = list2.plus(9) // 1, 2, 3, 4, 5, 6, 7, 8, 9
list3.add(9) // 1, 2, 3, 4, 5, 6, 7, 8, 9
```

**fliter**
조건식으로 배열에서 원하는 요소 추출
필터 결과로 List 타입 배열 반환

- 조건식 결과가 참이면 결과 배열에 넣고 거짓이면 넣지 않음

```kt
var list1: Array<Int> = arrayOf(1, 2, 3, 4, 5, 6, 7, 8, 9)
val filtered_list1 = list1.filter{it%3==0} // 3, 6, 9
```

#### 조건문

`if-else`

```kt
if (ranking <= 5) idx = 0
else if (ranking <= 10) idx = 1
else if (rankint <= 15) idx = 2

// ...

```

`when`

```kotlin
// style 1
when (ranking / 5) {
    0 -> idx = 0
    1 -> idx = 1
    // ...
}

// style 2
when (ranking) {
    in 0 .. 5 -> idx = 0
    in 6 .. 10 ->idx = 1
    // ...
}
```

**`if-else`와 `when`의 차이** : `if-else`는 조건식으로 판별하고 `when`은 조건 값으로 판별함

#### 반복문

`for`
```kotlin
fun main() {
    var grade: Array<String>
    grade = arrayOf("A", "B", "C", "D", "F")

    for (i in grade) print(i + " ")

    for (i: Int in 1 .. 5) print(i) // 12345
    println()

    val len: Int = 5
    for (i in 1 .. len) print(i) // 12345
    println()

    for (i in 1 until len) print(i) // 1234 (len-1까지 증가함 주의)

    for (i: Int in 1 .. 5 step(2)) print(i) // 135
    println()

    val len: Int = 5
    for (i in 5 downTo 1) print(i) // 54321
    println()

    for (i in 5 downTo 1 step(2)) print(i) // 531
}
```
`for`와 `in`을 결합하여 간결한 코딩 가능

`while`
```kotlin
fun main() {
    var grade: Array<String>
    grade = arrayOf("A", "B", "C", "D", "F")
    var idx: Int = 0

    while (idx < grade.size) print(grade[idx++] + " ")
}
```

반복문은 주로 UI 위젯 배열에 대한 접근에 사용됨

#### 형 변환

```kotlin
fun main() {
    var a: Int = 2024
    println(a)
    var b: String = a.toString() // 정수 -> 문자열
    println(b)

    if (b is String) // is로 타입 검사
        print("b is String") // b는 문자열이 맞음
    else
        print("b is not String)
}
```

#### 흐름 제어

`break`: 해당 iteration을 종료하고 **반복문 탈출**
`continue` : 해당 iteration을 종료하고 **다음 iteration으로 진입**

#### 클래스

**클래스(Class)** : 동일한 속성과 메소드를 가진 데이터 구조의 정의

```kotlin
public class Grade constructor(val name: String, score: Int) {
    var score = score
    
    fun change_score(changed_score: Int) {
        score = changed_score
    }
    fun print_score() {
        println(score)
    }
}

fun main() {
    var Hong = Grade("Hong", 80) // Grade : {"Hong", 80}
    Hong.print_score() // 80
    Hong.change_score(95) // Grade : {"Hong", 95}
    Hong.print_score() // 95
}
```

생성자 이름은 클래스 이름과 동일하기 때문에 생략 가능

클래스 내부의 변수는 파라미터 선언과 내부 변수 선언 2가지 방법이 존재함

**클래스 상속** : 부모 클래스의 속성과 메소드 구성을 자식 클래스가 동일하게 물려 받음

```kotlin
// 부모 클래스는 open 한정자로 선언
open class Person(school: String) {
    var school = school
    open fun print_school() {
        println(school)
    }
}

public class Grade constructur(school: String, val name: String, score: Int):Person(school) {
    var score = score
    fun change_score(changed_score: Int) {
        score = changed_score
    }
    fun print_score() {
        println(score)
    }
}

fun main() {
    var Hong = Grade("Pusan Univ.", "Hong", 80) // Grade : {"Pusan Univ.", "Hong", 80}
    Hong.print_score() // 80
    Hong.change_score(95) // Grade : {"Pusan Univ.", "Hong", 95}
    Hong.print_score() // 95
    Hong.print_school() // Pusan Univ.
    // print_school은 Person의 메소드
    // Grade는 Person을 상속받았기 때문에 호출 가능
}
```

#### 함수형 프로그래밍

**순수 함수**

- 같은 인자에 대한 반환값이 항상 같아야 함
- 함수 외부의 영향을 받지 않아야 함

**순수 함수 사용의 장점**

- 입력과 내용을 분리
- 재사용성 향상
- 여러 함수와 조합 가능
- 병행 작업 안정성 높음
- 함수 값 예측 가능하여 디버깅 및 테스트 쉬움

**람다 함수**

- 익명 함수 기법
- 함수를 간단하게 정의

`val <func_name>:(<param_type>)->(<return_type>) = {<params>->(<function>)}`

```kotlin
val lambda:(Int,Int)->(Int) = {a:Int, b:Int->(a+b)}
print(labda(3,4)) // 7
```

**고차 함수**

- 다른 함수를 매개변수로 받거나 함수를 반환하는 함수

```kotlin
fun main() {
    fun high_order_function(a: Int, operation(Int, Int)->Int) {
        val result = operation(2, 3)
        println(result) // 5
    }

    high_order_function(1) {a, b -> a + b} // 함수 외부에서 매개변수 함수 정의
}
```

```kotlin
enum class Delivery {STANDARD, EXPEDITED}
class Order(val itemCount: Int)

fun getShippingCostCalulator(delivery: Delivery):(Order)->Double {
    if (delivery == Delivery.EXPEDITED) {
        return {order -> 6+2.1*order.itemCount}
    }
    return {order -> 61.2*order.itemCount}
}

fun main() {
    val calculator = getShippingCostCalculator(Delivery.EXPEDITED)
    println(calculator(Order(3))) // 12.3
}
```

#### 확장 함수 & 오버로딩 & 오버라이딩

**확장 함수**
클래스를 직접 수정할 수 없을 때 클래스 주변에 새로운 함수나 속성을 추가하여 클래스의 크기를 확장하는 함수

```kotlin
class Adder() {
    fun add(a: Int, b: Int): Int {
        return a + b
    }

    // overloading
    fun add(a: Int, b: Int, c: Int): Int {
        return a + b + c
    }
}

// 확장 함수
fun Adder.add(a: Int, b: Int, c: Int, d: Int): Int {
    return a + b + c + d
}
```

**오버로딩 vs. 오버라이딩**

- 오버로딩: 한 클래스 내에서 동일한 이름의 함수를 기능만 다르게하여 여러 개의 함수를 정의
- 오버라이딩: 부모 클래스의 메소드를 자식 클래스에서 재정의하여 사용

#### Null 안정성

NullPointerException에서 안전 보장
기본적으로 kotlin은 Null을 허용하지 않지만 자료형 뒤에 `?`를 붙여 예외적으로 허용 가능

- 세이프 콜: `?.`

    - 변수 값이 Null이면 뒤의 메소드는 실행 안함

- 엘비스 연산자: `?:`

    - 변수가 Null이면 오른쪽, 아니면 왼쪽 선택
    