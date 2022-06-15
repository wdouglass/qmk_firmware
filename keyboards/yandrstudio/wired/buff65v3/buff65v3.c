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
#include "buff65v3.h"


#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}

#endif


bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(led_state.caps_lock){
        if(!rgblight_is_enabled()) {
            rgblight_enable_noeeprom();
        }
        rgblight_sethsv_at(0, 255, (rgblight_get_val()*RGBLIGHT_LIMIT_VAL)/255.0, 0);
    } else {
        if (!rgblight_is_enabled()) {
            rgblight_disable_noeeprom();
        }
    }
    return res;
}



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LOCK_GUI:
            process_magic(GUI_TOG, record);
            return false;
        default:
            return true;
    }
    return true;
}
