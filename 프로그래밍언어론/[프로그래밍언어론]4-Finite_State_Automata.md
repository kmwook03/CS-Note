### Finite State Automata

Grammar $\rightarrow$ 언어 **생성기**
Automata $\rightarrow$ 언어 **인식기**

**Finite Automaton**: 유한 개의 상태로 문자열을 인식하는 자동 기계

- Finite State Machine의 일종
- 초기 상태($q_0$)로부터 시작하여 입력 기호를 보고 상태 전이
- 최종 상태($F$)에 도달하면 문자열 인식
- FA $M=(Q, \Sigma, \delta, q_0, F)$
- FA $M$이 인식하는 언어 $L(M)=\{w\ |\ \delta(q_0, w) \in F\}$

**Deterministic Finite Automata**
어떤 상태에서 입력 기호에 따라 전이될 수 있는 상태가 단 하나인 오토마타

**Nondeterministic Finite Automata**
어떤 상태에서 입력 기호에 따라 전이될 수 있는 상태가 여러 개인 오토마타
여러 경로 중에서 하나라도 최종 상태에 도달하면 문자열을 인식한 것으로 판별함

- 모든 DFA는 NFA의 일종임

모든 NFA $M$은 DFA $M^{\prime}$으로 변환 가능
$$L(M)=L(M^{\prime})$$

![](https://velog.velcdn.com/images/kmwook/post/6ee6db0e-036c-44ac-ac7a-c96f149bd0b1/image.png)

NFA에서 갈 수 있는 모든 상태의 집합을 DFA의 상태로 간주하여 변환함

1. 원본 NFA의 상태가 3개이므로 이를 조합해 만들 수 있는 DFA의 최대 상태 개수는 $2^3=8$ 개

2. 각 상태 집합에서 입력을 받았을 때 전이 방향은 합집합($\cup$) 연산으로 계산

3. 원본 NFA에서 $q_2$ 가 종결 상태였으므로 $q_2$ 를 포함하는 집합은 모두 종결 상태로 간주 

![](https://velog.velcdn.com/images/kmwook/post/104663a3-3abd-4497-9c86-d4e0226b358f/image.png)

4. 도달 불가능 상태 제거

![](https://velog.velcdn.com/images/kmwook/post/409cb18e-d5fb-4c8e-a212-03036bb21d50/image.png)
