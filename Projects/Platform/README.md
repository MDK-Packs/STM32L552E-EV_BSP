Platform project
================

The **Platform** project configures the hardware of the evaluation board
and is a CMSIS-RTOS2 based software template that can be further expanded.

RTOS: Keil RTX5 Real-Time Operating System
------------------------------------------

The real-time operating system [Keil RTX5](https://arm-software.github.io/CMSIS_5/RTOS2/html/rtx5_impl.html) implements the resource management. 

It is configured with the following settings:

- [Global Dynamic Memory size](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#systemConfig): 24000 bytes
- [Default Thread Stack size](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#threadConfig): 3072 bytes
- [Event Recorder Configuration](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#evtrecConfig)
  - [Global Initialization](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#evtrecConfigGlobIni): 1
    - Start Recording: 1

Refer to [Configure RTX v5](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html) for a detailed description of all configuration options.

Board: STMicroelectronics STM32L552E-EV
---------------------------------------

The tables below list the device configuration for this board. This setup is configured using **STM32CubeMX**, 
an interactive tool provided by ST for device configuration. Refer to ["Create Projects with STM32Cube HAL and STM32CubeMX"](https://www.keil.com/pack/doc/STM32Cube) for additional information.

The heap/stack setup and the CMSIS-Driver assignment is in configuration files of related software components.
**STM32CubeMX** is used for all other settings.

The example project can be re-configured to work on custom hardware. Refer to ["Migrate STM32 Based Example Projects to Custom Hardware"](https://github.com/MDK-Packs/Documentation/tree/master/Porting_to_Custom_Hardware) for information. 

### System Configuration

| System Component        | Setting
|:------------------------|:----------------------------------------
| Device                  | STM32L522ZETzQ
| ICACHE                  | Mode: 2-ways set associative cache
| Heap                    | 64 kB (configured in startup file)
| Stack (MSP)             | 1 kB (configured in startup file)

### Clock Configuration

| Clock                   | Setting
|:------------------------|:----------------------------------------
| HCLK                    | 110 MHz
| FCLK                    | 110 MHz
| APB1                    | 110 MHz
| APB2                    | 110 MHz
| To USART3               | 110 MHz
| To LPUART1              |  16 MHz
---------------------------------------------

### GPIO Configuration and usage

| GPIO     | Signal / Label   | GPIO Settings                             | Usage
|:---------|:-----------------|:------------------------------------------|:-----
| PB11     | USART3_RX        | Alternate Function, Speed=Very High       | ST-LINK Virtual COM port (T_VCP_RX)
| PB10     | USART3_TX        | Alternate Function, Speed=Very High       | ST-LINK Virtual COM port (T_VCP_TX)
| PG8      | LPUART1_RX       | Alternate Function, Speed=Very High       | STMOD+ pin 3 (RX)
| PG7      | LPUART1_TX       | Alternate Function, Speed=Very High       | STMOD+ pin 2 (TX)
| PG10     | SPI3_MISO        | Alternate Function, Speed=Very High       | STMOD+ pin 3 (MISO)
| PC12     | SPI3_MOSI        | Alternate Function, Speed=Very High       | STMOD+ pin 2 (MOSI)
| PG9      | SPI3_SCK         | Alternate Function, Speed=Very High       | STMOD+ pin 4 (SCK)
| PA1      | vioBUTTON0       | not configured via CubeMX                 | Button TAMPER
| MFX_IO0  | vioJOYup         | not configured via CubeMX                 | Joystic UP
| MFX_IO1  | vioJOYdown       | not configured via CubeMX                 | Joystic DOWN
| MFX_IO2  | vioJOYleft       | not configured via CubeMX                 | Joystic LEFT
| MFX_IO3  | vioJOYright      | not configured via CubeMX                 | Joystic RIGHT
| MFX_IO1  | vioJOYselect     | not configured via CubeMX                 | Joystic SELECT
| PB3      | vioLED0          | not configured via CubeMX                 | LD4 GREEN
| PD3      | vioLED1          | not configured via CubeMX                 | LD5 RED
| MFX_IO11 | vioLED2          | not configured via CubeMX                 | LD6 YELLOW
| MFX_IO13 | vioLED3          | not configured via CubeMX                 | LD7 ORANGE

### NVIC Configuration

 - Priority Group = 3 bits for preemption priority 0 bits for subpriority

| NVIC Interrupt                          | Preempt Priority | Code Generation
|:----------------------------------------|:-----------------|:---------------
| Non maskable interrupt                  | 0                | Generate IRQ handler
| Hard fault interrupt                    | 0                | Generate IRQ handler
| Memory Management fault                 | 0                | Generate IRQ handler
| Prefetch fault, memory access fault     | 0                | Generate IRQ handler
| Undefined instruction or illegal state  | 0                | Generate IRQ handler
| System service call via SWI instruction | 0                | none
| Debug monitor                           | 0                | Generate IRQ handler
| Pendable request for system service     | 0                | none
| Time base: System tick timer            | 0                | none
| LPUART1 global / wake-up                | 4                | Generate IRQ handler, Call HAL handler
| SPI3 global                             | 4                | Generate IRQ handler, Call HAL handler

### Connectivity Peripherals Configuration

| Peripheral   | Mode / Settings                                                                                                    | IRQ | DMA | Note
|:-------------|:-------------------------------------------------------------------------------------------------------------------|:----|:----|:----
| SPI3         | Full-Duplex Master, Hardware NSS Signal=off, Do Not Generate Initialization Function Call                          | yes | no  | Arduino UNO R3 connector (CN11)
| LPUART1      | Asynchronous, Hardware Flow Control=off, Do Not Generate Initialization Function Call                              | yes | no  | Arduino UNO R3 connector (CN12)
| USART3       | Asynchronous, Hardware Flow Control=off, Baud Rate: 115200 Bits/s, Word Length: 8 Bits, Parity: None, Stop Bits: 1 | no  | no  | ST-LINK Virtual COM port

**STDIO** is routed to ST-LINK Virtual COM port (USART3)

### CMSIS-Driver mapping

| CMSIS-Driver | Peripheral
|:-------------|:----------
| SPI3         | SPI3
| USART6       | LPUART1

| CMSIS-Driver VIO  | Physical board hardware
|:------------------|:-----------------------
| vioBUTTON0        | Button TAMPER (PA1)
| vioJOYup          | Joystic UP (MFX_IO0)
| vioJOYdown        | Joystic DOWN (MFX_IO1)
| vioJOYleft        | Joystic LEFT (MFX_IO2)
| vioJOYright       | Joystic RIGHT (MFX_IO3)
| vioJOYselect      | Joystic SELECT (MFX_IO4)
| vioLED0           | LD4 GREEN (PB3)
| vioLED1           | LD5 RED (PD3)
| vioLED2           | LD6 YELLOW (MFX_IO11)
| vioLED3           | LD7 ORANGE (MFX_IO13)
