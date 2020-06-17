/*---------------------------------------------------------------------------
 * Copyright (c) 2020 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *      Name:    main_ns.c
 *      Purpose: Main function non-secure mode
 *
 *---------------------------------------------------------------------------*/

#include <arm_cmse.h>

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "..\part_S\Secure_Functions.h"

/*----------------------------------------------------------------------------
  NonSecure functions used for callbacks
 *----------------------------------------------------------------------------*/
int32_t NonSecure_LED_On(uint32_t num);
int32_t NonSecure_LED_On(uint32_t num)
{
  return Secure_LED_On(num);
}

int32_t NonSecure_LED_Off(uint32_t num);
int32_t NonSecure_LED_Off(uint32_t num)
{
  return Secure_LED_Off(num);
}

/*----------------------------------------------------------------------------
  SysTick IRQ Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void);
void SysTick_Handler (void) {
  static uint32_t ticks;

  switch (ticks++) {
    case 20U:
      Secure_LED_On(1U);
      break;
    case 50U:
      Secure_LED_Off(1U);
      break;
    case 99U:
      ticks = 0U;
      break;
    default:
      if (ticks > 99U) {
        ticks = 0U;
      }
  }
}

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void)
{
  uint32_t i;

  /* register NonSecure callbacks in Secure application */
  Secure_LED_On_callback(NonSecure_LED_On);
  Secure_LED_Off_callback(NonSecure_LED_Off);

  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 100U);  /* Generate interrupt each 10 ms */

  while (1) {
    Secure_LED_On (2U);
    for (i = 0U; i < 0x400000U; i++) __NOP();
    Secure_LED_Off(2U);
    for (i = 0U; i < 0x400000U; i++) __NOP();
  }
}
