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
#define PRODUCT_ID      0xAAC2
#define DEVICE_VER      0x0001
#define MANUFACTURER    ZUOER_Y&R
#define PRODUCT         Z_Alice_Ble

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

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

#define TAP_CODE_DELAY 15

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4



// for ble
// #define Z_ALICE_REV1
// rgb switch
#ifdef Z_ALICE_REV1

#   define DISABLE_MAGIC_BOOTLOADER
#   define DISABLE_EEPROM_CLEAR

// disable rgb when using ble
#   define RGB_ONLY_ON_WHEN_USB
#   define RGB_BLE_SW A6

#   define BIUNRF52ResetPin A0
#   define BIUNRF52WKPin A1
#   define BIUSTM32WKPin A3


// USB Power
#   define USB_PWR_READ
#   define USB_PWR_READ_PIN A8

// ADC SETTING
#   define SAMPLE_BATTERY
#   define BATTERY_LEVEL_SW_PIN A2 // Adc pin


#else

#   define DISABLE_MAGIC_BOOTLOADER
#   define DISABLE_EEPROM_CLEAR

// disable rgb when using ble
#   define RGB_ONLY_ON_WHEN_USB
#   define RGB_BLE_SW A6

#   define BIUSTM32WKPin A0
#   define BIUNRF52ResetPin A1
#   define BIUNRF52WKPin A3


// USB Power
#   define USB_PWR_READ
#   define USB_PWR_READ_PIN A8
// ADC SETTING
#   define SAMPLE_BATTERY
#   define BATTERY_LEVEL_SW_PIN A2 // Adc pin
#endif
