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
#include "eeconfig.h"

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
  KC_RESET,
  CC_ARRW,
  CC_PRN,
  CC_BRC,
  CC_CBR,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define NAV__TAP LT(_NAV, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, \
    KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            RAISE,     LOWER,      LOWER,   RAISE,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_GRV, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_SPC, KC_LSFT, KC_LCTL,      KC_RALT, KC_RGUI, NAV__TAP, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT \
  ),

  [_LOWER] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                                  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
    KC_INS,  _______, _______, CC_PRN,  CC_BRC,  CC_CBR,           _______, _______,          _______, _______,          KC_HOME, KC_PGDN,  KC_PGUP, KC_END,  _______, _______, \
    KC_RESET,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU \
  ),

  [_RAISE] = LAYOUT( \
    KC_ESC, KC_AMPR, KC_ASTR, KC_UNDS, KC_LPRN, KC_RPRN,                                                                KC_7,    KC_8,    KC_9,    KC_EQL,  _______, _______, \
    _______, KC_DLR,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,          _______, _______,          _______, _______,          KC_4,    KC_5,    KC_6,    KC_MINS, KC_PLUS, _______, \
    CC_ARRW, KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR, _______, _______, _______,          _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_BSLS, KC_PIPE \
  ),

  [_NAV] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______,                                                                _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, _______, _______, _______,          _______, _______,          _______, _______,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  )


};

void matrix_init_user(void) {
    dprintf("Initializing in matrix_scan_user");
#ifdef RGBLIGHT_ENABLE
    // uint8_t default_layer = eeconfig_read_default_layer();

    rgblight_enable();

    rgblight_sethsv (180,  255, 128);
#endif
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  //uint8_t default_layer = eeconfig_read_default_layer();
  switch (biton32(state)) {
    case _RAISE:
      rgblight_sethsv (60,  255, 255);
      rgblight_mode(5);
      break;
    case _LOWER:
      rgblight_sethsv (39,  255, 255);
      rgblight_mode(5);
      break;
    case _NAV:
      rgblight_sethsv_green();
      rgblight_mode(5);
      break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv (180,  255, 128);
        rgblight_mode(1);
        break;
  }
#endif
  return state;
}





bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _NAV);
    } else {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _NAV);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _NAV);
    } else {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _NAV);
    }
    return false;
    break;
  case KC_RESET: // Custom RESET code that setr RGBLights to RED
    if (!record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
      rgblight_enable();
      rgblight_mode(1);
      rgblight_setrgb(0xff, 0x00, 0x00);
#endif
      reset_keyboard();
    }
    return false;
    break;
    case CC_ARRW:
    if (record->event.pressed) {
        SEND_STRING("->");
      }
        return false;
      case CC_PRN:
       if (record->event.pressed) {
        SEND_STRING("()"SS_TAP(X_LEFT));
        }
        return false;
      case CC_BRC:
        if (record->event.pressed) {
          SEND_STRING("[]"SS_TAP(X_LEFT));
        }
        return false;
      case CC_CBR:
        if (record->event.pressed) {
          SEND_STRING("{}"SS_TAP(X_LEFT));
        }
        return false;
      }
  return true;
}