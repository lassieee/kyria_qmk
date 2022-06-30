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

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance keys
enum {
  LGUI_LCTL,
  LCTL_LGUI,
  ENT_SYM
};

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

// #define CTL_ESC  MT(MOD_LCTL, KC_ESC)
// #define CTL_MINS MT(MOD_RCTL, KC_MINUS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: QWERTY
 *
 * ,-----------------------------------------------.                                                  ,------------------------------------------------.
 * |  Esc   |   Q   |   W   |    E   |   R  |   T  |                                                  |   Y    |   U  |    I   |   O   |   P  |  Bksp  |
 * |--------+-------+-------+--------+------+------|                                                  |--------+------+--------+-------+------+--------|
 * | Tab/Nav|   A   |   S   |    D   |   F  |   G  |                                                  |   H    |   J  |    K   |   L   | ;  : |  ' "   |
 * |--------+-------+-------+--------+------+------+-------+-------.                 ,----------------+--------+------+--------+-------+------+--------|
 * | LShft  |   Z   |   X   |    C   |   V  |   B  |       |       |                 |        |       |   N    |   M  |  ,  <  | . >   | /  ? |   - _  |
 * '-----------------------------+------+---+------+-------|-------|                 |--------+-------+--------+------+--------+-----------------------'
 *                            |Adjust| LAlt |LShft | Space | LGUI/ |                 |  LCTL/ | Enter/| RShift | RALT | F-keys |
 *                            |      |      |      |       | LCTL  |                 |  LGUI  | SYM   |        |      |        |
 *                            '------------------------------------'                 '-----------------------------------------'
 */

    [_QWERTY] = LAYOUT(
     KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,                                                            KC_Y,  KC_U,   KC_I,    KC_O,   KC_P,    KC_BSPC,
     LT(NAV,KC_TAB),  KC_A, KC_S, KC_D, KC_F, KC_G,                                                    KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOTE,
     KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  _______,  _______,                 _______, _______, KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
                  ADJUST, KC_LALT, KC_LSFT, KC_SPACE, TD(LGUI_LCTL),                 TD(LCTL_LGUI), TD(ENT_SYM), KC_RSFT, KC_RALT, FKEYS
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |  RESET |      |      |      |scrnsht|     |                                                     | PgUp | Home |   ↑  | End  | VolUp| Delete |
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
      RESET,   _______, _______, _______, LSG(KC_4), _______,                                            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
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
 * |    |   |   \  |  :   |  ;   |  -   |  [   |      |      |                         |      |      |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        |      |      |      |      |      |                         |      |      |      |      |      |
 *                        '----------------------------------'                         '----------------------------------'
 */
    [_SYM] = LAYOUT(
     KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,
     KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE, KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, _______, _______,           _______, _______, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                                                     |      |      |      |      |      | RESET  |
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
      _______,  KC_F9,  KC_F10, KC_F11, KC_F12,    _______,                                                       _______, _______, _______, _______, _______, RESET,
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

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            // Check to see if the layer is already set
            if (layer_state_is(_SYM)) {
                // If already set, then switch it off
                layer_off(_SYM);
            } else {
                // If not already set, then switch the layer on
                layer_on(_SYM);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_SYM);
    }
    if (ql_tap_state.state == TD_SINGLE_TAP) {
        unregister_code16(KC_ENT);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [ENT_SYM] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [LGUI_LCTL] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LCTL),
    [LCTL_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
};
