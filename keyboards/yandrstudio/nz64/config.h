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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAAF
#define DEVICE_VER      0x0001
#define MANUFACTURER    JasonRen biu
#define PRODUCT         nz64

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//                         0    1    2    3    4   5    6    7    8   9    10   11  12   13  14
#define MATRIX_COL_PINS {  A15, B3,  B4,  B6,  B7, B5,  C13, A5,  A4, B14, B15, A8, A9,  A10   }
#define MATRIX_ROW_PINS {  C14, B13, B12, C15, A3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


#define  LED_CAPS_LOCK_PIN A5
#define  LED_PIN_ON_STATE 0



