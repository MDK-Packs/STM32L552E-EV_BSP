/******************************************************************************
 * @file     vio_STM32L552E-EV.c
 * @brief    Virtual I/O implementation for board STM32L552E-EV
 * @version  V1.2.0
 * @date     9. November 2022
 ******************************************************************************/
/*
 * Copyright (c) 2020-2022 Arm Limited (or its affiliates).
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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "cmsis_vio.h"

#include "RTE_Components.h"
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
#include "stm32l552e_eval.h"
#endif

// VIO input, output definitions
#define VIO_PRINT_MAX_SIZE      64U     // maximum size of print memory
#define VIO_PRINTMEM_NUM         4U     // number of print memories
#define VIO_VALUE_NUM            3U     // number of values
#define VIO_VALUEXYZ_NUM         3U     // number of XYZ values
#define VIO_IPV4_ADDRESS_NUM     2U     // number of IPv4 addresses
#define VIO_IPV6_ADDRESS_NUM     2U     // number of IPv6 addresses

// VIO input, output variables
__USED uint32_t      vioSignalIn;                                       // Memory for incoming signal
__USED uint32_t      vioSignalOut;                                      // Memory for outgoing signal
__USED char          vioPrintMem[VIO_PRINTMEM_NUM][VIO_PRINT_MAX_SIZE]; // Memory for the last value for each level
__USED int32_t       vioValue   [VIO_VALUE_NUM];                        // Memory for value used in vioGetValue/vioSetValue
__USED vioValueXYZ_t vioValueXYZ[VIO_VALUEXYZ_NUM];                     // Memory for XYZ value for 3-D vector
__USED vioAddrIPv4_t vioAddrIPv4[VIO_IPV4_ADDRESS_NUM];                 // Memory for IPv4 address value used in vioSetIPv4/vioGetIPv4
__USED vioAddrIPv6_t vioAddrIPv6[VIO_IPV6_ADDRESS_NUM];                 // Memory for IPv6 address value used in vioSetIPv6/vioGetIPv6

#if !defined CMSIS_VOUT
// Global types, variables, functions
static char         ip_ascii[40];       // string buffer for IP address conversion

/**
  convert IP4 address to ASCII

  \param[in]   ip4_addr   pointer to IP4 address.
  \param[out]  buf        pointer to ascii buffer.
  \param[in]   buf_len    length of a buffer (16 bytes)
*/
static void ip4_2a (const uint8_t *ip4_addr, char *buf, uint32_t buf_len) {
  if (buf_len < 16U) {
    return;
  }
  sprintf(buf, "%d.%d.%d.%d", ip4_addr[0], ip4_addr[1], ip4_addr[2], ip4_addr[3]);
}

/**
  convert IP6 address to ASCII

  \param[in]   ip6_addr   pointer to IP6 address.
  \param[out]  buf        pointer to ascii buffer.
  \param[in]   buf_len    length of a buffer (40 bytes)
*/
static void ip6_2a (const uint8_t *ip6_addr, char *buf, uint32_t buf_len) {
  uint16_t v16[8];
  int32_t i, j, nmax, idx;

  if (buf_len < 40U) {
    return;
  }

  /* Read IPv6 address in hextets */
  for (i = 0; i < 16; i += 2) {
    v16[i >> 1] = (uint16_t)(ip6_addr[i] << 8) | ip6_addr[i+1];
  }

  /* Find the largest block of consecutive zero hextets */
  idx = 8;
  for (i = nmax = 0; i < 8-1; i++) {
    if (v16[i] != 0U) {
      continue;
    }
    for (j = i; j < 8-1; j++) {
      if (v16[j+1] != 0U) {
        break;
      }
    }
    if (i == j) {
      continue;
    }
    if ((j - i) >= nmax) {
      /* Remember position and count */
      nmax = j - i + 1;
      idx  = i;
    }
    /* Skip already processed zero hextets */
    i = j;
  }
  for (i = j = 0; i < idx;  ) {
    j += sprintf(&buf[j], "%x", v16[i]);
    if (++i == idx) {
      break;
    }
    buf[j++] = ':';
  }
  if (i < 8) {
    /* Right-end not yet complete */
    buf[j++] = ':';
    for (i += nmax; i < 8; i++) {
      j += sprintf(&buf[j], ":%x", v16[i]);
    }
    if (buf[j-1] == ':') {
      buf[j++] = ':';
    }
  }
  /* Make string null-terminated */
  buf[j] = 0;
}
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

  memset(vioPrintMem, 0, sizeof(vioPrintMem));
  memset(vioValue,    0, sizeof(vioValue));
  memset(vioValueXYZ, 0, sizeof(vioValueXYZ));
  memset(vioAddrIPv4, 0, sizeof(vioAddrIPv4));
  memset(vioAddrIPv6, 0, sizeof(vioAddrIPv6));

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

// Print formatted string to test terminal.
int32_t vioPrint (uint32_t level, const char *format, ...) {
  va_list args;
  int32_t ret;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (level > vioLevelError) {
    return (-1);
  }

  if (level > VIO_PRINTMEM_NUM) {
    return (-1);
  }

  va_start(args, format);

  ret = vsnprintf((char *)vioPrintMem[level], sizeof(vioPrintMem[level]), format, args);

  va_end(args);

#if !defined CMSIS_VOUT
// Add user code here:

#endif

  return (ret);
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

  signal = vioSignalIn;

  return (signal & mask);
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

// Set XYZ value output.
void vioSetXYZ (uint32_t id, vioValueXYZ_t valueXYZ) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUEXYZ_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValueXYZ[index] = valueXYZ;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get XYZ value input.
vioValueXYZ_t vioGetXYZ (uint32_t id) {
  uint32_t index = id;
  vioValueXYZ_t valueXYZ = {0, 0, 0};
#if !defined CMSIS_VIN
// Add user variables here:
#endif

  if (index >= VIO_VALUEXYZ_NUM) {
    return valueXYZ;                    /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

#endif

  valueXYZ = vioValueXYZ[index];

  return valueXYZ;
}

// Set IPv4 address output.
void vioSetIPv4 (uint32_t id, vioAddrIPv4_t addrIPv4) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_IPV4_ADDRESS_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioAddrIPv4[index] = addrIPv4;

#if !defined CMSIS_VOUT
  // Convert IP4 address to ASCII
  ip4_2a((uint8_t *)&vioAddrIPv4[index], ip_ascii, sizeof(ip_ascii));
#endif
}

// Get IPv4 address input.
vioAddrIPv4_t vioGetIPv4 (uint32_t id) {
  uint32_t index = id;
  vioAddrIPv4_t addrIPv4 = { {0U, 0U, 0U, 0U} };
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_IPV4_ADDRESS_NUM) {
    return addrIPv4;                    /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioAddrIPv4[index] = ...;
#endif

  addrIPv4 = vioAddrIPv4[index];

  return addrIPv4;
}

// Set IPv6 address output.
void vioSetIPv6 (uint32_t id, vioAddrIPv6_t addrIPv6) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_IPV6_ADDRESS_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioAddrIPv6[index] = addrIPv6;

#if !defined CMSIS_VOUT
  // Convert IP6 address to ASCII
  ip6_2a((uint8_t *)&vioAddrIPv6[index], ip_ascii, sizeof(ip_ascii));
#endif
}

// Get IPv6 address input.
vioAddrIPv6_t vioGetIPv6 (uint32_t id) {
  uint32_t index = id;
  vioAddrIPv6_t addrIPv6 = { {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
                              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U} };
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_IPV6_ADDRESS_NUM) {
    return addrIPv6;                    /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioAddrIPv6[index] = ...;
#endif

  addrIPv6 = vioAddrIPv6[index];

  return addrIPv6;
}
