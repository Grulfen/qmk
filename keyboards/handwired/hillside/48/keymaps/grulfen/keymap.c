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
#include "features/swapper.h"
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
    _NAV,
    _SYM,
    _NUMBER,
    _NUMBAR,
};

enum custom_keycodes {
    SE_TILDE = SAFE_RANGE,
    SE_GRAVE,
    SE_HATT,
    OS_CTL,
    OS_SFT,
    OS_ALT,
    OS_GUI,
    ALT_TAB,
    SA_TAB,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define NUMBAR   MO(_NUMBAR)
#define NUMBER   MO(_NUMBER)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |                |      |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |Caps- | Nav  |Numbar|      |  |      | Space| Sym  | BSPC |      |
 *                        |      |Word  |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     _______ ,   SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,                                        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P , _______,
     _______ ,   SE_A ,  SE_S  ,  SE_D  ,   SE_F ,   SE_G ,                                        SE_H,   SE_J ,   SE_K ,   SE_L , SE_SCLN, _______,
     _______ ,   SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B , _______,                   _______,    SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH, _______,
                                _______ , TD_CPS ,   NAV  , NUMBAR , _______, _______,  KC_SPC,     SYM, KC_BSPC, _______
    ),
/*
 * Nav Layer: Media, navigation, F-keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  tab |alttab|ALTTAB|      |      |                              | PgDn | PgUp | Home | End  | VolUp|        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  gui | alt  | shft | ctrl |Ctrl-b|                              |  ←   |  ↓   |  ↑   |   →  | VolDn|        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |PrtSc |      |      |      |      |      |                |      | Pause|M Prev|M Play|M Next|VolMut|        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |Number|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_TAB , SA_TAB,  ALT_TAB, _______, _______,                                     KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU, _______,
      _______, OS_GUI , OS_ALT , OS_SFT , OS_CTL , C(KC_B),                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD, _______,
      _______, KC_PSCR, _______, _______, _______, _______, _______,                   _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Sym Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | esc  |  {   |  [   |  (   |  ~   |                              |   ^  |   )  |  ]   |  }   |  `   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  -   |  *   |  =   |  _   |  $   |                              |   #  | ctrl | shft |  alt |  gui |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |  +   |  |   |  @   |  /   |  %   |      |                |      |   '  |  \   |  &   |  ?   |   !  |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |Number|      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______ , KC_ESC , SE_LCBR, SE_LBRC, SE_LPRN,SE_TILDE,                                     SE_HATT, SE_RPRN, SE_RBRC, SE_RCBR,SE_GRAVE, _______,
     _______ , SE_MINS, SE_ASTR, SE_EQL , SE_UNDS, SE_DLR ,                                     SE_HASH, OS_CTL , OS_SFT , OS_ALT , OS_GUI , _______,
     _______ , SE_PLUS, SE_PIPE, SE_AT  , SE_SLSH, SE_PERC, _______,                   _______, SE_QUOT, SE_BSLS, SE_AMPR, SE_QUES, SE_EXLM, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
   ),

/*
 * Num Layer: Numbers
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1   |  2   |  3   |  4   |  5   |                              |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | gui  | alt  | shft | ctrl | F11  |                              |  F12 | ctrl | shft |  alt |  gui |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |                |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBER] = LAYOUT(
      _______,  SE_1  ,  SE_2  ,  SE_3  ,  SE_4  ,  SE_5  ,                                      SE_6  ,  SE_7  ,  SE_8  ,  SE_9  ,  SE_0  , _______,
      _______, OS_GUI , OS_ALT , OS_SFT , OS_CTL , KC_F11 ,                                     KC_F12 , OS_CTL , OS_SFT , OS_ALT , OS_GUI , _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , KC_F5  , _______,                   _______,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Numbar
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  F7  |  F8  |  F9  | F12  |                              |      | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |  F4  |  F5  |  F6  | F11  |                              |  *   | 4 $  | 5 %  | 6 ^  | = +  |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |      |  F1  |  F2  |  F3  | F10  |      |                |      |      | 1 !  | 2 @  | 3 #  |  /   |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | 0 )  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBAR] = LAYOUT(
      _______, _______,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F12 ,                                     _______, SE_7,    SE_8,    SE_9, SE_MINS, _______,
      _______, _______,  KC_F4 ,  KC_F5 ,  KC_F6 , KC_F11 ,                                     SE_ASTR, SE_4,    SE_5,    SE_6, SE_PLUS, _______,
      _______, _______,  KC_F1 ,  KC_F2 ,  KC_F3 , KC_F10 , _______,                   _______, _______, SE_1,    SE_2,    SE_3, SE_SLSH, _______,
                                 _______, _______, _______, _______, _______, _______, _______, SE_0   , _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |                |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
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
  UJ_ARNG,
  OP_ARNG,
  IK_ADIA,
  LSEMICOLON_ADIA,
  OL_ODIA,
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
const uint16_t PROGMEM uj_combo[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM ik_combo[] = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM ol_combo[] = {KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM ksemicolon_combo[] = {KC_K, SE_SCLN, COMBO_END};
const uint16_t PROGMEM lsemicolon_combo[] = {KC_L, SE_SCLN, COMBO_END};
const uint16_t PROGMEM mcomma_combo[] = {KC_M, SE_COMM, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {SE_COMM, SE_DOT, COMBO_END};

combo_t key_combos[] = {
    [KL_ENT] = COMBO(kl_combo, KC_ENT),
    [XC_ESC] = COMBO(xc_combo, KC_ESC),
    [WE_TAB] = COMBO(we_combo, KC_TAB),
    [UJ_ARNG] = COMBO(uj_combo, SE_ARNG),
    [OP_ARNG] = COMBO(op_combo, SE_ARNG),
    [IK_ADIA] = COMBO(ik_combo, SE_ADIA),
    [LSEMICOLON_ADIA] = COMBO(lsemicolon_combo, SE_ADIA),
    [OL_ODIA] = COMBO(ol_combo, SE_ODIA),
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

bool sw_win_active = false;

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

    update_swapper(&sw_win_active, KC_LALT, KC_TAB, KC_LSFT, ALT_TAB, SA_TAB, keycode, record);

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
void left_encoder(bool clockwise) {
    if (layer_state_is(_SYM)) {
        if (clockwise) {
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
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
        left_encoder(clockwise);
    }
    return false;
}
// }}}

// vim: set foldmethod=marker:foldlevel=0
