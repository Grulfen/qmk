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

#include "features/casemodes.h"
#include "features/oneshot.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

// {{{ tap dances
enum {
    TD_CAPS
};

void dance_capsword(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        enable_caps_word();
        enable_xcase_with(SE_UNDS);
    } else if (state->count == 2) {
        enable_xcase_with(SE_UNDS);
    } else {
        set_oneshot_mods(MOD_LSFT);
        enable_xcase_with(OSM(MOD_LSFT));
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN(dance_capsword),
};

#define TD_CPS TD(TD_CAPS)
// }}}

// {{{ layers

enum layers {
    _QWERTY = 0,
    _SC2,
    _NAV,
    _SYM,
    _NUMBER,
    _NUMBAR,
    _SC2_NUM,
};

enum custom_keycodes {
    SE_TILDE = SAFE_RANGE,
    SE_GRAVE,
    SE_HATT,
    OS_CTL,
    OS_SFT,
    OS_ALT,
    OS_GUI,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define SC2      DF(_SC2)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define NUMBAR   MO(_NUMBAR)
#define NUMBER   MO(_NUMBER)
#define SC2_N    MO(_SC2_NUM)
#define C_SC2_N  LM(_SC2_NUM, MOD_LCTL)
#define S_SC2_N  LM(_SC2_NUM, MOD_LSFT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | SE/US|Caps- | Nav  |Numbar|      |  |      | Space| Sym  | BSPC | SC2  |
 *                        |      |Word  |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  ,   SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,                                        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P , SE_ARNG,
     KC_ESC  ,   SE_A ,  SE_S  ,  SE_D  ,   SE_F ,   SE_G ,                                        SE_H,   SE_J ,   SE_K ,   SE_L , SE_SCLN, SE_ADIA,
     _______ ,   SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B , _______, _______, _______, _______,    SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH, _______,
                     KEY_OVERRIDE_TOGGLE, TD_CPS ,   NAV  ,  NUMBAR, _______, _______,  KC_SPC,     SYM, KC_BSPC, SC2
    ),
/*
 * Nav Layer: Media, navigation, F-keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgDn | PgUp | Home | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  gui | alt  | shft | ctrl |Ctrl-b|                              |  ←   |  ↓   |  ↑   |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |Number|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU, KC_DEL ,
      _______, OS_GUI , OS_ALT , OS_SFT , OS_CTL , C(KC_B),                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD, KC_INS ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Sym Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | esc  |  {   |  [   |  (   |  ~   |                              |   ^  |   )  |  ]   |  }   |  `   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  -   |  *   |  =   |  _   |  $   |                              |   #  | ctrl | shft |  alt |  gui |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  +   |  |   |  @   |  /   |  %   |      |      |  |      |      |   '  |  \   |  &   |  ?   |   !  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |Number|      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______ , KC_ESC , SE_LCBR, SE_LBRC, SE_LPRN,SE_TILDE,                                     SE_HATT, SE_RPRN, SE_RBRC, SE_RCBR,SE_GRAVE, _______,
     _______ , SE_MINS, SE_ASTR, SE_EQL , SE_UNDS, SE_DLR ,                                     SE_HASH, OS_CTL , OS_SFT , OS_ALT , OS_GUI , _______,
     _______ , SE_PLUS, SE_PIPE, SE_AT  , SE_SLSH, SE_PERC, _______, _______, _______, _______, SE_QUOT, SE_BSLS, SE_AMPR, SE_QUES, SE_EXLM, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
   ),

/*
 * Num Layer: Numbers
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1   |  2   |  3   |  4   |  5   |                              |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | gui  | alt  | shft | ctrl | F11  |                              |  F12 | ctrl | shft |  alt |  gui |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  |      |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBER] = LAYOUT(
      _______,  SE_1  ,  SE_2  ,  SE_3  ,  SE_4  ,  SE_5  ,                                      SE_6  ,  SE_7  ,  SE_8  ,  SE_9  ,  SE_0  , _______,
      _______, OS_GUI , OS_ALT , OS_SFT , OS_CTL , KC_F11 ,                                     KC_F12 , OS_CTL , OS_SFT , OS_ALT , OS_GUI , _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , KC_F5  , _______, _______, _______, _______,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Numbar
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  F7  |  F8  |  F9  | F12  |                              |      | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |  F4  |  F5  |  F6  | F11  |                              |  *   | 4 $  | 5 %  | 6 ^  | = +  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  F1  |  F2  |  F3  | F10  |      |      |  |      |      |      | 1 !  | 2 @  | 3 #  |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | 0 )  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBAR] = LAYOUT(
      _______, _______,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F12 ,                                     _______, SE_7,    SE_8,    SE_9, SE_MINS, _______,
      _______, _______,  KC_F4 ,  KC_F5 ,  KC_F6 , KC_F11 ,                                     SE_ASTR, SE_4,    SE_5,    SE_6, SE_PLUS, _______,
      _______, _______,  KC_F1 ,  KC_F2 ,  KC_F3 , KC_F10 , _______, _______, _______, _______, _______, SE_1,    SE_2,    SE_3, SE_SLSH, _______,
                                 _______, _______, _______, _______, _______, _______, _______, SE_0   , _______, _______
    ),

/*
 * SC2 Layer: Base layer with easy access to number, shift + number and ctrl + number
 *            Only left half is intended to be used
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |   U  |      |  |      |  ] } |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | Shft+| SC2_N| Ctrl+|  F2  |  | Sym  | Space| Sym  | AltGr|Qwerty|
 *                        |      | SC2_N|      | SC2_N|      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SC2] = LAYOUT(
     KC_ESC  ,   SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,                                        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P , SE_ARNG,
     KC_TAB  ,   SE_A ,  SE_S  ,  SE_D  ,   SE_F ,   SE_G ,                                        SE_H,   SE_J ,   SE_K ,   SE_L , SE_ODIA, SE_ADIA,
     KC_LSFT ,   SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B ,  SE_U  , _______, _______, SE_RBRC,    SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH, _______,
                                 XXXXXXX, S_SC2_N,  SC2_N , C_SC2_N, KC_F2  , SYM    ,  KC_SPC,     SYM, KC_RALT, QWERTY
    ),
/*
 * SC2 Number
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | 6    | 7    | 8    | 9    | 0    |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | 1    | 2    | 3    | 4    | 5    |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SC2_NUM] = LAYOUT(
      _______,   SE_6 ,   SE_7 ,   SE_8 ,   SE_9 ,   SE_0 ,                                     _______, _______, _______, _______, _______, _______,
      _______,   SE_1 ,   SE_2 ,   SE_3 ,   SE_4 ,   SE_5 ,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUMBER);
}

// }}}

// {{{ key overrides
// Add key overrides to emulate american layout on swedish keyboard
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_SCLN, SE_COLN);  // shift + ; -> :
const key_override_t labk_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_COMM, SE_LABK);  // shift + , -> <
const key_override_t rabk_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_DOT, SE_RABK);   // shift + . -> >
const key_override_t squo_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUOT, SE_DQUO);  // shift + ' -> "

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL); // shift + backspace -> Del

const key_override_t **key_overrides = (const key_override_t *[]) {
    &coln_key_override,
    &labk_key_override,
    &rabk_key_override,
    &squo_key_override,

    &delete_key_override,

    NULL,
};

// }}}

// {{{ combos

enum combo_events {
  KL_ENT,
  XC_ESC,
  WE_TAB,
  OP_ARNG,
  LSEMICOLON_ADIA,
  KSEMICOLON_ODIA,
  MCOMMA_MINS,
  COMMADOT_UNDS,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ksemicolon_combo[] = {KC_K, SE_SCLN, COMBO_END};
const uint16_t PROGMEM lsemicolon_combo[] = {KC_L, SE_SCLN, COMBO_END};
const uint16_t PROGMEM mcomma_combo[] = {KC_M, SE_COMM, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {SE_COMM, SE_DOT, COMBO_END};

combo_t key_combos[] = {
    [KL_ENT] = COMBO(kl_combo, KC_ENT),
    [XC_ESC] = COMBO(xc_combo, KC_ESC),
    [WE_TAB] = COMBO(we_combo, KC_TAB),
    [OP_ARNG] = COMBO(op_combo, SE_ARNG),
    [LSEMICOLON_ADIA] = COMBO(lsemicolon_combo, SE_ADIA),
    [KSEMICOLON_ODIA] = COMBO(ksemicolon_combo, SE_ODIA),
    [MCOMMA_MINS] = COMBO(mcomma_combo, SE_MINS),
    [COMMADOT_UNDS] = COMBO(commadot_combo, SE_UNDS),
};
// }}}

// {{{ process_record_user

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case NAV:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SFT, keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTL, keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT, keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_GUI, keycode, record
    );

    // Regular user keycode case statement
    switch (keycode) {
        case SE_TILDE:
            if (record->event.pressed) {
                SEND_STRING("~");
            }
            return true;
        case SE_GRAVE:
            if (record->event.pressed) {
                SEND_STRING("`");
            }
            return true;
        case SE_HATT:
            if (record->event.pressed) {
                SEND_STRING("^");
            }
            return true;
        default:
            return true;
    }
}

// }}}

// {{{ Encoder
#ifdef ENCODER_ENABLE
void left_encoder(bool clockwise) {
    if (layer_state_is(_SYM)) {
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
    } else {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // Left encoder
        left_encoder(!clockwise);  // For some reason the clockwise is flipped for me on the kyria
    }
    return false;
}
#endif
// }}}

// vim: set foldmethod=marker:foldlevel=0
