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
    _WIN,
    _MAC,
    _LIN,
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
    RGB_BRI_DN,
    RGB_BRI_UP,
    UGL_BRI_DN,
    UGL_BRI_UP,
    M_PAREN,
    M_BRACK,
    M_CURLY,
    M_VM,
    M_HOST,
    KB_LOCK,
    EXT_SAFE_RANGE,
    MIN_MV
};

void lock_keyboard(void);
void unlock_keyboard(void);
bool is_keyboard_locked(void);
bool process_record_security(uint16_t keycode, keyrecord_t *record);
void init_security_sync(void);
void security_task(void);

void set_os_mode(uint8_t mode);
uint8_t get_os_mode(void);
bool process_record_os(uint16_t keycode, keyrecord_t *record);
void init_os_sync(void);
void sync_os_mode_task(void);

void get_rgb_from_id(uint8_t color_id, uint8_t *r, uint8_t *g, uint8_t *b);
bool process_record_rgb(uint16_t keycode, keyrecord_t *record);
void init_rgb_sync(void);
void sync_rgb_state_task(void);
void apply_user_underglow_brightness(uint8_t *r, uint8_t *g, uint8_t *b);
void update_rgb_underglow_color(uint8_t color_id);
void update_rgb_underglow(void);
void update_rgb_indicators(void);
void apply_layer_color(uint8_t layer);

bool process_record_macros(uint16_t keycode, keyrecord_t *record);
