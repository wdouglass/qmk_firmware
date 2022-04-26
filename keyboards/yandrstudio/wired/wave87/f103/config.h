/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

//                        0    1    2    3     4    5    6    7    8    9    10    11   12  13   14   15   16   17
#define MATRIX_COL_PINS { B8,  B9,  C13, C14,  C15, A0,  A3,  A4,  A5,  A6,  B0,   B1,  A1, A2,  B14, B13, B12 }
#define MATRIX_ROW_PINS { A15, B3,  B4,  B5,   B6,  B7}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 3
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_SLEEP

#   define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#   define WS2812_PWM_CHANNEL 2     // default: 2
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#   define WS2812_DMA_CHANNEL 3

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif
