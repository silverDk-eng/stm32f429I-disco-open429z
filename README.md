# stm32f429I-disco-open429z
stm32f429I-discovery-open429z-d board

<b>reference book : Mastering STM32. A step-by-step guide.2ed 2022(Noviello C)</b>
<br><b>stm32f429I-dicovery board rev : MB1075E</b>
<br>https://www.st.com/en/evaluation-tools/32f429idiscovery.html
<br>schematic[<b>MB1075E</b>] : mb1075-f429i-e01_schematic.pdf [https://www.st.com/en/evaluation-tools/32f429idiscovery.html#cad-resources]

<br>
<br><b>Open429Z-D board Maker: WAVESHARE 확장보드</b>
<br>Development Resources
<br> -.Schematic
<br> -.Demo code (examples in C, μC/OS-II)
<br> -.Related software (KEIL etc.)
<br> -.STM32 Datasheets
<br> -.STM32 development documentations
<br> -.https://www.waveshare.com/open429z-d-standard.htm?utm_source=chatgpt.com
<br> -.Wiki: www.waveshare.com/wiki/Open429Z-D

<br><b>개발 환경</b> 
<br> IDE : STM32CubeIDE 
<br><b>Port 설정</b>
<br><b>1.UART1
<br>PA9	USART1_TX	↔ STLINK_RX [STM32F103CBT6_PA3]
<br>PA10	USART1_RX ↔ STLINK_TX [STM32F103CBT6_PA2]
<br>2.UART5
<br>PC12 UART5_TX - USBTOUART RXD0 - JUMPER 제거 후, 직접 연결
<br>PD2	UART5_RX  - USBTOUART TXD0 - JUMPER 제거 후, 직접 연결</b>

<img width="848" alt="image" src="https://github.com/user-attachments/assets/7a58f447-541d-4b22-a76d-b86c88d20d93" />

<img width="593" alt="image" src="https://github.com/user-attachments/assets/b2567c15-4da9-4735-b695-5d58a400b57c" />
