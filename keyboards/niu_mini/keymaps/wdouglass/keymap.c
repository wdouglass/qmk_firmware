/* Copyright 2015-2017 Jack Humbert
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

extern keymap_config_t keymap_config;

enum unicode_names {
    LAMBDA_L,
    LAMBDA_U
};

const uint32_t PROGMEM unicode_map[] = {
    [LAMBDA_L] = 0x3BB,
    [LAMBDA_U] = 0x39B
};

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _UNICODE,
  _ADJUST
};

enum keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  UNICODE
};

enum tapdance {
    TD_RESET = 0
};

void reset_dance_each(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
    case 1:
        SEND_STRING ("R");
        break;
    case 2:
        SEND_STRING ("E");
        break;
    case 3:
        SEND_STRING ("S");
        break;
    case 4:
        SEND_STRING ("E");
        break;
    case 5:
        SEND_STRING ("T");
        break;
    default:
        SEND_STRING (" ");
        break;
    }
}

void reset_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 4) {
        reset_keyboard();
        reset_tap_dance(state);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------------------.
 * | Tab     |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |---------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |---------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |---------+------+------+------+------+------+------+------+------+------+------+------|
 * |         | Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------'
 */
  [_QWERTY] = LAYOUT_planck_mit(
    KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    UNICODE,         KC_LCTL, KC_LGUI, KC_LALT, LOWER,       KC_SPC,       RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

/* Qwerty
 * ,--------------------------------------------------------------------------------------.
 * | Tab     |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |---------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |---------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |---------+------+------+------+------+------+------+------+------+------+------+------|
 * |         | Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------'
 */
  [_UNICODE] = LAYOUT_planck_mit(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,              _______,    _______,    
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    XP(LAMBDA_L, LAMBDA_U),    _______,    _______,    
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,               _______,    _______,    
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_planck_mit(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |Pg Up |Pg Dn | Next |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
  [_RAISE] = LAYOUT_planck_mit(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_PGDN, KC_MNXT,
    _______, _______, _______, _______, _______,     _______,      _______, _______, KC_VOLD, KC_VOLU, KC_MPLY
    ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Reset| Debug|      |      |      |    Lock     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_planck_mit(
    _______,      _______, _______, _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL ,
    _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    TD(TD_RESET),   DEBUG, _______, _______, _______,   LCA(KC_L),      _______, _______, _______, _______, _______
    )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case UNICODE:
    if (record->event.pressed) {
      layer_on(_UNICODE);
    } else {
      layer_off(_UNICODE);
    }
  default:
    break;
  }
  return true;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_RESET]     = ACTION_TAP_DANCE_FN_ADVANCED(reset_dance_each, reset_dance_finished, NULL)
};
