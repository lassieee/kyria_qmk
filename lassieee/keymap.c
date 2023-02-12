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

#include "keycodes.h"

#ifdef OLED_ENABLE
#    include "oled_utils.h"
#endif

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
  LSFT_LALT,
  RSFT_RALT,
  ENT_L1
};

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ent_l1_finished(qk_tap_dance_state_t *state, void *user_data);
void ent_l1_reset(qk_tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * L0 - Base Layer: QWERTY
 *
 * ,-----------------------------------------------.                                                  ,-----------------------------------------------.
 * |  Esc   |   Q   |   W   |    E   |   R  |   T  |                                                  |   Y    |   U  |    I   |   O   |   P  |  Bksp |
 * |--------+-------+-------+--------+------+------|                                                  |--------+------+--------+-------+------+-------|
 * | Tab/L2 |   A   |   S   |    D   |   F  |   G  |                                                  |   H    |   J  |    K   |   L   | ;  : |  ' "  |
 * |--------+-------+-------+--------+------+------+-------+-------.                 ,----------------+--------+------+--------+-------+------+-------|
 * |   L3   |   Z   |   X   |    C   |   V  |   B  |       |       |                 |        |       |   N    |   M  |  ,  <  | . >   | /  ? |   - _ |
 * '--------------------------+------+------+------+-------+-------|                 |--------+-------+--------+------+--------+----------------------'
 *                            |      |      |LShft/| Space | LGUI/ |                 |  LCTL/ | Enter/| RShft/ |      |        |
 *                            |      |      | LALT |       | LCTL  |                 |  LGUI  |  L1   |  RALT  |      |        |
 *                            '------------------------------------'                 '-----------------------------------------'
 */

    [_L0] = LAYOUT(
     KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,                                                            KC_Y,  KC_U,   KC_I,    KC_O,   KC_P,    KC_BSPC,
     LT(L2,KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,                                                      KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOTE,
         L3, KC_Z,  KC_X, KC_C, KC_V, KC_B,  _______,  _______,                      _______, _______, KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
           _______, _______, TD(LSFT_LALT), KC_SPACE, TD(LGUI_LCTL),                 TD(LCTL_LGUI), TD(ENT_L1), TD(RSFT_RALT), _______, _______
    ),

/*
 * L1 - Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                                                     |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                                                     |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |      |      |                         |      |      |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |LShft/| Space|LGUI/ |                         | LCTL/|Enter/|RShft/|      |      |
 *                        |      |      | LALT |      |LCTL  |                         | LGUI | L1   | RALT |      |      |
 *                        '----------------------------------'                         '----------------------------------'
 */
    [_L1] = LAYOUT(
     KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,
     KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE, KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, _______, _______,           _______, _______, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
    ),

/*
 * L2 - Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |  RESET |      |      |      |scrnsht|     |                                                     | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                                                     | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |                         |      |      | Pause|M Prev|      |M Next|VolMut| PrtSc  |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |LShft/| Space|LGUI/ |                         | LCTL/|Enter/|RShft/|      |      |
 *                        |      |      | LALT |      |LCTL  |                         | LGUI | L1   | RALT |      |      |
 *                        '----------------------------------'                         '----------------------------------'
 */
    [_L2] = LAYOUT(
     QK_RBT, _______, _______, _______, LSG(KC_4), _______,                                              KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                              KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
      _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,KC_PAUSE, KC_MPRV, _______, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    ),

/*
 * L3 - Function + Adjust layer: F-keys and RGB keys
 *
 * ,-------------------------------------------.                                                     ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                                                     |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                                                     | TOG  | SAI  | HUI  |  VAI |  MOD |        |
 * |--------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |                         |      |      |      | SAD  | HUD  |  VAD |  RMOD|        |
 * '----------------------+------+------+------+------+------|                         |------+------+------+------+------+----------------------'
 *                        |      |      |LShft/| Space|LGUI/ |                         | LCTL/|Enter/|RShft/|      |      |
 *                        |      |      | LALT |      |LCTL  |                         | LGUI | L1   | RALT |      |      |
 *                        '----------------------------------'                         '----------------------------------'
 */
    [_L3] = LAYOUT(
      _______,  KC_F9,  KC_F10, KC_F11, KC_F12,    _______,                                                       _______, _______, _______,  _______, _______, _______,
      _______,  KC_F5,   KC_F6,   KC_F7,   KC_F8,  _______,                                                       RGB_TOG, RGB_SAI, RGB_HUI,  RGB_VAI, RGB_MOD, _______,
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______, _______,                   _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    render_status();
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ent_l1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ent_l1_finished(qk_tap_dance_state_t *state, void *user_data) {
    ent_l1_tap_state.state = cur_dance(state);
    switch (ent_l1_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_ENT);
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            // Check to see if the layer is already set
            if (layer_state_is(_L1)) {
                // If already set, then switch it off
                layer_off(_L1);
            } else {
                // If not already set, then switch the layer on
                layer_on(_L1);
            }
            break;
        default:
            break;
    }
}

void ent_l1_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ent_l1_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_L1);
    }
    if (ent_l1_tap_state.state == TD_SINGLE_TAP) {
        unregister_code16(KC_ENT);
    }
    if (ent_l1_tap_state.state == TD_DOUBLE_TAP) {
        unregister_code16(KC_ENT);
    }
    ent_l1_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    //[ENT_L1] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, L1),
    //[ENT_L1] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ent_l1_finished, ent_l1_reset, 100), // override default tapping term
    [ENT_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ent_l1_finished, ent_l1_reset),
    [LGUI_LCTL] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LCTL),
    [LCTL_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
    [LSFT_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LALT),
    [RSFT_RALT] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_RALT)
};
