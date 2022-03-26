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
extern rgblight_config_t rgblight_config;
uint8_t pre_mode = 0xff;

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (host_keyboard_led_state().caps_lock) {
            if (pre_mode == 0xff) {
                pre_mode = rgblight_get_mode();
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_sethsv(128, 135, rgblight_config.val);
            }
        } else {
            if (pre_mode != 0xff) {
                rgblight_mode(pre_mode);
                pre_mode = 0xff;
            }
        }
    }
    return res;
}

#endif
