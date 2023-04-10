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

// Define a type for every tap dance state you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_SINGLE_TAP,
    TD_DOUBLE_HOLD
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
  ENT_L1_L3,
  SPC_L2_L4
};

/* L0 - QWERTY
 * L1 - SYM1
 * L2 - SYM2
 * L3 - NAV3
 * L4 - FKEYS4
 * L5 - ADJUST5
 */

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ent_sft_finished(qk_tap_dance_state_t *state, void *user_data);
void ent_sft_reset(qk_tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * L0: Base Layer: QWERTY
 *
 * .----------------------------------------------.                                                           .-----------------------------------------------.
 * | ------ |   Q   |   W   |  E   |   R  |   T   |                                                           |   Y   |   U  |    I   |   O   |   P  | ------ |
 * |--------+-------+-------+------+------+-------|                                                           |-------+------+--------+-------+------+--------|
 * | ------ |   A   |   S   |  D   |   F  |   G   |                                                           |   H   |   J  |    K   |   L   | ;  : | ------ |
 * |--------+-------+-------+------+------+-------+-----------------.                       .-----------------+-------+------+--------+-------+------+--------|
 * | ------ |   Z   |   X   |  C   |   V  |   B   | ------- | ----- |                       | ----- | --------|   N   |   M  |  ,  <  | . >   | /  ? | ------ |
 * '------------------------+------+------+-------+---------+-------|                       |-------+---------+-------+------+--------+-----------------------'
 *                          | ---- | ---- |SFT/ALT|SPC/L2/L4|CMD/CTL|                       |CTL/CMD|ENT/L1/L3|SFT/ALT| ---- | ------ |
 *                          '---------------------------------------'                       '-----------------------------------------'
 */

    [_L0] = LAYOUT(
      XXXXXXX, KC_Q, KC_W, KC_E, KC_R, KC_T,                                                                KC_Y, KC_U,    KC_I,   KC_O,    KC_P,  XXXXXXX,
      XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G,                                                                KC_H, KC_J,    KC_K,   KC_L, KC_SCLN,  XXXXXXX,
      XXXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B,  XXXXXXX,  XXXXXXX,                          XXXXXXX, XXXXXXX, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  XXXXXXX,
      XXXXXXX, XXXXXXX, TD(LSFT_LALT), TD(SPC_L2_L4), TD(LGUI_LCTL),                      TD(LCTL_LGUI), TD(ENT_L1_L3), TD(RSFT_RALT), XXXXXXX, XXXXXXX
    ),

/*
 * L1: Sym Layer1: Numbers and symbols
 *
 * .------------------------------------------.                                                           .-------------------------------------------.
 * | ------ |  1   |  2   |  3   |  4   |  5  |                                                           |   6  |  7   |  8   |  9   |  0   | ------ |
 * |--------+------+------+------+------+-----|                                                           |------+------+------+------+------+--------|
 * | ------ |  !   |  @   |  #   |  $   |  %  |                                                           |   ^  |  &   |  *   |  (   |  )   | ------ |
 * |--------+------+------+------+------+-----+----------------.                             .--------------+------+------+------+------+------+--------|
 * | ------ |  ` ~ |  :   |   ;  |  - _ |  [  | ------ | ----- |                             | ----- | ---- |   ]  |  ' " |  \ | |      | / ?  | ------ |
 * '----------------------+------+------+-----+--------+-------|                             |-------+------+------+------+------+----------------------'
 *                     | ---- | ---- |SFT/ALT|SPC/L2/L4|CMD/CTL|                       |CTL/CMD|ENT/L1/L3|SFT/ALT| ---- | ------ |
 *                     '---------------------------------------'                       '-----------------------------------------'
 */
    [_L1] = LAYOUT(
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
      XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
      XXXXXXX,  KC_GRV, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, KC_RBRC, KC_QUOT, KC_BSLS, XXXXXXX, KC_SLSH, XXXXXXX,
      XXXXXXX, XXXXXXX, TD(LSFT_LALT), TD(SPC_L2_L4), TD(LGUI_LCTL),                       TD(LCTL_LGUI), TD(ENT_L1_L3), TD(RSFT_RALT), XXXXXXX, XXXXXXX
    ),

/*
 * L2: Sym Layer2: Numbers and symbols
 *
 * .--------------------------------------------.                                                         .-------------------------------------------.
 * | ------ | ESC  |   `  |      |      |       |                                                         |      |      |      |      | Bksp | ------ |
 * |--------+------+------+------+------+-------|                                                         |------+------+------+------+------+--------|
 * | ------ | TAB  |   ~  |      |      |       |                                                         |      |  :   |   '  |      |  +   | ------ |
 * |--------+------+------+------+------+-------+--------------.                            .-------------+------+------+------+------+------+--------|
 * | ------ |      |      |  /   |      |       | ---- | ----- |                            | ---- | ---- |      |  ;   |   \  |  |   |  =   | ------ |
 * '----------------------+------+------+-------+------+-------|                            |------+------+------+------+------+----------------------'
 *                          | ---- | ---- |SFT/ALT|SPC/L2/L4|CMD/CTL|                       |CTL/CMD|ENT/L1/L3|  L1  | ---- | ------ |
 *                          '---------------------------------------'                       '----------------------------------------'
 */
    [_L2] = LAYOUT(
      XXXXXXX, KC_ESC,  KC_GRV, XXXXXXX,  XXXXXXX, XXXXXXX,                                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX,
      XXXXXXX, KC_TAB, KC_TILD, XXXXXXX,  XXXXXXX, XXXXXXX,                                              XXXXXXX, KC_COLN, KC_QUOT, XXXXXXX, KC_PLUS, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, KC_SLSH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN, KC_BSLS, KC_PIPE, KC_EQL, XXXXXXX,
      XXXXXXX, XXXXXXX, TD(LSFT_LALT), TD(SPC_L2_L4), TD(LGUI_LCTL),                       TD(LCTL_LGUI), TD(ENT_L1_L3), TD(RSFT_RALT), XXXXXXX, XXXXXXX
    ),

/*
 * L3: Nav Layer: Media, navigation
 *
 * .--------------------------------------------.                                                          .------------------------------------------.
 * | ------ | ESC  |      |      |BrigUp| VolUp |                                                          | PgUp | Home |   ↑  | End  | Bksp | ----- |
 * |--------+------+------+------+------+-------|                                                          |------+------+------+------+------+-------|
 * | ------ | TAB  |      |      |BrigDn| VolDn |                                                          | PgDn |  ←   |   ↓  |   →  |  Del | ----- |
 * |--------+------+------+------+------+-------+--------------.                             .-------------+------+------+------+------+------+-------|
 * | ------ |      |      |      |      | Mute  | ---- | ----- |                             | ---- | ---- | Pause|M Prev|      |M Next|  Ins | ----- |
 * '----------------------+------+------+-------+------+-------|                             |------+------+------+------+------+---------------------'
 *                        | ---- | ---- |SFT/ALT| L0   |CMD/CTL|                            | L3   | L4   |  L5  | ---- | ---- |
 *                        '------------------------------------'                            '----------------------------------'
 */

    [_L3] = LAYOUT(
      XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX, KC_BRMU, KC_VOLU,                                               KC_PGUP, KC_HOME,   KC_UP,  KC_END,   KC_BSPC, XXXXXXX,
      XXXXXXX,  KC_TAB, XXXXXXX, XXXXXXX, KC_BRMD, KC_VOLD,                                               KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,    KC_DEL, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_PAUSE, KC_MPRV, XXXXXXX, KC_MNXT,    KC_INS, XXXXXXX,
      XXXXXXX, XXXXXXX, TD(LSFT_LALT), TD(SPC_L2_L4), TD(LGUI_LCTL),                       TD(LCTL_LGUI), TD(ENT_L1_L3), TD(RSFT_RALT), XXXXXXX, XXXXXXX
    ),

/*
 * L4: Function Layer: Function keys
 *
 * .---------------------------------------------.                                                      .-------------------------------------------.
 * | ------ |  F9  | F10  | F11  | F12  |        |                                                      |      |   7  |  8   |  9   |      | ------ |
 * |--------+------+------+------+------+--------|                                                      |------+------+------+------+------+--------|
 * | ------ |  F5  |  F6  |  F7  |  F8  |        |                                                      |      |   4  |  5   |  6   |      | ------ |
 * |--------+------+------+------+------+--------+--------------.                         .-------------+------+------+------+------+------+--------|
 * | ------ |  F1  |  F2  |  F3  |  F4  |        | ---- | ----- |                         | ---- | ---- |   0  |   1  |  2   |  3   |      | ------ |
 * '----------------------+------+------+--------+------+-------|                         |------+------+------+------+------+----------------------'
 *                        | ---- | -----|SFT/ALT|  L0  |CMD/CTL|                             | L2   | L4   | L5   | ---- | ---- |
 *                        '------------------------------------'                             '----------------------------------'
 */
    [_L4] = LAYOUT(
      XXXXXXX, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX,                                                XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_F5,  KC_F6,  KC_F7,  KC_F8, XXXXXXX,                                                XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_F1,  KC_F2,  KC_F3,  KC_F4, XXXXXXX, XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, KC_0, KC_1, KC_2, KC_3, XXXXXXX,
      XXXXXXX, XXXXXXX, TD(LSFT_LALT), TD(SPC_L2_L4), TD(LGUI_LCTL),                       TD(LCTL_LGUI), TD(ENT_L1_L3), TD(RSFT_RALT), XXXXXXX, XXXXXXX
    ),

/*
 * L5: Adjust Layer: Default layer settings, RGB, Reset key
 *
 * .--------------------------------------------.                                                        .-------------------------------------------.
 * | ------ | RESET|      |QWERTY|      |       |                                                        |      |      |      |      |      | ------ |
 * |--------+------+------+------+------+-------|                                                        |------+------+------+------+------+--------|
 * | ------ |      |      |      |      |       |                                                        | TOG  | SAI  | HUI  | VAI  | MOD  | ------ |
 * |--------+------+------+------+------+-------+--------------.                           .-------------+------+------+------+------+------+--------|
 * | ------ |      |      |      |      |       | ---- | ----- |                           | ---- | ---- |      | SAD  | HUD  | VAD  | RMOD | ------ |
 * '----------------------+------+------+-------+------+-------|                           |------+------+------+------+------+----------------------'
 *                        | ---- | ---- | SFT/ALT|  L0  |CMD/CTL|                         | L1   |  L2  | L3   | ---- | ---- |
 *                        '-------------------------------------'                         '----------------------------------'
 */
    [_L5] = LAYOUT(
      XXXXXXX,   QK_RBT, XXXXXXX, L0, XXXXXXX, XXXXXXX,                                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                              RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, XXXXXXX,
      XXXXXXX, XXXXXXX, TD(LSFT_LALT), TD(SPC_L2_L4), TD(LGUI_LCTL),                       TD(LCTL_LGUI), TD(ENT_L1_L3), TD(RSFT_RALT), XXXXXXX, XXXXXXX
    ),
};

// clang-format on

// BEGIN OLED CONFIG //
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    render_status();
    return false;
}
#endif
// END OLED CONFIG //


// BEGIN ENCODER CONFIG //
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
// END ENCODER CONFIG //


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else return TD_UNKNOWN;
}

// BEGIN TapDance ENT_L1_L3 //
// Initialize tap structure associated with tap dance key
static td_tap_t ent_l1_l3_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ent_l1_l3_finished(qk_tap_dance_state_t *state, void *user_data) {
    ent_l1_l3_tap_state.state = cur_dance(state);
    switch (ent_l1_l3_tap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_ENT); break;
        case TD_DOUBLE_TAP: tap_code(KC_ENT); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_ENT); tap_code(KC_ENT); break;
        case TD_SINGLE_HOLD: layer_on(_L1); break;
        case TD_DOUBLE_HOLD: layer_on(_L3); break;
        default: break;
    }

}

void ent_l1_l3_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ent_l1_l3_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_L1);
    }
    if (ent_l1_l3_tap_state.state == TD_SINGLE_TAP) {
        unregister_code16(KC_ENT);
    }
    if (ent_l1_l3_tap_state.state == TD_DOUBLE_TAP) {
        unregister_code16(KC_ENT);
    }
    if (ent_l1_l3_tap_state.state == TD_DOUBLE_SINGLE_TAP) {
        unregister_code16(KC_ENT);
    }
    if (ent_l1_l3_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_L3);
    }
    ent_l1_l3_tap_state.state = TD_NONE;
}
// END TapDance ENT_L1_L3 //


// BEGIN TapDance SPC_L2_L4 //
// Initialize tap structure associated with tap dance key
static td_tap_t spc_l2_l4_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void spc_l2_l4_finished(qk_tap_dance_state_t *state, void *user_data) {
    spc_l2_l4_tap_state.state = cur_dance(state);
    switch (spc_l2_l4_tap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_SPC); break;
        case TD_DOUBLE_TAP: tap_code(KC_SPC); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SPC); tap_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_on(_L2); break;
        case TD_DOUBLE_HOLD: layer_on(_L4); break;
        default: break;
    }
}

void spc_l2_l4_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (spc_l2_l4_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_L2);
    }
    if (spc_l2_l4_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_L4);
    }
    if (spc_l2_l4_tap_state.state == TD_SINGLE_TAP) {
        unregister_code16(KC_SPC);
    }
    if (spc_l2_l4_tap_state.state == TD_DOUBLE_TAP) {
        unregister_code16(KC_SPC);
    }
    if (spc_l2_l4_tap_state.state == TD_DOUBLE_SINGLE_TAP) {
        unregister_code16(KC_SPC);
    }
    spc_l2_l4_tap_state.state = TD_NONE;
}
// END TapDance SPC_L2_L4 //


// Associate tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    //[ENT_SYM] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ent_sym_finished, ent_sym_reset, 100), // override default tapping term
    [ENT_L1_L3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ent_l1_l3_finished, ent_l1_l3_reset),
    [SPC_L2_L4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_l2_l4_finished, spc_l2_l4_reset),
    [LGUI_LCTL] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LCTL),
    [LCTL_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
    [LSFT_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LALT),
    [RSFT_RALT] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_RALT)
};

