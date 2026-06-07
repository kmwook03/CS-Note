### 1. 정보의 표현 및 통신 시스템 기본 (Information Representation)

#### 📌 핵심 용어 및 개념
*   **Information (정보):** 표현하고자 하는 대상의 본질입니다.
*   **Data (데이터):** 정보를 논리적인 숫자 값(Numerical Value)으로 표현한 것입니다.
*   **Signal (신호):** 데이터가 전파(Propagated)되기 위한 물리적인 수단입니다 (예: 전압 펄스, 변조된 파형 등).
*   **Analog vs. Digital (아날로그와 디지털):** 아날로그는 연속적(Continuous)인 형태를 띠며, 디지털은 이산적(Discrete)인 형태를 띱니다.
*   **Digital System (디지털 시스템):** 모든 형태의 정보(숫자, 문자, 소리, 영상 등)를 이진(Binary) 데이터로 표현, 저장, 처리하는 시스템입니다.

#### 💡 기술의 적용법
*   **부호화 및 역부호화 (Encoding / Decoding):** 특정 정보를 이진 값(Binary)으로 변환하는 과정을 부호화(Encoding)라 하고, 그 역과정을 역부호화(Decoding)라고 합니다. 어떤 부호화 방식이 적용되었는지 알아야만 정확한 역부호화 및 데이터 해석이 가능합니다.
*   **음수 정수의 표현 (Negative Integer Representation):** $n$개의 비트는 $2^n$개의 다른 값을 표현할 수 있습니다. 최상위 비트인 **MSB (Most Significant Bit)**를 활용하여 부호를 나타내는데, MSB가 0이면 양수(Unsigned integer로 해석 가능)를, MSB가 1이면 음수를 표현하도록 절반씩 나누어 적용합니다.
*   **디지털 통신의 핵심 블록 (Essential Blocks of Digital Communication):**
    데이터는 `Format` $\rightarrow$ `Source Encode` $\rightarrow$ `Encrypt(암호화)` $\rightarrow$ `Channel Encode` $\rightarrow$ `Multiplex(다중화)` $\rightarrow$ `Pulse Modulation` $\rightarrow$ `Bandpass Modulation` $\rightarrow$ `Frequency Spread` $\rightarrow$ `Multiple Access`의 단계를 거쳐 송신되며, 수신 시에는 이 역과정(Decode, Decrypt, Demultiplex 등)을 거칩니다.

### 2. 멀티미디어 압축 및 정보 이론 (Multimedia Compression & Entropy)

멀티미디어 정보(예: 해상도 $640 \times 480$, 초당 프레임 **FPS (Frames Per Second)** 30인 무손실 영상)는 데이터 발생량이 막대하므로 **압축(Compression)**이 필수적입니다.

#### 📌 핵심 용어 및 개념
*   **Entropy (엔트로피):** 정보 이론에서 기원한 개념으로, 어떤 심볼(Symbol)이 발생할 확률($p_n$)을 바탕으로 해당 심볼에서 얻을 수 있는 정보량의 기댓값(평균 정보량)을 의미합니다. 
    *   공식: $H(A) = \sum p_n \log_b (\frac{1}{p_n})$
*   **Entropy Coding (엔트로피 코딩):** 섀넌의 정보 코딩 정리(Shannon's source coding theorem)에 따라, 자주 발생하는 심볼에는 짧은 코드워드(Codeword)를 할당하고 발생 빈도가 낮은 심볼에는 긴 코드워드를 할당하여 전체 데이터 크기를 줄이는 압축 기술입니다.
*   **Run-Length Encoding (RLE):** 동일한 값이 연속해서 나타날 때, '값'과 '연속된 갯수'로 묶어서 표현하는 압축 기법입니다 (예: 0이 8번 연속되면 (0; 8)로 표현).

#### 💡 기술의 적용법
*   엔트로피 코딩의 대표적인 적용 알고리즘으로는 **Huffman Coding(허프만 코딩)**과 **Lempel-Zip Coding**이 있으며, 데이터의 통계적 확률을 분석하여 최적의 비트 길이를 할당합니다.

### 3. 영상 압축 (Video Compression)

영상처리는 일반적으로 `Analog/Digital Convert` $\rightarrow$ `RGB-YUV Convert` $\rightarrow$ `Subsampling (ex. 4:2:0)` $\rightarrow$ `Encoding (H.264 / MPEG4-AVC)`의 과정을 거칩니다. 영상 압축은 공간적 모델과 시간적 모델을 결합하여 이루어집니다.

#### 가. 색상 모델 변환 (RGB & YUV)
*   **YUV Model:** 컴퓨터 그래픽스에서 주로 쓰이는 RGB 모델과 달리, 인간의 시각 인지 특성을 반영하여 색상을 분리하는 모델입니다.
*   **적용법:** 밝기 정보를 의미하는 **Luma (Y)**와 색상 정보를 의미하는 **Chrominance (U, V)**로 분리합니다. 인간의 눈은 색상보다 밝기 변화에 훨씬 민감하므로, 흑백(밝기) 정보는 그대로 유지하면서 색상 정보(U, V)의 데이터양만 줄이는 서브샘플링(Subsampling)을 적용하여 시각적 손실 없이 데이터를 크게 압축합니다.

#### 나. 공간적 압축 (Spatial Model)
하나의 정지 이미지(프레임) 내에 존재하는 인접 화소들 간의 중복성을 제거하는 기법입니다.
*   **Spatial Frequency (공간 주파수):** 공간에서 색이나 구조가 변화하는 정도를 뜻합니다.
*   **DCT (Discrete Cosine Transform, 이산 코사인 변환):** 화소(Pixel) 값으로 이루어진 $8 \times 8$ 공간 영역 데이터를 주파수 영역(Frequency domain)으로 변환하는 기술입니다.
*   **적용법:** 
    1. 원본 이미지를 $8 \times 8$ 블록으로 나누고 **DCT**를 수행합니다. 일반적인 영상은 DCT 수행 시 값이 저주파 영역에 집중되는 성질을 보입니다.
    2. 생성된 DCT 계수(Coefficient) 행렬을 **Quantization(양자화)** 테이블을 통해 양자화하여 불필요한 고주파 성분을 제거합니다.
    3. 2차원 배열을 1차원 데이터로 만들기 위해 지그재그 스캐닝(**ZigZag Scanning**)을 수행한 후, 연속된 0의 값을 압축하는 **RLE (Run-Length Encoding)**를 적용하여 공간적 잉여 데이터(Spatial redundancy)를 획기적으로 줄입니다.

#### 다. 시간적 압축 (Temporal Model)
연속된 비디오 프레임 사이의 움직임 변화가 크지 않다는 점(Temporal Redundancy, 시간적 중복)을 이용하여 압축하는 기법입니다.
*   **GOP (Group Of Picture):** 압축 및 재생의 단위가 되는 프레임들의 그룹입니다.
*   **적용법 (Frame Types):** 전체 화면을 모두 저장하지 않고, 기준이 되는 프레임과 변화된 움직임 정보만을 저장합니다.
    *   **I Frame (Intra-frame):** 기준이 되는 독립적인 프레임으로, 랜덤 액세스(Random access point)의 기준이 됩니다.
    *   **P Frame (Predictive-frame):** 이전 프레임을 바탕으로 단방향 예측(Unidirectional prediction)을 수행하여 변화된 부분만 저장합니다.
    *   **B Frame (Bi-directional-frame):** 앞뒤 프레임을 모두 참조하는 양방향 예측을 통해 가장 높은 압축률을 달성합니다. 
