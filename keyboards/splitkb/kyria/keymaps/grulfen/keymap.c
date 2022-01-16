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
    } else {
        enable_xcase_with(SE_UNDS);
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
    _NUMBAR,
};

enum custom_keycodes {
    CAPSWORD = SAFE_RANGE,
    SNEKCASE,
    SE_TILDE,
    SE_GRAVE,
    SE_HATT,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      OSL(_SYM)
#define NAV      OSL(_NAV)
#define NUMBAR   MO(_NUMBAR)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define SFT_SPC  MT(MOD_LSFT, KC_SPC)
#define RSFT_SPC MT(MOD_RSFT, KC_SPC)
#define AGR_BSP  MT(MOD_RALT, KC_BSPC)

// Left-hand home row mods
#define GUI_A LGUI_T(SE_A)
#define ALT_S LALT_T(SE_S)
#define SFT_D LSFT_T(SE_D)
#define CTL_F LCTL_T(SE_F)

// Right-hand home row mods
#define CTL_J RCTL_T(SE_J)
#define SFT_K RSFT_T(SE_K)
#define ALT_L LALT_T(SE_L)
#define GUI_ODIA RGUI_T(SE_ODIA)

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
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  | [ {  |      |  |      |  ] } |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | SE/US|Caps- |Enter/|Numbar| Nav  |  | Sym  | Space| Sym  | AltGr| RGUI |
 *                        |      |Word  | Nav  |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  ,   SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,                                        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P , SE_ARNG,
     KC_ESC  ,   GUI_A,  ALT_S ,  SFT_D ,  CTL_F ,   SE_G ,                                        SE_H,   CTL_J,   SFT_K,   ALT_L, SE_ODIA, SE_ADIA,
     _______ ,   SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B , SE_LBRC, _______, _______, SE_RBRC,    SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH, _______,
                     KEY_OVERRIDE_TOGGLE, TD_CPS , NAV_ENT, NUMBAR ,  NAV   , SYM    ,  KC_SPC,     SYM, KC_RALT, KC_RGUI
    ),
/*
 * Nav Layer: Media, navigation, F-keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              | PgDn | PgUp | Home | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |Ctrl-b|                              |  ←   |  ↓   |  ↑   |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | Bspc |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU, KC_DEL ,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , C(KC_B),                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD, KC_INS ,
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
 * |    |   |   \  |  [   |  ]   |  -   |      |      |      |  |      |      |      |  _   |  {   |  }   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     SE_GRAVE,   SE_1 ,   SE_2 ,   SE_3 ,   SE_4 ,   SE_5 ,                                       SE_6 ,   SE_7 ,   SE_8 ,   SE_9 ,   SE_0 , SE_EQL ,
     SE_TILDE, SE_EXLM,  SE_AT , SE_HASH,  SE_DLR, SE_PERC,                                     SE_HATT, SE_AMPR, SE_ASTR, SE_LPRN, SE_RPRN, SE_PLUS,
     SE_PIPE , SE_BSLS, SE_LBRC, SE_RBRC, SE_MINS, _______, _______, _______, _______, _______, _______, SE_UNDS, SE_LCBR, SE_RCBR, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Numbar
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |  *   | 4 $  | 5 %  | 6 ^  | = +  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | 1 !  | 2 @  | 3 #  |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | 0 )  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBAR] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, SE_7,    SE_8,    SE_9, SE_MINS, _______,
      _______, _______, _______, _______, _______, _______,                                     SE_ASTR, SE_4,    SE_5,    SE_6, SE_PLUS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SE_1,    SE_2,    SE_3, SE_SLSH, _______,
                                 _______, _______, _______, _______, _______, _______, _______, SE_0   , _______, _______
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

// {{{ key overrides
// Add key overrides to emulate american layout on swedish keyboard
// ä and ö are available under ctrl modifier
const key_override_t adia_key_override = ko_make_basic(MOD_MASK_CTRL, SE_ADIA, SE_ADIA);   // ctrl + ä -> ä
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_ADIA, SE_DQUO);  // shift + ä -> "
const key_override_t quot_key_override = ko_make_basic(0, SE_ADIA, SE_QUOT);               // ä -> '

const key_override_t odia_key_override = ko_make_basic(MOD_MASK_CTRL, SE_ODIA, SE_ODIA);   // ctrl + ö -> ö
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_ODIA, SE_COLN); // shift + ö -> :
const key_override_t scln_key_override = ko_make_basic(0, SE_ODIA, SE_SCLN);               // ö -> ;

const key_override_t labk_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_COMM, SE_LABK);  // shift + , -> <
const key_override_t rabk_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_DOT, SE_RABK);   // shift + . -> >
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_SLSH, SE_QUES);  // shift + / -> ?

const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_LBRC, SE_LCBR);  // shift + [ -> {
const key_override_t rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_RBRC, SE_RCBR);  // shift + ] -> }

const key_override_t **key_overrides = (const key_override_t *[]) {
    &adia_key_override,
    &dquo_key_override,
    &quot_key_override,

    &odia_key_override,
    &coln_key_override,
    &scln_key_override,

    &labk_key_override,
    &rabk_key_override,
    &ques_key_override,

    &lcbr_key_override,
    &rcbr_key_override,

    NULL,
};

// }}}

// {{{ combos
//
//
enum combo_events {
  IO_BSPC,
  KL_ENT,
  XC_ESC,
  WE_TAB,
  MCOMMA_MINS,
  COMMADOT_UNDS,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {SFT_K, ALT_L, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM mcomma_combo[] = {KC_M, SE_COMM, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {SE_COMM, SE_DOT, COMBO_END};

combo_t key_combos[] = {
    [IO_BSPC] = COMBO(io_combo, KC_BSPC),
    [KL_ENT] = COMBO(kl_combo, KC_ENT),
    [XC_ESC] = COMBO(xc_combo, KC_ESC),
    [WE_TAB] = COMBO(we_combo, KC_TAB),
    [MCOMMA_MINS] = COMBO(mcomma_combo, SE_MINS),
    [COMMADOT_UNDS] = COMBO(commadot_combo, SE_UNDS),
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

// {{{ process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    // Regular user keycode case statement
    switch (keycode) {
        case CAPSWORD:
            if (record->event.pressed) {
                enable_caps_word();
                enable_xcase_with(SE_UNDS);
            }
            return false;
        case SNEKCASE:
            if (record->event.pressed) {
                enable_xcase_with(SE_UNDS);
            }
            return false;
        case SE_TILDE:
            if (record->event.pressed) {
                SEND_STRING("~ ");
            }
            return true;
        case SE_GRAVE:
            if (record->event.pressed) {
                SEND_STRING("` ");
            }
            return true;
        case SE_HATT:
            if (record->event.pressed) {
                SEND_STRING("^ ");
            }
            return true;
        default:
            return true;
    }
}

// }}}

// vim: set foldmethod=marker:foldlevel=0
