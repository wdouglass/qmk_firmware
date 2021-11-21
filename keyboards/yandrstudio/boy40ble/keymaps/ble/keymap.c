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
#include QMK_KEYBOARD_H
#include "outputselect.h"
#include "biu_ble_common.h"
#include "distributors.h"
#include "usb_main.h"

enum keyboard_keycodes {
    BLE_TOG_EXT = SAFE_RANGE, // ble
    USB_TOG_EXT,              // usb
    BAU_TOG_EXT,              // if ble then usb, if usb then ble
    BL_SW_0_EXT,              // ble id 0
    BL_SW_1_EXT,
    BL_SW_2_EXT,
    BL_SW_3_EXT,
    BL_SW_4_EXT,
    BL_SW_5_EXT,
    BL_SW_6_EXT,
    BL_SW_7_EXT,
    BLE_DEL_EXT,              // delete current ble bound
    BLE_CLR_EXT,              // delete all ble bound
    BLE_OFF_EXT,          // power off
    NEW_SAFE_RANGE  // Important!
};

#define BLE_TOG     KC_F15  // 打开蓝牙
#define USB_TOG     KC_F16  // 打开USB
#define BAU_TOG     KC_F17  // 蓝牙和USB之间切换
#define BL_SW_0     KC_F18  // 开启蓝牙通道0（需要打开蓝牙的条件下才行）
#define BL_SW_1     KC_F19  // 开启蓝牙通道1（需要打开蓝牙的条件下才行）
#define BL_SW_2     KC_F20  // 开启蓝牙通道2（需要打开蓝牙的条件下才行）
#define BL_SW_3     KC_F21  // 开启蓝牙通道3（需要打开蓝牙的条件下才行）
#define BLE_DEL     KC_F22  // 删除当前蓝牙绑定
#define BLE_CLR     KC_F23  // 清空所有蓝牙绑定
#define BLE_OFF KC_F24  // 关闭蓝牙连接


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT,
		KC_LCTL, TO(2), KC_PSCR, KC_SPC, MO(1), KC_SLSH, KC_SCLN, KC_QUES),
	LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
		KC_TAB, KC_BSLS, KC_QUOT, KC_GRV, KC_LABK, KC_RABK, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_DEL,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, BLE_TOG, USB_TOG, BL_SW_0, BL_SW_1, BLE_DEL, BLE_CLR,
		KC_TRNS, KC_LGUI, KC_LALT, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	LAYOUT(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS,
		KC_TRNS, TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

void keyboard_post_init_user(void) {
    debug_enable=true;
    //   debug_matrix=true;
    //   debug_keyboard=true;
    //     //debug_mouse=true;

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifndef CUSTOM_DELAY_KEYCODE
    switch(keycode) {
        case BLE_TOG:
        case BLE_TOG_EXT:
            if (record->event.pressed) {
                set_output(OUTPUT_BLUETOOTH);
            }
            return false;
        case USB_TOG:
        case USB_TOG_EXT:
            if (record->event.pressed) {
                usb_event_queue_init();
                init_usb_driver(&USB_DRIVER, false);
                set_output(OUTPUT_USB);
            }
            return false;
        case BAU_TOG:
        case BAU_TOG_EXT:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_USB) {
                    set_output(OUTPUT_BLUETOOTH);
                } else {
                    usb_event_queue_init();
                    init_usb_driver(&USB_DRIVER, false);
                    set_output(OUTPUT_USB);
                }
            }
            return false;
        case BL_SW_0:
        case BL_SW_1:
        case BL_SW_2:
        case BL_SW_3:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                if (record->event.pressed) {
                    set_output(OUTPUT_BLUETOOTH);
                    bluetooth_switch_one(keycode - BL_SW_0);
                }
            }
            return false;
        case BL_SW_0_EXT:
        case BL_SW_1_EXT:
        case BL_SW_2_EXT:
        case BL_SW_3_EXT:
        case BL_SW_4_EXT:
        case BL_SW_5_EXT:
        case BL_SW_6_EXT:
        case BL_SW_7_EXT:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                if (record->event.pressed) {
                    set_output(OUTPUT_BLUETOOTH);
                    bluetooth_switch_one(keycode - BL_SW_0_EXT);
                }
            }
            return false;
        case BLE_DEL:
        case BLE_DEL_EXT:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_BLUETOOTH) {
                    bluetooth_unpair_current();
                }
            }
            return false;
        case BLE_CLR:
        case BLE_CLR_EXT:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_BLUETOOTH) {
                    bluetooth_unpair_all();
                }
            }
            return false;
        case BLE_OFF:
        case BLE_OFF_EXT:
            stop_one_lilnk(0);
            return false;
        default:
            return true;
    }
#endif
    return true;
}
