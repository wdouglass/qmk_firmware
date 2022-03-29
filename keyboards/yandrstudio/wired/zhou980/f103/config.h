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
#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { A8,  B15, B14, B13,  A10, A3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A15
#    define RGBLED_NUM 4
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_SLEEP

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif

#ifdef BOOTLOADER_TINYUF2
#   define FEE_PAGE_BASE_ADDRESS 0x08004000
#endif
