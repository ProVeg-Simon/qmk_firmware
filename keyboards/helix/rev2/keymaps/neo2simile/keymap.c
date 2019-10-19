#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _LAYER1 = 0,
    _LAYER2LEFTSHIFT,
    _LAYER2RIGHTSHIFT,
    _LAYER3,
    _LAYER4,
    _LAYER5,
    _LAYER6
};

/*
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};
*/

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_TAB, KC_X, KC_V, KC_L, KC_C, KC_W, KC_K, KC_H, KC_G, KC_F, KC_Q, MO(3), MO(3), KC_U, KC_I, KC_A, KC_E, KC_O, KC_S, KC_N, KC_R, KC_T, KC_D, KC_Y, MO(1), UC(0xFC), UC(0xF6), UC(0xE4), KC_P, KC_Z, KC_NO, KC_NO, KC_B, KC_M, KC_COMM, KC_DOT, KC_J, MO(2), KC_LCTL, KC_LALT, MO(4), KC_LEFT, KC_RGHT, KC_BSPC, KC_DEL, KC_ENT, KC_SPC, KC_UP, KC_DOWN, UC(0xDF), KC_RGUI, KC_RALT),
        [1] = LAYOUT(DF(0), UC(0xB0), UC(0xA7), UC(0x2113), UC(0xBB), UC(0xAB), KC_DLR, UC(0x20AC), UC(0x201E), UC(0x201C), UC(0x201D), KC_NO, LSFT(KC_TAB), LSFT(KC_X), LSFT(KC_V), LSFT(KC_L), LSFT(KC_C), LSFT(KC_W), LSFT(KC_K), LSFT(KC_H), LSFT(KC_G), LSFT(KC_F), LSFT(KC_Q), MO(5), MO(5), LSFT(KC_U), LSFT(KC_I), LSFT(KC_A), LSFT(KC_E), LSFT(KC_O), LSFT(KC_S), LSFT(KC_N), LSFT(KC_R), LSFT(KC_T), LSFT(KC_D), LSFT(KC_Y), KC_NO, UC(0xDC), UC(0xD6), UC(0xE4), LSFT(KC_P), LSFT(KC_Z), KC_NO, KC_NO, LSFT(KC_B), LSFT(KC_M), UC(0x2013), UC(0x2022), LSFT(KC_J), KC_CAPS, LSFT(KC_LCTL), LSFT(KC_LALT), KC_NO, LSFT(KC_LEFT), LSFT(KC_RGHT), LSFT(KC_BSPC), LSFT(KC_DEL), LSFT(KC_ENT), LSFT(KC_SPC), LSFT(KC_UP), LSFT(KC_DOWN), UC(0x1E9E), LSFT(KC_RGUI), LSFT(KC_RALT)),
        [2] = LAYOUT(DF(0), UC(0xB0), UC(0xA7), UC(0x2113), UC(0xBB), UC(0xAB), RSFT(KC_4), UC(0x20AC), UC(0x201E), UC(0x201C), UC(0x201D), KC_NO, RSFT(KC_TAB), RSFT(KC_X), RSFT(KC_V), RSFT(KC_L), RSFT(KC_C), RSFT(KC_W), RSFT(KC_K), RSFT(KC_H), RSFT(KC_G), RSFT(KC_F), RSFT(KC_Q), MO(5), MO(5), RSFT(KC_U), RSFT(KC_I), RSFT(KC_A), RSFT(KC_E), RSFT(KC_O), RSFT(KC_S), RSFT(KC_N), RSFT(KC_R), RSFT(KC_T), RSFT(KC_D), RSFT(KC_Y), KC_CAPS, UC(0xDC), UC(0xD6), UC(0xE4), RSFT(KC_P), RSFT(KC_Z), KC_NO, KC_NO, RSFT(KC_B), RSFT(KC_M), UC(0x2013), UC(0x2022), RSFT(KC_J), KC_NO, RSFT(KC_LCTL), RSFT(KC_LALT), KC_NO, RSFT(KC_LEFT), RSFT(KC_RGHT), RSFT(KC_BSPC), RSFT(KC_DEL), RSFT(KC_ENT), RSFT(KC_SPC), RSFT(KC_UP), RSFT(KC_DOWN), UC(0x1E9E), RSFT(KC_RGUI), RSFT(KC_RALT)),
        [3] = LAYOUT(KC_ESC, UC(0xB9), UC(0xB2), UC(0xB3), UC(0x203A), UC(0x2039), UC(0xA2), UC(0xA5), UC(0x201A), UC(0x2018), UC(0x2019), KC_NO, KC_TAB, KC_DOT, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_EXLM, KC_LT, KC_GT, KC_EQL, KC_AMPR, KC_NO, KC_NO, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT, MO(5), KC_HASH, KC_DLR, KC_PIPE, KC_TILD, KC_GRV, KC_NO, KC_NO, KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, MO(5), KC_LCTL, KC_LALT, MO(6), KC_NO, KC_NO, KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_NO, KC_NO, UC(0x17F), KC_RGUI, KC_RALT),
        [4] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PPLS, MO(6), MO(6), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PCMM, KC_PDOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PGUP, KC_NO, KC_LCTL, KC_LALT, KC_NO, KC_LEFT, KC_RGHT, KC_BSPC, KC_DEL, KC_NO, KC_P0, KC_UP, KC_DOWN, KC_NO, KC_RGUI, KC_RALT),
        [5] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UC_LNX, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UC_OSX, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UC_WINC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

