/* Copyright 2022 JasonRen(biu)
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
#define PRODUCT_ID      0xAA8D
#define DEVICE_VER      0x0001
#define MANUFACTURER    TG_Y&R
#define PRODUCT         tg67

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0    1    2    3    4    5    6    7    8    9    10   11   12   13   14
#define MATRIX_COL_PINS {  B9,  A3,  A4,  A5,  A6,  A7,  B0,  B2,  B10, B11, B12, B13, B14, B15, A8 }
#define MATRIX_ROW_PINS {  B3,  B4,  B6,  B7,  B8 }

#define TAP_CODE_DELAY 15

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B4
#    define RGBLED_NUM 1
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

#endif


