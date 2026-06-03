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

##### Select Algorithm

* **Linear Search**

    * 모든 블록 순차 스캔
    * 정렬 여부 관계없이 사용 가능
    * 디스크 I/O cost: $b_r$

        * 키 속성으로 정렬되어있다면 $b_r/2$
* **Primary Index Search**

    * 파일이 **키 기준으로 정렬되어** 있을 때 사용 가능
    * 인덱스를 사용해 시작점을 찾고 Sequential Scan 수행
    * 디스크 I/O cost: Index Access Cost + $\lceil N_{selected}/B_f \rceil$
* **Secondary Index Search**

    * 인덱스는 정렬되어 있으나 실제 레코드는 흩어져 있는 경우
    * 포인터를 따라 Random Access 발생
    * 디스크 I/O cost: Index Access Cost + 포인터마다 1회 I/O

**주요 쟁점: 선형 탐색 vs 인덱스 기반 탐색**
Secondary Index를 사용하더라도 레코드가 여러 블록에 분산되어있다면 Linear Scan이 더 나은 성능을 보일 수도 있다.
$\Rightarrow$ Clustering이 성능에 미치는 영향이 큼

##### Select : Complex Query

* Conjunction : $\sigma_{\theta_1 \wedge \theta_2 \wedge ... \wedge \theta_n}(r)$

    * 1개의 인덱스 사용

        * Step 1: $\theta_i$ 조건 select해서 메모리로 가져옴
        * Step 2: 메모리 버퍼에서 나머지 조건을 테스트
    * Multiple-key 인덱스 사용

        * 복합 속성 인덱스가 있다면 직접 탐색
    * Intersection of identifiers

        * Step 1: 각 조건의 Record Pointer 집합을 인덱스를 통해 구함
        * Step 2: 교집합(intersection) 연산 수행
        * Step 3: 파일에서 해당 레코드만 메모리로 가져옴

* Disjunction : $\sigma_{\theta_1 \vee \theta_2 \vee ... \vee \theta_n}(r)$

    * 각 조건 식별자 포인터를 구해 합집합(Union) 연산 수행 후 실제 데이터 읽어옴

#### Project ($\Pi_{attr}$)
> **특정 속성을 추출함**

(e.g.) Find Student\.name where score > 3.5
$\Pi_{name}(\sigma_{score>3.5}(Student))$

전체 스캔이 필요함

```
간단한 이해
Select: 행 추출
Project: 열 추출
```

#### Join ($\bowtie$)
> **두 개 이상의 Relation을 공통 속성 기준으로 Cartesian Product 함**

(e.g.)
Student(StudentName, AdvisorProfessorID, Department, Score)
Professor(ProfessorName, ProfessorID, Department)

$Student\bowtie_{AdvisorProfessorID = ProfessorID}Professor$

$= \sigma_{AdvisorProfessorID=ProfessorID}(Student\times Professor)$

##### Nested-Loop Join (NLJ)
인덱스가 없고 어떠한 join 조건에서도 적용 가능한 가장 단순한 형태의 loop join
메모리 버퍼가 매우 제한적일 때 사용되지만 디스크 접근 횟수가 극단적으로 높아 비효율 발생

$R \bowtie_\theta S$
```
for each tuple r in R do begin
    for each tuple s in S do begin
        test pair(r, s) to see if they satisfy the join condition θ
        if they do, add r*s to the result
    end
end
```
Outer Relation R의 각 튜플마다 Inner Relation S의 모든 튜플을 처음부터 끝까지 스캔하여 조건 검사

* worst case
    
    * $cost = n_r \times b_s + b_r$

##### Block Nested-Loop Join (BNLJ)
튜플 단위가 아닌 블록 단위로 메모리에 로드하여 루프를 도는 최적화 기법
디스크 I/O 병목 해결을 위해 고안됨

$R \bowtie_\theta S$
```
for each Block B_r of R do begin
    Get Block B_r
    for each Block B_s of S do begin
        Get Block B_s
        for each tuple r in B_r do begin
            for each tuple s in B_s do begin
                Check if (r, s) satisfy the join condition
                if they do, add r*s to the result
            end
        end
    end
end 
```
Outer block 하나를 메모리에 올리고 Inner block 하나를 올린 뒤 메모리 내부에서 튜플 간 cross-check를 수행하여 I/O 횟수를 줄임

* $cost = \lceil b_r/(M-2) \rceil \times b_s + b_r$

    * 즉, Outer 블록을 최대한 많이 버퍼에 올려두면 Inner Relation을 읽는 횟수를 크게 줄일 수 있음

##### Indexed Nested-Loop Join (INLJ)
Inner Relation의 join 속성에 인덱스가 존재할 때 사용할 수 있는 기법
equi-join 또는 natural join 시 파일 스캔을 인덱스 탐색으로 대체하여 검색 속도를 비약적으로 높임
조건에 맞지 않는 불필요한 Inner Relation 블록을 스캔하는 낭비를 없애기 위해 사용함
양쪽 모두 인덱스가 있다면 튜플 수가 적은 쪽을 Outer Relation으로 삼는 것이 유리함

```
for each Block B_r of R do begin
    Get Block B_r
    for each tuple t_r in B_r do begin
        Search Index(IDX, t_r key)
        if found, add t_r * t_s to the result
    end
end
```
Outer Relation R의 각 블록을 읽고 블록 내 튜플 $t_r$d의 키 값을 추출
해당 키 값을 이용해 Inner Relation S의 인덱스를 탐색하고 일치하는 튜플 $t_s$만 결과에 추가

* $cost = b_r + n_r \times c$  

    * $c$ : 인덱스를 순회하고 실제 일치 튜플을 메모리에 올리는 비용

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


