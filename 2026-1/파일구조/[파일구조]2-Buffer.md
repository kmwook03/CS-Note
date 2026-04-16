## I/O and Buffer

```
           +-------+
           |  CPU  |
           +-------+
               |
    +--------------------+
    | Main Memory        |
    | +----------------+ |
    | | Process Memory | |
    | +----------------+ |
    | +----------------+ |
    | |     Buffer     | <---- 블록 전송을 위한 임시 저장소
    | +----------------+ |
    +--------------------+
               |
    +--------------------+
    |  Secondary Memory  |
    +--------------------+
```

- Buffer: 데이터 청크를 전송하기 위한 임시 메모리

    - 1 Buffer는 여러 개의 블록
- Page: 디스크의 블록에 대응되는 버퍼의 한 조각

### Buffer Management: I/O Processing

> **Read(I)**

```
Scan Buffer
if Target is placed in Buffer
    Get Data
else
    if Buffer is full
        Evict a block in buffer to disk
        if Evicted block is dirty
            Write block in disk
    Load target block from disk to buffer
    Get Data
```

> **Write(O)**

```
Scan Buffer
if Target is placed in Buffer
    Write Data
else
    if Buffer is full
        Evict a block in buffer to disk
        if Evicted block is dirty
            Write block in disk
    Load target block from disk to buffer
    Write Data
```

### Buffer Management: Replacement Policy

**LRU(Least Recently Used)**

- 가장 오랫동안 사용안한 블록 교체
- 중첩 루프 조인(Nested loops join)이나 반복적인 순차 스캔(Sequential scans)과 같은 특정 질의 패턴에서는 오히려 매우 비효율적

**Prediction of future reference**

- 운영체제와 달리 데이터베이스 시스템은 사용자의 질의(Query) 구조를 분석하여 미래의 데이터 접근 패턴을 예측 가능

**Toss-immediate strategy**

- 특정 블록의 마지막 튜플(Tuple) 처리가 끝나는 즉시 해당 블록의 공간 해제

**MRU(Most Recently Used)**

- 현재 처리 중인 블록을 고정(Pin)시키고, 해당 블록의 마지막 튜플 처리가 끝나면 고정을 해제(Unpin)
- 해제된 블록은 '가장 최근에 사용된 블록'이 되어 다음 번 교체 1순위가 됨

- **Pinned Block**: 디스크로 다시 기록되거나 버퍼에서 교체되는 것이 허용되지 않는 메모리 블록
