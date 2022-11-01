#include QMK_KEYBOARD_H
#include "oled_font_lib/ext_font.h"

enum Layer_name {
    _QWERTY,
    _RAISE,
    _LOWER,
    _OTHER
};

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define RAISE      MO(_RAISE)
#define LOWER      MO(_LOWER)

#   ifdef I_AM_LEFT
void render_layer_helper_fun(uint8_t start_line, const char * data, uint8_t gap_w, uint8_t l) {
    uint8_t j = 0, k = 0;
    for (j = 0; j < l; ++j) { // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(32) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[pgm_read_byte(&data[j])-0x20][k]), start_line*2*128 + 32 + gap_w + j*12+k);
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[pgm_read_byte(&data[j])-0x20][k+12]), start_line*2*128+128 + 32 + gap_w + j*12+k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128 + 32 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128 + 32 + gap_w + l*12 + j);

        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128+128 + 32 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128+128 + 32 + gap_w + l*12 + j);

    }
}
void render_layer(uint8_t layer) {
    render_layer_helper_fun(0, PSTR("LAYER:"), 12, 6);
    switch (layer) {
    case 0:
        render_layer_helper_fun(1, PSTR("1:QWERTY"), 0, 8);
        break;
    case 1:
        render_layer_helper_fun(1, PSTR("2:RAISE"), 6, 7);
        break;
    case 2:
        render_layer_helper_fun(1, PSTR("3:LOWER"), 6, 7);
        break;
    case 3:
    default:
        render_layer_helper_fun(1, PSTR("4:OTHERS"), 0, 8);
        break;
    }
}

# endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L2  |   Y  |   U  |   I  |   O  |   P  | Bksp   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  (   |           |   )  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | Enter  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Win  | Alt  |                                       | Left | Down |  Up  |Right | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Lower|Space |------|       |------| Space  |Raise |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
	LAYOUT(
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(1),
        CTL_ESC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_LPRN,
        LT(1,KC_GRV),   KC_QUOT,      LALT(KC_LSFT),  KC_LGUI, KC_LALT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                                 LOWER,KC_SPC,KC_END,
        // right hand
        KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
        TG(2),       KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSPC,
                     KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          KC_QUOT,
        KC_RPRN,     KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_ENT,
                             KC_LEFT, KC_DOWN,KC_UP,KC_RIGHT,          TT(1),
        KC_LALT,        CTL_T(KC_ESC),
        KC_PGUP,
        KC_PGDN,KC_SPC,RAISE
    ),
/* Keymap 1: Raise Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |    `    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   Del  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   -  |   =  |   [  |   ]  |   \    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |Hue+  |      |      |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |Hue-  |      |      |
 *                                 `--------------------'       `--------------------'
 */
	LAYOUT(
       // left hand
       KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_TRNS,
       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,      KC_5,     KC_TRNS,
       KC_TRNS,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,   KC_GRV,
       KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,   KC_TILD,  KC_TRNS,
       TOG_OLED, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                          RGB_MOD,KC_TRNS,
                                                                  KC_TRNS,
                                                  RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_F12, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
                KC_DOWN, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
       KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_TOG, KC_TRNS,
       RGB_HUI,
       RGB_HUD, KC_TRNS, KC_TRNS
    ),
/* Keymap 2: Lower=
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |      |           |      |  ^   |  &   |  *   |  (   |  )   | Del    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  _   |  +   |  {   |  }   |  |     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Play | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
	LAYOUT(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
                 KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
    ),
/* Keymap 3: Empty
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
	LAYOUT(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    )
};
