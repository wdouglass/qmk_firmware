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

//                        0    1    2    3   4    5    6    7    8    9    10   11   12   13   14   15   16
#define MATRIX_COL_PINS { B7,  A6,  B6, B5,  B4,  B3,  A5,  A1,  B1,  B0,  A7,  A9,  B11, B10, B2,  A15, B15 }
#define MATRIX_ROW_PINS { A3,  B9,  B8,  A4, C14, C13 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A8
#    define RGBLED_NUM 12
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_SLEEP

#endif
