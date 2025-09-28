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
#include "features/keymap_swedish_mac_ansi.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

// {{{ tap dances
enum td_keycodes {
    TD_CAPS,
    TD_SYMB,
    TD_MAC_SYMB
};

void td_sym_tap_fn(tap_dance_state_t *state, void *user_data);
void td_sym_reset_fn(tap_dance_state_t *state, void *user_data);

void mac_td_sym_tap_fn(tap_dance_state_t *state, void *user_data);
void mac_td_sym_reset_fn(tap_dance_state_t *state, void *user_data);

void dance_capsword(tap_dance_state_t *state, void *user_data) {
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

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN(dance_capsword),
    [TD_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(td_sym_tap_fn, NULL, td_sym_reset_fn),
    [TD_MAC_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(mac_td_sym_tap_fn, NULL, mac_td_sym_reset_fn),
};

#define TD_CPS TD(TD_CAPS)
#define TD_SYM TD(TD_SYMB)
#define TD_MC_S TD(TD_MAC_SYMB)
// }}}

// {{{ layers

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUMBER,
    _MAC_QWE,
    _MAC_NAV,
    _MAC_SYM,
    _MAC_NUMBER,
    _MOUSE,
    _NUMBAR,
    _ADJUST,
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
    MC_TAB,
    MC_STAB,
    MC_TICK,
    MC_STICK,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define NUMBER   MO(_NUMBER)
#define MAC_QWE  DF(_MAC_QWE)
#define MAC_SYM  MO(_MAC_SYM)
#define MAC_NAV  MO(_MAC_NAV)
#define MAC_NUM  MO(_NUMBER)
#define NUMBAR   MO(_NUMBAR)
#define ADJUST   MO(_ADJUST)

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
 * |        |   Z  |   X  |   C  |   V  |   B  | MCTL |                |ADJUST|   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |Caps- | Nav  |Shift |Numbar|  |      | Space| Sym  | BSPC |      |
 *                        |      |Word  |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     _______ ,   SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,                                        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P , _______,
     _______ ,   SE_A ,  SE_S  ,  SE_D  ,   SE_F ,   SE_G ,                                        SE_H,   SE_J ,   SE_K ,   SE_L , SE_SCLN, _______,
     _______ ,   SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B , KC_MCTL,                    ADJUST,    SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH, _______,
                                _______ , TD_CPS ,   NAV  , KC_LSFT, NUMBAR , _______,  KC_SPC,  TD_SYM, KC_BSPC, _______
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
                                 _______, _______, _______, _______, _______, _______, _______,  TD_SYM, _______, _______
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
 * Mac Base Layer: MAC_QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |                |ADJUST|   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |Caps- | Nav  |Shift |Numbar|  |      | Space| Sym  | BSPC |      |
 *                        |      |Word  |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MAC_QWE] = LAYOUT(
     _______ ,   AP_Q ,  AP_W  ,  AP_E  ,   AP_R ,   AP_T ,                                        AP_Y,   AP_U ,   AP_I ,   AP_O ,   AP_P , _______,
     _______ ,   AP_A ,  AP_S  ,  AP_D  ,   AP_F ,   AP_G ,                                        AP_H,   AP_J ,   AP_K ,   AP_L , AP_SCLN, _______,
     _______ ,   AP_Z ,  AP_X  ,  AP_C  ,   AP_V ,   AP_B , KC_MCTL,                    ADJUST,    AP_N,   AP_M , AP_COMM, AP_DOT , AP_SLSH, _______,
                                _______ , TD_CPS ,MAC_NAV , KC_LSFT, NUMBAR , _______,  KC_SPC, TD_MC_S, KC_BSPC, _______
    ),
/*
 * Mac_Nav Layer: Mac Media, navigation, F-keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  tab |alttab|ALTTAB|alt+` |ALT+` |                              | PgDn | PgUp | Home | End  | VolUp|        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  gui | alt  | shft | ctrl |Ctrl-b|                              |  ←   |  ↓   |  ↑   |   →  | VolDn|        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |PrtSc |      |      |      |      |      |                |      | Pause|M Prev|M Play|M Next|VolMut|        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |Number|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MAC_NAV] = LAYOUT(
      _______, KC_TAB , MC_STAB, MC_TAB , MC_TICK,MC_STICK,                                     KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU, _______,
      _______, OS_GUI , OS_ALT , OS_SFT , OS_CTL , C(KC_B),                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD, _______,
      _______, KC_PSCR, _______, _______, _______, _______, _______,                   _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Mac Sym Layer: Mac Symbols
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
    [_MAC_SYM] = LAYOUT(
     _______ , KC_ESC , AP_LCBR, AP_LBRC, AP_LPRN,SE_TILDE,                                     SE_HATT, AP_RPRN, AP_RBRC, AP_RCBR,SE_GRAVE, _______,
     _______ , AP_MINS, AP_ASTR, AP_EQL , AP_UNDS, AP_DLR ,                                     AP_HASH, OS_CTL , OS_SFT , OS_ALT , OS_GUI , _______,
     _______ , AP_PLUS, AP_PIPE, AP_AT  , AP_SLSH, AP_PERC, _______,                   _______, AP_QUOT, AP_BSLS, AP_AMPR, AP_QUES, AP_EXLM, _______,
                                 _______, _______, _______, _______, _______, _______, _______, TD_MC_S, _______, _______
   ),

/*
 * Mac Num Layer: Mac Numbers
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
    [_MAC_NUMBER] = LAYOUT(
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
/*
 * Sym2 Layer: Mouse stuff
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |MOUSE1|MOUSE2|      |                              |  ←   |  ↓   |  ↑   |   →  |      |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |                |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOUSE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, KC_BTN1, KC_BTN2, _______,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------.                ,------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |                |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------.  ,------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, QWERTY , _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, MAC_QWE, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
    state = update_tri_layer_state(state, _SYM, _NAV, _NUMBER);
    state = update_tri_layer_state(state, _MAC_SYM, _MAC_NAV, _MAC_NUMBER);
    return state;
}

// }}}

// {{{ key overrides
// Add key overrides to emulate american layout on swedish keyboard
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_SCLN, SE_COLN);  // shift + ; -> :
const key_override_t squo_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUOT, SE_DQUO);  // shift + ' -> "

const key_override_t labk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, SE_COMM, SE_LABK, 1 << _QWERTY);  // shift + , -> <
const key_override_t rabk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, SE_DOT, SE_RABK, 1 << _QWERTY);   // shift + . -> >

const key_override_t mac_labk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, AP_COMM, AP_LABK, 1 << _MAC_QWE);  // shift + , -> <
const key_override_t mac_rabk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, AP_DOT, AP_RABK, 1 << _MAC_QWE);   // shift + . -> >

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL); // shift + backspace -> Del

const key_override_t *key_overrides[] = {
    &coln_key_override,
    &squo_key_override,
    &labk_key_override,
    &rabk_key_override,
    &mac_labk_key_override,
    &mac_rabk_key_override,
    &delete_key_override,
};

// }}}

// {{{ combos

enum combo_events {
  JKL_ENT,
  XC_ESC,
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

const uint16_t PROGMEM jkl_combo[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM uj_combo[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM ik_combo[] = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM ol_combo[] = {KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM ksemicolon_combo[] = {KC_K, SE_SCLN, COMBO_END};
const uint16_t PROGMEM lsemicolon_combo[] = {KC_L, SE_SCLN, COMBO_END};
const uint16_t PROGMEM mcomma_combo[] = {KC_M, SE_COMM, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {SE_COMM, SE_DOT, COMBO_END};

combo_t key_combos[] = {
    [JKL_ENT] = COMBO(jkl_combo, KC_ENT),
    [XC_ESC] = COMBO(xc_combo, KC_ESC),
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
    case TD_SYM:
    case NAV:
    case MAC_SYM:
    case TD_MC_S:
    case MAC_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case TD_SYM:
    case NAV:
    case MAC_SYM:
    case TD_MC_S:
    case MAC_NAV:
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
bool mac_sw_app_active = false;
bool mac_sw_win_active = false;

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
    update_swapper(&mac_sw_app_active, KC_LGUI, KC_TAB, KC_LSFT, MC_TAB, MC_STAB, keycode, record);
    update_swapper(&mac_sw_win_active, KC_LGUI, AP_LABK, KC_LSFT, MC_TICK, MC_STICK, keycode, record);

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
    if (layer_state_is(_MOUSE)) {
        if (clockwise) {
            tap_code16(KC_MS_WH_DOWN);
        } else {
            tap_code16(KC_MS_WH_UP);
        }
    } else if (layer_state_is(_SYM)) {
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

void right_encoder(bool clockwise) {
    if (layer_state_is(_NAV)) {
        if (clockwise) {
            SEND_STRING("g+");
        } else {
            SEND_STRING("g-");
        }
    } else {
        if (clockwise) {
            tap_code16(LCTL(SE_R));
        } else {
            tap_code(SE_U);
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // Left encoder
        left_encoder(clockwise);
    } else if (index == 1) { // Right encoder
        right_encoder(clockwise);
    }
    return false;
}
// }}}

// {{{ tap dance function definitions
void td_sym_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_SYM);
    } else if (state->count == 2) {
        layer_on(_MOUSE);
    }
}

void td_sym_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_MOUSE);
    layer_off(_SYM);
};

void mac_td_sym_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_MAC_SYM);
    } else if (state->count == 2) {
        layer_on(_MOUSE);
    }
}

void mac_td_sym_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_MOUSE);
    layer_off(_MAC_SYM);
};
// }}}


// vim: set foldmethod=marker:foldlevel=0
