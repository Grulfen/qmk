/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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


// {{{ layers

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      OSL(_SYM)
#define NAV      OSL(_NAV)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define SFT_SPC  MT(MOD_LSFT, KC_SPC)
#define RSFT_SPC MT(MOD_RSFT, KC_SPC)
#define AGR_BSP  MT(MOD_RALT, KC_BSPC)

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K LSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

#define NAV_ENT  LT(_NAV, KC_ENT)
#define SYM_BSP  LT(_SYM, KC_BSPC)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  [ {   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |      |  |      |  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |Enter/| LSft/| Nav  |  | Sym  | LSft/| Sym  | AltGr| RGUI |
 *                        |      |      | Nav  | Space|      |  |      | Space|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  ,   KC_Q ,  KC_W  ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,   KC_I ,   KC_O ,   KC_P , KC_LBRC,
     KC_ESC  ,   GUI_A,  ALT_S ,  SFT_D ,  CTL_F ,   KC_G ,                                        KC_H,   CTL_J,   SFT_K,   ALT_L,GUI_SCLN,KC_QUOTE,
     KC_LSFT ,   KC_Z ,  KC_X  ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC, _______, _______, KC_RBRC, KC_N   ,   KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                 _______, _______, NAV_ENT, SFT_SPC,  NAV   , SYM    ,RSFT_SPC,     SYM, KC_RALT, KC_RGUI
    ),
/*
 * Nav Layer: Media, navigation, F-keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              | PgDn | PgUp | Home | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |Ctrl-q|                              |  ←   |  ↓   |  ↑   |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | Bspc |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU, KC_DEL ,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , C(KC_Q),                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD, KC_INS ,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, KC_BSPC, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// }}}

// {{{ combos
//
//
enum combo_events {
  IO_BSPC,
  KL_ENT,
  SD_ESC,
  WE_TAB,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {SFT_K, ALT_L, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {ALT_S, SFT_D, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};

combo_t key_combos[] = {
    [IO_BSPC] = COMBO(io_combo, KC_BSPC),
    [KL_ENT] = COMBO(kl_combo, KC_ENT),
    [SD_ESC] = COMBO(sd_combo, KC_ESC),
    [WE_TAB] = COMBO(we_combo, KC_TAB),
};
// }}}

// {{{ rotary encoder

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
    return false;
}
#endif

// }}}

// vim: set foldmethod=marker:foldlevel=0
