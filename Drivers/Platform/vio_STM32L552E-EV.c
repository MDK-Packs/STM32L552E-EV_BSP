/******************************************************************************
 * @file     vio_STM32L552E-EV.c
 * @brief    Virtual I/O implementation for board STM32L552E-EV
 * @version  V2.0.0
 * @date     3. October 2023
 ******************************************************************************/
/*
 * Copyright (c) 2020-2023 Arm Limited (or its affiliates).
 * All rights reserved.
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
 */

/*! \page vio_STM32L552E_EV Physical I/O Mapping

The table below lists the physical I/O mapping of this CMSIS-Driver VIO implementation.

Virtual Resource  | Variable       | Physical Resource on STM32L552E-EV             |
:-----------------|:---------------|:-----------------------------------------------|
vioBUTTON0        | vioSignalIn.0  | GPIO A.1: Button TAMPER                        |
vioJOYup          | vioSignalIn.4  | MFX_IO0:  Joystic UP                           |
vioJOYdown        | vioSignalIn.5  | MFX_IO1:  Joystic DOWN                         |
vioJOYleft        | vioSignalIn.6  | MFX_IO2:  Joystic LEFT                         |
vioJOYright       | vioSignalIn.7  | MFX_IO3:  Joystic RIGHT                        |
vioJOYselect      | vioSignalIn.8  | MFX_IO4:  Joystic SELECT                       |
vioLED0           | vioSignalOut.0 | GPIO B.3: LD4 GREEN                            |
vioLED1           | vioSignalOut.1 | GPIO D.3: LD5 RED                              |
vioLED2           | vioSignalOut.2 | MFX_IO11: LD6 YELLOW                           |
vioLED3           | vioSignalOut.3 | MFX_IO13: LD7 ORANGE                           |
*/

/* History:
 *  Version 2.0.0
 *    Updated to API 1.0.0
 *  Version 1.0.0
 *    Initial release
 */

#include <string.h>
#include "cmsis_vio.h"

#include "RTE_Components.h"                 // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
#include "stm32l552e_eval.h"
#endif

// VIO input, output definitions
#define VIO_VALUE_NUM           3U          // Number of values

// VIO input, output variables
__USED uint32_t vioSignalIn;                // Memory for incoming signal
__USED uint32_t vioSignalOut;               // Memory for outgoing signal
__USED int32_t  vioValue[VIO_VALUE_NUM];    // Memory for value used in vioGetValue/vioSetValue

#if !defined CMSIS_VOUT
// Add global user types, variables, functions here:

#endif

#if !defined CMSIS_VIN
// Add global user types, variables, functions here:

#endif

// Initialize test input, output.
void vioInit (void) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  memset(vioValue, 0, sizeof(vioValue));

#if !defined CMSIS_VOUT
  // Initialize LEDs pins
  BSP_LED_Init(LED_RED);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_YELLOW);
  BSP_LED_Init(LED_ORANGE);
#endif

#if !defined CMSIS_VIN
  // Initialize buttons pins, joystick pins
  BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
  BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_GPIO);

  BSP_JOY_Init(JOY1, JOY_MODE_GPIO, JOY_ALL);
#endif
}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
  // Output signals to LEDs

  if ((mask & vioLED0) != 0U) {
    if ((signal & vioLED0) != 0U) {
      BSP_LED_On(LED_RED);
    } else {
      BSP_LED_Off(LED_RED);
    }
  }

  if ((mask & vioLED1) != 0U) {
    if ((signal & vioLED1) != 0U) {
      BSP_LED_On(LED_GREEN);
    } else {
      BSP_LED_Off(LED_GREEN);
    }
  }

#if (USE_BSP_IO_CLASS == 1)
  if ((mask & vioLED2) != 0U) {
    if ((signal & vioLED2) != 0U) {
      BSP_LED_On(LED_YELLOW);
    } else {
      BSP_LED_Off(LED_YELLOW);
    }
  }

  if ((mask & vioLED3) != 0U) {
    if ((signal & vioLED3) != 0U) {
      BSP_LED_On(LED_ORANGE);
    } else {
      BSP_LED_Off(LED_ORANGE);
    }
  }
#endif
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

#if !defined CMSIS_VIN
  // Get input signals from buttons and joystick
  if ((mask & vioBUTTON0) != 0U) {
    if (BSP_PB_GetState(BUTTON_TAMPER) == 1U) {
      vioSignalIn |=  vioBUTTON0;
    } else {
      vioSignalIn &= ~vioBUTTON0;
    }
  }

#if (USE_BSP_IO_CLASS == 1)
  if ((mask & vioJOYup) != 0U) {
    if (BSP_JOY_GetState(JOY1) == JOY_UP) {
      vioSignalIn |=  vioJOYup;
    } else {
      vioSignalIn &= ~vioJOYup;
    }
  }

  if ((mask & vioJOYselect) != 0U) {
    if (BSP_JOY_GetState(JOY1) == JOY_SEL) {
      vioSignalIn |=  vioJOYselect;
    } else {
      vioSignalIn &= ~vioJOYselect;
    }
  }

  if ((mask & vioJOYright) != 0U) {
    if (BSP_JOY_GetState(JOY1) == JOY_RIGHT) {
      vioSignalIn |=  vioJOYright;
    } else {
      vioSignalIn &= ~vioJOYright;
    }
  }

  if ((mask & vioJOYleft) != 0U) {
    if (BSP_JOY_GetState(JOY1) == JOY_LEFT) {
      vioSignalIn |=  vioJOYleft;
    } else {
      vioSignalIn &= ~vioJOYleft;
    }
  }

  if ((mask & vioJOYdown) != 0U) {
    if (BSP_JOY_GetState(JOY1) == JOY_DOWN) {
      vioSignalIn |=  vioJOYdown;
    } else {
      vioSignalIn &= ~vioJOYdown;
    }
  }
#endif
#endif

  signal = vioSignalIn & mask;

  return signal;
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value = 0;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return value;                       /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioValue[index] = ...;
#endif

  value = vioValue[index];

  return value;
}
