Platform Project
================

The 'Platform' project configures the hardware of the evaluation board
and is a CMSIS-RTOS2 based software template that can be further expanded.

This implementation contains the following configured interface drivers:

  - CMSIS-Driver LPUART1 routed to STMOD+ connector
    - TX: P2 pin 2
    - RX: P2 pin 3

  - CMSIS-Driver SPI3 routed to STMOD+ connector
    - SCK:  P21 pin 4
    - MISO: P21 pin 9
    - MOSI: P21 pin 8
    - SSN:  P21 pin 1

  - CMSIS-Driver I2C1 routed to STMOD+ connector
    - SCL: P21 pin 7
    - SDA: P21 pin 10

  - CMSIS-Driver VIO with the following board hardware mapping
    - vioBUTTON0:   PA1      - Button TAMPER
    - vioJOYup:     MFX_IO0  - Joystic UP
    - vioJOYdown:   MFX_IO1  - Joystic DOWN
    - vioJOYleft:   MFX_IO2  - Joystic LEFT
    - vioJOYright:  MFX_IO3  - Joystic RIGHT
    - vioJOYselect: MFX_IO4  - Joystic SELECT
    - vioLED0:      PB3      - LD4 GREEN
    - vioLED1:      PD3      - LD5 RED
    - vioLED2:      MFX_IO11 - LD6 YELLOW
    - vioLED3:      MFX_IO13 - LD7 ORANGE

The CMSIS-RTOS2 is based on RTX5 with the following configuration settings:

   - Global Dynamic Memory size: 32768 bytes

   - Default Thread Stack size: 3072 bytes
