### 1. 주파수 대역 및 무선 전파 (Frequency Band & Radio Frequency)

무선 통신의 기반이 되는 전자기 스펙트럼(**Electromagnetic Spectrum**)과 주파수 대역의 분류입니다. 통상적으로 1 GHz 이상을 **Microwave**, 30 GHz 이상을 **Millimeter wave(mmWave)**라고 부릅니다.

*   **주요 주파수 대역과 기술 적용법:**
    *   **VLF / LF / MF / HF**: 저주파 대역으로 수분 투과력이 좋아 잠수함 통신(VLF)에 쓰이거나, AM 라디오(MF), 단파 방송(HF)에 적용됩니다.
    *   **VHF / UHF (30MHz ~ 3GHz)**: 널리 쓰이는 대역으로 FM/TV 방송(VHF)과 **Cellular 통신, Wi-Fi, Bluetooth, GPS**(UHF)에 적용됩니다.
    *   **SHF / EHF (3GHz ~ 300GHz)**: 초고주파 대역으로 무선 랜(WLAN), 위성 통신, **5G Cellular (Sub-6GHz 및 28/39GHz mmWave)**, 레이더망에 사용됩니다.

### 2. 무선 전파 특성 (Wireless Propagation)

전파가 매질을 통과하거나 장애물을 만났을 때 겪는 물리적 현상과 이로 인한 데이터 손실 모델입니다.

*   **핵심 전파 용어 (Propagation Behaviors):**
    *   **Absorption (흡수)**: 수분 등에 의해 전파 에너지가 흡수되는 현상입니다. 인체의 50~65%는 물이므로, 사용자 밀도(**User Density**)가 높은 실내(예: 공항)에서는 인체 흡수로 인해 무선 랜(WLAN) 신호의 감쇄(**Attenuation**)가 발생합니다.
    *   **Refraction (굴절)**: 매질의 밀도 차이로 인해 전파 방향이 휘는 현상입니다. 기온, 기압, 수증기 등에 의해 발생하며 실외 원거리 브릿지 통신에 영향을 줍니다.
    *   그 외 **Reflection (반사), Scattering (산란), Diffraction (회절)** 현상이 존재합니다.
*   **Multipath (다중 경로)와 ISI:**
    *   다중 경로 현상으로 인해 신호가 서로 다른 시간에 도착하는 것을 지연 확산(**Delay Spread**)이라고 합니다.
    *   이는 신호의 강도를 증가(**Upfade**)시키거나 상쇄(**Nulling**)시킬 수 있으며, 앞선 심볼이 다음 심볼에 영향을 미치는 **ISI (Inter-Symbol Interference, 기호 간 간섭)**를 유발하여 데이터의 손상을 가져옵니다.
*   **Sub-1 GHz Band (황금 대역):**
    *   1 GHz 이하 대역은 수 km에 달하는 장거리 통신이 가능하고 훌륭한 벽/건물 투과 성능(**Penetration**)을 가지며 저전력 소비가 가능합니다. 따라서 **IoT 및 LPWAN (Low Power Wide Area)** 환경에 최적화되어 적용됩니다.
*   **Link Budget (링크 예산):**
    *   송신기의 전력(**Transmission Power**)에서 시작해 케이블 손실, 안테나 이득, 공간 경로 손실(**Path Loss**)을 거쳐 최종 수신기에 도달하는 신호의 강도를 계산하는 방법입니다.
    *   수신기가 신호를 성공적으로 처리할 수 있는 최소 전력인 **Receiver Sensitivity (수신 감도)**를 만족해야 통신이 가능합니다.

### 3. 대역 확산 (Spread Spectrum)

전송에 필요한 대역폭보다 의도적으로 훨씬 넓은 대역폭을 사용하여 신호를 퍼뜨리는 기술입니다. 협대역(**Narrowband**)에 비해 전파 방해(**Jamming**) 및 도청에 강한 내성을 갖습니다. 여러 사용자가 간섭 없이 대역을 공유하는 **CDMA** 통신이나 보안 통신에 적용됩니다.

*   **대역 확산의 3가지 주요 기법:**
    *   **FHSS (Frequency Hopping Spread Spectrum)**: 송신기와 수신기가 동기화되어 일련의 무작위 주파수 채널로 빠르게 도약(**Hop**)하며 전송합니다. 의사 난수(**Pseudo-Random Numbers**)를 사용하므로 알고리즘과 시드(Seed)를 모르는 도청자는 잡음(Blips)만 듣게 됩니다.
    *   **DSSS (Direct Sequence Spread Spectrum)**: 데이터의 각 비트를 치핑 코드(**Chipping code**)라는 다수의 비트로 변환(XOR 연산 등)하여 넓은 주파수 대역에 분산시킵니다.
    *   **CSS (Chirp Spread Spectrum)**: 선형적으로 주파수가 증가하거나 감소하는 넓은 대역의 **Chirp 펄스**를 사용합니다. 도플러 효과 및 다중경로 페이딩에 강력한 저항력을 지녀 군사 통신 및 장거리 저전력 통신인 **LoRa (LPWA)** 기술에 핵심적으로 적용됩니다.
*   **SDR (Software Defined Radio):**
    *   전통적인 하드웨어 라디오 컴포넌트(믹서, 필터 등)를 **DSP (Digital Signal Processing)** 소프트웨어로 구현하여 유연성을 극대화한 라디오 통신 시스템입니다.

### 4. OFDM 및 채널 상태 정보 (OFDM & CSI)

*   **OFDM (Orthogonal Frequency Division Multiplexing, 직교 주파수 분할 다중화):**
    *   단일 고속 데이터를 다수의 저속 하위 반송파(**Sub-carrier**)로 쪼개어 다중 전송하는 다중 반송파 변조(**MCM, Multi-Carrier Modulation**) 기술입니다. 각 서브캐리어는 직교성(**Orthogonality**)을 띄어 서로 간섭하지 않습니다.
    *   **적용 방법 및 극복하는 한계:**
        1.  **ISI 극복**: 단일 반송파로 고속 전송 시 심볼 길이가 너무 짧아져(**Short Symbol**) 앞서 설명한 **ISI**에 치명적입니다. OFDM은 데이터를 병렬로 쪼개므로 심볼 길이(**Symbol Duration**)를 길게 유지할 수 있어 ISI 방어에 유리합니다.
        2.  **Frequency Selective Fading (주파수 선택적 페이딩) 극복**: 광대역 신호는 다중 경로를 거치면서 특정 주파수 성분만 크게 감쇄되거나 증폭되어 신호 형태가 파괴됩니다. OFDM은 전체 대역을 좁은 여러 대역(Narrowband)으로 나누므로, 채널 응답이 평탄(Flat)해져 원래 신호 모양을 유지할 수 있습니다.
*   **Wi-Fi Sensing과 CSI (Channel State Information):**
    *   **CSI**는 신호가 송신기에서 수신기로 전파되면서 겪는 페이딩, 산란, 전력 감쇄 등에 대한 '채널 상태 정보'를 의미합니다.
    *   **적용법**: 과거에는 단순한 통신 최적화에만 쓰였으나, 최근에는 CSI의 변화 패턴을 분석하여 벽 너머 사람의 걷는 동작이나 위치를 감지 및 추적하는 **Wi-Fi Sensing** (무선 센싱) 기술로 적극 활용되고 있습니다.
