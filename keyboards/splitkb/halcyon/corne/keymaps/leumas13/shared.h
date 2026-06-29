#pragma once
#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _NUM,
    _SYM,
    _CFG,
    _NAV,
    _MOUSE,
    _FUN,
    _EXTRA
};

enum os_modes {
    OS_WIN = 0,
    OS_MAC,
    OS_LINUX
};

enum led_colors {
    _OFF = 0,
    _OS_C,
    _RED,
    _ORG,
    _YLW,
    _GRN,
    _BLU,
    _PRP,
    _CYN,
    _MAG,
    _WHT
};

enum custom_keycodes {
    OS_SWITCH = SAFE_RANGE,
    OS_WIN_MODE,
    OS_MAC_MODE,
    OS_LINUX_MODE,
    OS_UNDO,
    OS_REDO,
    OS_CUT,
    OS_COPY,
    OS_PASTE,
    OS_WORD_LEFT,
    OS_WORD_RIGHT,
    OS_HOME,
    OS_END,
    M_PAREN,
    M_BRACK,
    M_CURLY,
    EXT_SAFE_RANGE
};

void set_os_mode(uint8_t mode);
uint8_t get_os_mode(void);
bool process_record_os(uint16_t keycode, keyrecord_t *record);

void get_rgb_from_id(uint8_t color_id, uint8_t *r, uint8_t *g, uint8_t *b);
void update_rgb_underglow(void);
void update_rgb_indicators(void);
void apply_layer_color(uint8_t layer);

bool process_record_macros(uint16_t keycode, keyrecord_t *record);
