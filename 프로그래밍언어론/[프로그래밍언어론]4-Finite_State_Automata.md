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

모든 NFA $M$은 DFA $M^{\prime}$으로 변환 가능
$$L(M)=L(M^{\prime})$$
NFA에서 갈 수 있는 모든 상태의 집합을 DFA의 상태로 간주하여 변환

![](https://velog.velcdn.com/images/kmwook/post/6ee6db0e-036c-44ac-ac7a-c96f149bd0b1/image.png)

