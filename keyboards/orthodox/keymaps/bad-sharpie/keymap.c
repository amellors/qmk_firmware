/*
This is the keymap for the keyboard

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "orthodox.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _NAV 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NAV,
  CC_ARRW,
  CC_PRN,
  CC_BRC,
  CC_CBR,
  KC_RESET
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define NAV_TAP LT(_NAV, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*[_QWERTY] = KEYMAP( \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, \
    KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      TT(_RAISE), TT(_LOWER),         TT(_LOWER), TT(_RAISE)      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_GRV, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    NAV_TAP, KC_LSFT, KC_LCTL,         KC_LALT, KC_LGUI, KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT \
  ),*/
  [_QWERTY] = KEYMAP( \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, \
    KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          TT(_RAISE), TT(_LOWER),     TT(_LOWER), TT(_RAISE),      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_GRV, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC, KC_LSFT, KC_LCTL,         KC_LALT, KC_LGUI, KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT \
  ),

  [_LOWER] = KEYMAP( \
    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                                  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
    KC_INS,   _______, _______, CC_PRN,  CC_BRC,  CC_CBR,           _______, _______,          _______, _______,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
    KC_RESET, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU \
  ),

  [_RAISE] = KEYMAP( \
    KC_ESC, KC_AMPR, KC_ASTR, KC_UNDS, KC_LPRN, KC_RPRN,                                                                KC_7,    KC_8,    KC_9,    KC_EQL,  _______, _______, \
    _______, KC_DLR,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,          _______, _______,          _______, _______,          KC_4,    KC_5,    KC_6,    KC_MINS, KC_PLUS, _______, \
    CC_ARRW, KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR, _______, _______, _______,          _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_BSLS, KC_PIPE \
  ),

  [_NAV] =  KEYMAP( \
    _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                                                                _______, _______, _______, _______, _______, _______,  \
    _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT,          _______, _______,          _______, _______,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
    switch(keycode) {
      case CC_ARRW:
      if (record->event.pressed) {
        SEND_STRING("->");
        return false;
      }
      case CC_PRN:
      if (record->event.pressed) {
        SEND_STRING("()"SS_TAP(X_LEFT));
        return false;
      }
      case CC_BRC:
      if (record->event.pressed) {
        SEND_STRING("[]"SS_TAP(X_LEFT));
        return false;
      }
      case CC_CBR:
      if (record->event.pressed) {
        SEND_STRING("{}"SS_TAP(X_LEFT));
        return false;
      }
      case KC_RESET: // Custom RESET code that sets RGBLights to RED
        if (!record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
          reset_keyboard();
        }
        return false;
        break;
    }
  return true;
}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {

#ifdef RGBLIGHT_ENABLE
  rgblight_enable();
  rgblight_sethsv_teal();
#endif // RGBLIGHT_ENABLE
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
  case _NAV:
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_green();
    rgblight_mode(1);
#endif // RGBLIGHT_ENABLE
    break;
  case _RAISE:
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_yellow();
    rgblight_mode(5);
#endif // RGBLIGHT_ENABLE
    break;
  case _LOWER:
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_orange();
    rgblight_mode(5);
#endif // RGBLIGHT_ENABLE
    break;
  default:
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_teal();
    rgblight_mode(1);
#endif // RGBLIGHT_ENABLE
    break;
  }
  return state;
}

