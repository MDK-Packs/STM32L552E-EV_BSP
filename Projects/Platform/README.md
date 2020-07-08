Platform project
================

The **Platform** project configures the hardware of the evaluation board
and is a CMSIS-RTOS2 based software template that can be further expanded.

RTX5 Real-Time Operating System
-------------------------------
The [RTX5 RTOS](https://arm-software.github.io/CMSIS_5/RTOS2/html/rtx5_impl.html) 
implements the resource management. It is configured with the following settings:

- Global Dynamic Memory size: 24000 bytes
- Default Thread Stack size: 3072 bytes

STMicroelectronics STM32L552E-EV Target Board
---------------------------------------------
The Board layer contains the following configured interface drivers:

**CMSIS-Driver USART3** routed to Virtual COM port (ST-LINK):
 - RX: VCP_USART3_RX (PB11)
 - TX: VCP_USART3_TX (PB10)

**CMSIS-Driver USART6** routed to STMOD+ connector (P2):
 - RX: LPUART1_RX (PG8)
 - TX: LPUART1_TX (PG7)

**CMSIS-Driver SPI3** routed to STMOD+ connector (P2):
 - SCK:  SPI3_SCK (PG9)
 - MISO: SPI3_MISO (PG10)
 - MOSI: SPI3_MOSI (PC12)

**CMSIS-Driver VIO** with the following board hardware mapping:
 - vioBUTTON0:   Button TAMPER (PA1)
 - vioJOYup:     Joystic UP (MFX_IO0)
 - vioJOYdown:   Joystic DOWN (MFX_IO1)
 - vioJOYleft:   Joystic LEFT (MFX_IO2)
 - vioJOYright:  Joystic RIGHT (MFX_IO3)
 - vioJOYselect: Joystic SELECT (MFX_IO4)
 - vioLED0:      LD4 GREEN (PB3)
 - vioLED1:      LD5 RED (PD3)
 - vioLED2:      LD6 YELLOW (MFX_IO11)
 - vioLED3:      LD7 ORANGE (MFX_IO13)

**STDOUT** routed to Virtual COM port (ST-LINK, baudrate = 115200)

The board configuration can be modified using 
[STM32CubeMX](https://www.keil.com/stmicroelectronics-stm32) 
and is stored in the file `STCubeGenerated.ioc`.
