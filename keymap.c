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

// Layers
enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};

// Tap Dance declarations
enum {
  TD_LSHFT_LALT,
  TD_RSHFT_RALT,
  TD_RGUI_ENT,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LSHFT_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LALT),
  [TD_RSHFT_RALT] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_RALT),
  [TD_RGUI_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_RGUI, KC_ENT),
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

// #define CTL_ESC  MT(MOD_LCTL, KC_ESC)
// #define CTL_MINS MT(MOD_RCTL, KC_MINUS)
// #define ALT_ENT  MT(MOD_LALT, KC_ENT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: QWERTY
 *
 * ,-----------------------------------------------.                                                 ,------------------------------------------------.
 * |  Esc   |   Q   |   W   |    E   |   R  |   T  |                                                 |   Y    |   U  |    I   |   O   |   P  |  Bksp  |
 * |--------+-------+-------+--------+------+------|                                                 |--------+------+--------+-------+------+--------|
 * |  Tab   |   A   |   S   |    D   |   F  |   G  |                                                 |   H    |   J  |    K   |   L   | ;  : |  ' "   |
 * |--------+-------+-------+--------+------+------+-------+-------.                ,----------------+--------+------+--------+-------+------+--------|
 * | LShft  |   Z   |   X   |    C   |   V  |   B  |  [ {  |  Nav  |                |  RGUI  |  ] }  |   N    |   M  |  ,  <  | . >   | /  ? |   - _  |
 * '-----------------------------+------+---+------+-------|-------|                |--------+-------+--------+------+--------+-----------------------'
 *                            |Adjust| LAlt |LShft | Space/|  LGUI |                |  Sym   | Enter/| RShift | RALT | F-keys |
 *                            |      |      |      | LCtrl |       |                |        | LCTL  |        |      |        |
 *                            '------------------------------------'                '-----------------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                                                        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
     KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,                                                             KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOTE,
     KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_LBRC,  NAV,                         KC_RGUI, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
                        ADJUST, KC_LALT, KC_LSFT, MT(MOD_LCTL,KC_SPACE), KC_LGUI,       SYM, MT(MOD_LCTL,KC_ENT), KC_RSFT, KC_RALT, FKEYS
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |        |      |      |      |      |      |                                                     | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                                                     | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |                         |      |      | Pause|M Prev|      |M Next|VolMut| PrtSc  |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        `----------------------------------'                         '----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                              KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                              KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
      _______, _______, _______, _______, _______, _______, _______, KC_SLCK,          _______, _______,KC_PAUSE, KC_MPRV, _______, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                                                     |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                                                     |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |                         |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        '----------------------------------'                         '----------------------------------'
 */
    [_SYM] = LAYOUT(
      KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,
     KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE, KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______,           _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                                                     |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                                                     |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |                         |      |      |      |      |      |      |      |        |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        '----------------------------------'                         '----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F9,  KC_F10, KC_F11, KC_F12,    _______,                                                       _______, _______, _______, _______, _______, _______,
      _______,  KC_F5,   KC_F6,   KC_F7,   KC_F8,  _______,                                                       _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                                                     |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                                                     | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |                         |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        `----------------------------------'                         `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______,  QWERTY, _______, _______,                                              _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                              RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, _______, _______, _______,_______, _______,           _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______,           _______, _______, _______, _______, _______
    ),
};
