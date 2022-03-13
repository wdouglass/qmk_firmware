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
#include "wave87.h"


#ifdef RGBLIGHT_ENABLE
// globol
extern rgblight_config_t rgblight_config;
extern LED_TYPE led[RGBLED_NUM];
LED_TYPE last_led = {0, 0, 0};
typedef union {
  uint32_t raw;
  bool rgb_sw[3];
} kb_cums_config_t;
kb_cums_config_t kb_cums_config;

void housekeeping_task_kb(void) {
    static bool first_back_caps = false;
    if (!rgblight_is_enabled()) return;
    if (!kb_cums_config.rgb_sw[0]) {
        rgblight_setrgb_at(0, 0, 0, 0);
    }
    if (!kb_cums_config.rgb_sw[1]) {
        rgblight_setrgb_at(0, 0, 0, 1);
    }
    if (!kb_cums_config.rgb_sw[2]) {
        rgblight_setrgb_at(0, 0, 0, 2);
    }
    if (host_keyboard_led_state().caps_lock) {
        if (!first_back_caps) {
            first_back_caps = true;
            last_led = led[2];
        }
        rgblight_setrgb_at(120*rgblight_config.val/255.0, 255*rgblight_config.val/255.0, 255*rgblight_config.val/255.0, 2);
    } else {
        if (first_back_caps) {
            first_back_caps = false;
            rgblight_setrgb_at(last_led.r,last_led.g, last_led.b, 2);
        }
    }
}

void eeconfig_init_kb(void) {
    kb_cums_config.raw = 0;
    kb_cums_config.rgb_sw[0] = false;
    kb_cums_config.rgb_sw[1] = false;
    kb_cums_config.rgb_sw[2] = true;
    eeconfig_update_kb(kb_cums_config.raw);
}

void keyboard_post_init_kb(void) {
    kb_cums_config.raw = eeconfig_read_kb();
    rgblight_reload_from_eeprom();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_F22:
            if (rgblight_is_enabled() && record->event.pressed) {
                kb_cums_config.rgb_sw[0] = !kb_cums_config.rgb_sw[0];
                eeconfig_update_kb(kb_cums_config.raw);
                rgblight_reload_from_eeprom();
            }
            return false;
        case KC_F23:
            if (rgblight_is_enabled() && record->event.pressed) {
                kb_cums_config.rgb_sw[1] = !kb_cums_config.rgb_sw[1];
                eeconfig_update_kb(kb_cums_config.raw);
                rgblight_reload_from_eeprom();
            }
            return false;
        case KC_F24:
            if (rgblight_is_enabled() && record->event.pressed) {
                kb_cums_config.rgb_sw[2] = !kb_cums_config.rgb_sw[2];
                eeconfig_update_kb(kb_cums_config.raw);
                rgblight_reload_from_eeprom();
            }
            return false;
        default:
            return true;
    }
    return true;
}

#endif
