### 1. 통신 기초 개념 (Basic Concepts)

*   **데이터(Data)와 신호(Signal):** 데이터는 의미나 정보를 담고 있는 개체이며, 신호는 이러한 데이터를 전기적 또는 전자기적으로 표현하여 전파하는 수단입니다.
*   **전송 매체(Transmission Medium):** 유선(Guided Media, 예: 꼬임쌍선, 동축케이블, 광섬유)과 무선(Unguided Media, 예: 공기, 바닷물)으로 나뉘며, 두 기기만 독점 사용하는 **점대점(Point-to-Point)** 방식과 다수가 공유하는 **브로드캐스트(Broadcast/Shared)** 방식으로 분류됩니다.
*   **디지털 전송의 장점 (Why Digital?):** 
    *   아날로그 전송은 신호 감쇠를 막기 위해 **증폭기(Amplifier)**를 사용하는데, 이때 노이즈(Noise)까지 함께 증폭되는 문제가 있습니다.
    *   반면 디지털 전송은 **리피터(Repeater)**를 사용하여 노이즈 없이 원래 신호를 **재생성(Regenerate)**하므로 데이터 무결성(Data Integrity)이 높습니다.
    *   또한 여러 신호를 쉽게 다중화(Multiplexing)할 수 있고, 압축(Compression) 및 암호화(Encryption) 적용이 용이합니다.

### 2. 아날로그 데이터를 디지털 신호로 변환 (Analog $\rightarrow$ Digital)

음성, 영상 같은 연속적인 아날로그 데이터를 컴퓨터가 처리할 수 있는 디지털 신호로 바꾸는 과정이며, 이 역할을 하는 장치를 **코덱(Codec, Coder/Decoder)**이라고 합니다. (적용 예: CD, DVD 오디오)

*   **PCM (Pulse Code Modulation):** 아날로그 신호를 디지털 비트 스트림으로 변환하는 대표적인 기술입니다. 다음 3단계를 거칩니다.
    1.  **표본화 (Sampling):** 연속적인 시간 축에서 일정한 간격($T_s$)으로 신호의 진폭을 측정하여 이산적인 값으로 만듭니다.
        *   **나이퀴스트 정리 (Nyquist Sampling Theorem):** 신호를 정보 손실 없이 완벽하게 복원하려면, 표본화 주파수($f_s$)가 신호의 최고 주파수($f_{max}$)의 **2배보다 커야 합니다 ($f_s > 2 \cdot f_{max}$)**. 이를 위반하면 **에일리어싱(Aliasing)**이라는 왜곡 현상이 발생합니다.
    2.  **양자화 (Quantization):** 샘플링된 진폭 값을 유한한 개수의 이산적인 레벨로 근사화합니다.
    3.  **부호화 (Encoding):** 양자화된 각 레벨을 고유한 이진 코드(Bit stream)로 변환합니다.

### 3. 디지털 데이터를 디지털 신호로 변환 (Digital $\rightarrow$ Digital)

컴퓨터 내부의 0과 1(디지털 데이터)을 전송 매체로 보내기 위해 전압 펄스(디지털 신호)로 바꾸는 과정으로, **디지털 인코딩(Digital Encoding)** 또는 **라인 코딩(Line Coding)**이라고 합니다.

*   **NRZ (Nonreturn to Zero):**
    *   **NRZ-L (Level):** 0과 1을 서로 다른 두 전압 레벨로 표현합니다.
    *   **NRZI (Inverted):** 전압의 레벨이 아닌 **'전이(Transition)'의 유무**로 데이터를 표현합니다. 시작 시점에 전이(변화)가 있으면 1, 없으면 0입니다.
    *   *단점:* 직류 성분(DC Component)이 발생하고, 동기화(Synchronization) 기능이 부족합니다.
*   **Multilevel Binary (다중 레벨 이진):**
    *   **Bipolar-AMI:** 0은 신호 없음(0 전압), 1은 양(+)과 음(-)의 펄스가 번갈아 나타납니다. 
    *   **Pseudoternary (가상 3진):** AMI와 반대로 1이 0 전압, 0이 양/음 교대 펄스입니다.
    *   *장점:* 직류 성분이 없고, 에러 검출이 쉽습니다.
*   **Biphase (2상):**
    *   **Manchester:** 각 비트 주기의 중간에서 항상 전이가 발생합니다. (Low$\rightarrow$High는 1, High$\rightarrow$Low는 0). 중간 전이가 데이터와 **클럭(Clock) 동기화** 역할을 모두 수행합니다. **IEEE 802.3(이더넷)**에서 사용됩니다.
    *   **Differential Manchester:** 비트 중간의 전이는 클럭용으로만 쓰이고, 비트 시작점에서의 전이 유무(없으면 1, 있으면 0)로 데이터를 판별합니다. **IEEE 802.5(토큰 링)**에서 사용됩니다.
*   **Scrambling (스크램블링):**
    *   **B8ZS, HDB3:** 동기화를 잃게 만드는 '긴 연속된 0'을 수신자가 인식할 수 있는 특정 변조 패턴(Filling sequence)으로 대체하여 동기화를 유지시키는 기술입니다.

---

### 4. 디지털 데이터를 아날로그 신호로 변환 (Digital $\rightarrow$ Analog)

디지털 데이터를 아날로그 반송파(Carrier)에 실어 보내는 과정으로, 이 역할을 하는 장치를 **모뎀(Modem, Modulator/Demodulator)**이라고 합니다. (적용 예: 공중 전화망을 통한 PC 데이터 전송, 무선 전송)

*   **디지털 변조 기법 (Digital Modulation Techniques):** 반송파의 어떤 특성을 변화시키느냐에 따라 나뉩니다.
    *   **ASK (Amplitude Shift Keying):** 진폭을 변화시킵니다 (0과 1을 진폭의 크기로 구분). 광섬유 등에서 사용됩니다.
    *   **FSK (Frequency Shift Keying):** 주파수를 변화시킵니다. 고주파 무선 및 LAN 동축 케이블에 적용됩니다 (예: BFSK, MFSK).
    *   **PSK (Phase Shift Keying):** 위상을 변화시킵니다. 
        *   **QPSK (Quadrature PSK):** 위상을 90도($\pi/2$) 단위로 4개로 나누어, 한 신호 요소(Signal element)에 2비트(00, 01, 10, 11)를 담아 전송 효율을 높입니다.
    *   **QAM (Quadrature Amplitude Modulation):** ASK(진폭)와 PSK(위상)를 결합한 방식으로, 예를 들어 4레벨 ASK와 위상을 결합해 16상태, 64상태 등으로 대역폭 대비 데이터 전송률을 극대화하는 방식입니다.

---

### 5. 아날로그 데이터를 아날로그 신호로 변환 (Analog $\rightarrow$ Analog)

음성 등의 베이스밴드(기저대역) 신호를 더 높은 대역의 반송파 주파수(Carrier Frequency)로 옮기는 과정입니다.

*   **베이스밴드(Baseband) vs 패스밴드(Passband):**
    *   **Baseband Signal:** 변조 전의 원본 정보 신호입니다.
    *   **Passband Signal:** 변조를 거쳐 높은 반송파 주파수 대역으로 이동한 신호입니다.
*   **아날로그 변조 기법 (Analog Modulation):**
    *   **AM (Amplitude Modulation):** 진폭 변조.
    *   **FM (Frequency Modulation):** 주파수 변조.
    *   **PM (Phase Modulation):** 위상 변조.
*   **적용법 - FDM (Frequency Division Multiplexing, 주파수 분할 다중화):**
    *   변조를 하는 가장 큰 이유는 **다중화(Multiplexing)**를 위해서입니다.
    *   예를 들어 4kHz 대역폭을 가지는 여러 개의 음성 채널을 서로 다른 반송파 주파수로 변조(Passband 변환)하여 하나의 넓은 대역폭 링크(예: 12kHz)에 겹치지 않게 합쳐서 동시에 전송하는 기술이 FDM입니다.
