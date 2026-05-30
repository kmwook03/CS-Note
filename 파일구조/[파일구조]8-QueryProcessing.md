## Query Processing

### Query

> **조건을 만족하는 레코드 검색 요청**

* Query 유형

    * Operators
    * Aggregate Query
    * Sorting

### Relational Operators

#### Selection ($\sigma_{cond}$)

> **조건을 만족하는 레코드들을 검색함**

(e.g.) Find Student where Student.score > 3.5
$\sigma_{score>3.5}(Student)$

Index 또는 Hash를 사용하여 검색

#### Project ($\Pi_{attr}$)

> **특정 속성을 추출함**

(e.g.) Find Student\.name where score > 3.5
$\Pi_{name}(\sigma_{score>3.5}(Student))$

전체 스캔이 필요함

#### Join ($\bowtie$)

> **두 개 이상의 Relation을 공통 속성 기준으로 Cartesian Product 함**

(e.g.)
Student(StudentName, AdvisorProfessorID, Department, Score)
Professor(ProfessorName, ProfessorID, Department)

$Student\bowtie_{AdvisorProfessorID = ProfessorID}Professor$

$= \sigma_{AdvisorProfessorID=ProfessorID}(Student\times Professor)$

### Relational Algebra

Operand: Table(Relation)
Operator: Relational Operator

(e.g.)
find Student\.Name
from Student, Professor
where Student.Score > 3.5 and Student.AdvisorProfessorID = Professor\.ID and Professor.Department = 'CSE'

$\Pi_{student.name}(\sigma_{score>3.5}(Student)\bowtie \sigma_{Department='CSE'}(Professor))$

### Query Processing

> **관계형 데이터베이스에서 사용자가 선언한 Declarative Query를 파일 시스템의 물리적 데이터 접근 연산으로 변환하고 실행하는 전체 과정**

**Mechanism**

1. Parsing and Translation
2. Optimization
3. Evaluation

```
      User Query (SQL)
           ↓
+-----------------------+
| Parser and Translator |  <-- 1. 문법 검사 및 관계 대수로 변환
+-----------------------+
           ↓ (Relational Algebra Expression)
+-----------------------+
|      Optimizer        |  <-- 2. Catalog(통계)를 참조하여 최저 비용의 QEP 선택
+-----------------------+
           ↓ (Query Execution Plan, QEP)
+-----------------------+
|   Evaluation Engine   |  <-- 3. 계획에 따라 데이터베이스(Disk) 접근 및 실행
+-----------------------+
           ↓
      Query Output
```

#### Parsing and Translation

> **사용자가 입력한 SQL 구문이 문법적으로 옳은지(Syntax check), 참조하는 Relation이 존재하는지 확인 후 이를 Relation Algebra로 변환하는 과정**

Parsing 과정에서 여러 개의 Relation algebra(Equivalent Expression)가 도출될 수 있음
변환된 Relation algebra에 구체적인 실행 알고리즘을 매핑한 것 $\rightarrow$ Query Execution Plan

#### Query Optimization

> **여러 개의 Equivalent QEP 중 Execution Cost가 가장 낮은 단 하나의 Plan을 선택하는 과정**

모든 QEP를 실제로 실행하고 비교하는 것은 물리적으로 불가능함 $\rightarrow$ 통계 기반 Cost Estimation 필수

$C = C_{index} + C_{data}$

* $C_{index}$ : 인덱스 접근 비용
* $C_{data}$ : 데이터 블록 검색 비용

**Selectivity Estimation**

> **특정 조건을 만족하는 레코드가 전체 중 차지하는 비율을 추정하는 기법**

* Parametric Method

    * 데이터가 가우시안 정규 분포 등을 따른다고 가정하고 수학적 모델로 계산함
* Non-Parametric Method

    * 히스토그램을 사용하여 실제 데이터 분포 구간(Bucket)별 빈도수를 저장함
    * 데이터 Skew 현상을 반영할 수 있어 현대 DBMS에서 널리 쓰임
    * Wavelet, Discrete Cosine 등을 통해 Smoothing 처리가 필요함
