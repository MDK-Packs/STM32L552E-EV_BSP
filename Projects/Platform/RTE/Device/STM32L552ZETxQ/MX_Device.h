/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 11/11/2020 08:18:50
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            16000000
#define MX_HSE_VALUE                            16000000
#define MX_SYSCLKFreq_VALUE                     110000000
#define MX_HCLKFreq_Value                       110000000
#define MX_FCLKCortexFreq_Value                 110000000
#define MX_CortexFreq_Value                     110000000
#define MX_AHBFreq_Value                        110000000
#define MX_APB1Freq_Value                       110000000
#define MX_APB2Freq_Value                       110000000
#define MX_APB1TimFreq_Value                    110000000
#define MX_APB2TimFreq_Value                    110000000
#define MX_PWRFreq_Value                        110000000
#define MX_RTCFreq_Value                        32000
#define MX_USBFreq_Value                        16000000
#define MX_WatchDogFreq_Value                   32000
#define MX_MCO1PinFreq_Value                    110000000

/*-------------------------------- ICACHE     --------------------------------*/

#define MX_ICACHE                               1

/* GPIO Configuration */

/*-------------------------------- LPUART1    --------------------------------*/

#define MX_LPUART1                              1

/* GPIO Configuration */

/* Pin PG8 */
#define MX_LPUART1_RX_GPIO_Speed                GPIO_SPEED_FREQ_VERY_HIGH
#define MX_LPUART1_RX_Pin                       PG8
#define MX_LPUART1_RX_GPIOx                     GPIOG
#define MX_LPUART1_RX_GPIO_PuPd                 GPIO_NOPULL
#define MX_LPUART1_RX_GPIO_Pin                  GPIO_PIN_8
#define MX_LPUART1_RX_GPIO_AF                   GPIO_AF8_LPUART1
#define MX_LPUART1_RX_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PG7 */
#define MX_LPUART1_TX_GPIO_Speed                GPIO_SPEED_FREQ_VERY_HIGH
#define MX_LPUART1_TX_Pin                       PG7
#define MX_LPUART1_TX_GPIOx                     GPIOG
#define MX_LPUART1_TX_GPIO_PuPd                 GPIO_NOPULL
#define MX_LPUART1_TX_GPIO_Pin                  GPIO_PIN_7
#define MX_LPUART1_TX_GPIO_AF                   GPIO_AF8_LPUART1
#define MX_LPUART1_TX_GPIO_Mode                 GPIO_MODE_AF_PP

/* NVIC Configuration */

/* NVIC LPUART1_IRQn */
#define MX_LPUART1_IRQn_interruptPremptionPriority 4
#define MX_LPUART1_IRQn_PriorityGroup           NVIC_PRIORITYGROUP_3
#define MX_LPUART1_IRQn_Subriority              0

/*-------------------------------- USART3     --------------------------------*/

#define MX_USART3                               1

#define MX_USART3_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PB10 */
#define MX_USART3_TX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART3_TX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART3_TX_Pin                        PB10
#define MX_USART3_TX_GPIOx                      GPIOB
#define MX_USART3_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART3_TX_GPIO_Pin                   GPIO_PIN_10
#define MX_USART3_TX_GPIO_AF                    GPIO_AF7_USART3

/* Pin PB11 */
#define MX_USART3_RX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART3_RX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART3_RX_Pin                        PB11
#define MX_USART3_RX_GPIOx                      GPIOB
#define MX_USART3_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART3_RX_GPIO_Pin                   GPIO_PIN_11
#define MX_USART3_RX_GPIO_AF                    GPIO_AF7_USART3

/*-------------------------------- PWR        --------------------------------*/

#define MX_PWR                                  1

/* GPIO Configuration */

/*-------------------------------- SPI3       --------------------------------*/

#define MX_SPI3                                 1

/* GPIO Configuration */

/* Pin PG9 */
#define MX_SPI3_SCK_GPIO_Speed                  GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI3_SCK_Pin                         PG9
#define MX_SPI3_SCK_GPIOx                       GPIOG
#define MX_SPI3_SCK_GPIO_PuPd                   GPIO_NOPULL
#define MX_SPI3_SCK_GPIO_Pin                    GPIO_PIN_9
#define MX_SPI3_SCK_GPIO_AF                     GPIO_AF6_SPI3
#define MX_SPI3_SCK_GPIO_Mode                   GPIO_MODE_AF_PP

/* Pin PB4 (NJTRST) */
#define MX_SPI3_MISO_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI3_MISO_Pin                        PB4_NJTRST
#define MX_SPI3_MISO_GPIOx                      GPIOB
#define MX_SPI3_MISO_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI3_MISO_GPIO_Pin                   GPIO_PIN_4
#define MX_SPI3_MISO_GPIO_AF                    GPIO_AF6_SPI3
#define MX_SPI3_MISO_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PB5 */
#define MX_SPI3_MOSI_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI3_MOSI_Pin                        PB5
#define MX_SPI3_MOSI_GPIOx                      GPIOB
#define MX_SPI3_MOSI_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI3_MOSI_GPIO_Pin                   GPIO_PIN_5
#define MX_SPI3_MOSI_GPIO_AF                    GPIO_AF6_SPI3
#define MX_SPI3_MOSI_GPIO_Mode                  GPIO_MODE_AF_PP

/* NVIC Configuration */

/* NVIC SPI3_IRQn */
#define MX_SPI3_IRQn_interruptPremptionPriority 4
#define MX_SPI3_IRQn_PriorityGroup              NVIC_PRIORITYGROUP_3
#define MX_SPI3_IRQn_Subriority                 0

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

#endif  /* __MX_DEVICE_H */

