#include "shared.h"

#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#endif

#ifndef USER_RGB_BRIGHTNESS_STEP
#    define USER_RGB_BRIGHTNESS_STEP 15
#endif

#ifndef USER_RGB_MATRIX_DEFAULT_BRIGHTNESS
#    define USER_RGB_MATRIX_DEFAULT_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#ifndef USER_RGB_UNDERGLOW_DEFAULT_BRIGHTNESS
#    define USER_RGB_UNDERGLOW_DEFAULT_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

typedef struct {
    uint8_t matrix;
    uint8_t underglow;
} user_rgb_state_t;

static user_rgb_state_t user_rgb_state = {
    .matrix    = USER_RGB_MATRIX_DEFAULT_BRIGHTNESS,
    .underglow = USER_RGB_UNDERGLOW_DEFAULT_BRIGHTNESS,
};

#ifdef SPLIT_KEYBOARD
static bool     rgb_state_sync_dirty = true;
static uint32_t rgb_state_sync_timer = 0;
#endif

static uint8_t adjust_brightness(uint8_t brightness, bool increase) {
    if (increase) {
        return (brightness < RGB_MATRIX_MAXIMUM_BRIGHTNESS - USER_RGB_BRIGHTNESS_STEP) ? brightness + USER_RGB_BRIGHTNESS_STEP : RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    }

    return (brightness > USER_RGB_BRIGHTNESS_STEP) ? brightness - USER_RGB_BRIGHTNESS_STEP : 0;
}

static void mark_rgb_state_dirty(void) {
#ifdef SPLIT_KEYBOARD
    rgb_state_sync_dirty = true;
#endif
}

static void apply_user_brightness(uint8_t brightness, uint8_t *r, uint8_t *g, uint8_t *b) {
    if (brightness > RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
        brightness = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    }

    *r = ((uint16_t)*r * brightness) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    *g = ((uint16_t)*g * brightness) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    *b = ((uint16_t)*b * brightness) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
}

static void apply_user_matrix_brightness(uint8_t *r, uint8_t *g, uint8_t *b) {
    apply_user_brightness(user_rgb_state.matrix, r, g, b);
}

void apply_user_underglow_brightness(uint8_t *r, uint8_t *g, uint8_t *b) {
    apply_user_brightness(user_rgb_state.underglow, r, g, b);
}

bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case RGB_BRI_DN:
            user_rgb_state.matrix = adjust_brightness(user_rgb_state.matrix, false);
            mark_rgb_state_dirty();
            return false;
        case RGB_BRI_UP:
            user_rgb_state.matrix = adjust_brightness(user_rgb_state.matrix, true);
            mark_rgb_state_dirty();
            return false;
        case UGL_BRI_DN:
            user_rgb_state.underglow = adjust_brightness(user_rgb_state.underglow, false);
            mark_rgb_state_dirty();
            return false;
        case UGL_BRI_UP:
            user_rgb_state.underglow = adjust_brightness(user_rgb_state.underglow, true);
            mark_rgb_state_dirty();
            return false;
    }

    return true;
}

void get_rgb_from_id(uint8_t color_id, uint8_t *r, uint8_t *g, uint8_t *b) {
    switch (color_id) {
        case _OS_C:
            switch (get_os_mode()) {
                case OS_WIN:
                    *r = 0; *g = 180; *b = 80;
                    return;
                case OS_MAC:
                    *r = 60; *g = 120; *b = 255;
                    return;
                case OS_LINUX:
                    *r = 255; *g = 255; *b = 255;
                    return;
            }
            break;
        case _WIN: *r = 0;   *g = 180; *b = 80;  return;
        case _MAC: *r = 60;  *g = 120; *b = 255; return;
        case _LIN: *r = 255; *g = 255; *b = 255; return;
        case _RED: *r = 255; *g = 40;  *b = 30;  return;
        case _ORG: *r = 255; *g = 110; *b = 0;   return;
        case _YLW: *r = 255; *g = 210; *b = 0;   return;
        case _GRN: *r = 0;   *g = 200; *b = 80;  return;
        case _BLU: *r = 30;  *g = 100; *b = 255; return;
        case _PRP: *r = 140; *g = 40;  *b = 255; return;
        case _CYN: *r = 0;   *g = 210; *b = 255; return;
        case _MAG: *r = 255; *g = 0;   *b = 180; return;
        case _WHT: *r = 255; *g = 255; *b = 255; return;
    }

    *r = 0;
    *g = 0;
    *b = 0;
}

const uint8_t PROGMEM layer_pattern_leds[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        _BLU,  _BLU,  _RED,  _RED,  _ORG,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
        _BLU,  _RED,  _RED,  _ORG,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
        _RED,  _RED,  _ORG,  _YLW,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
                             _YLW,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW
    ),

    [_GAME] = LAYOUT_split_3x6_3(
        _BLU,  _BLU,  _RED,  _RED,  _ORG,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
        _BLU,  _RED,  _RED,  _ORG,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
        _RED,  _RED,  _ORG,  _YLW,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
                             _YLW,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW
    ),

    [_GNUM] = LAYOUT_split_3x6_3(
        _BLU,  _BLU,  _RED,  _RED,  _ORG,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
        _BLU,  _RED,  _RED,  _ORG,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
        _RED,  _RED,  _ORG,  _YLW,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW,  _YLW,  _YLW,  _YLW,
                             _YLW,  _YLW,  _YLW,      _YLW,  _YLW,  _YLW
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        _PRP,  _OFF,  _RED,  _RED,  _RED,  _PRP,      _OFF,  _PRP,  _PRP,  _PRP,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _PRP,  _PRP,  _PRP,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _PRP,  _PRP,  _PRP,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _OFF,  _PRP,  _WHT
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _BLU,      _BLU,  _BLU,  _BLU,  _BLU,  _OFF,  _BLU,
        _ORG,  _BLU,  _BLU,  _BLU,  _BLU,  _BLU,      _BLU,  _BLU,  _BLU,  _BLU,  _BLU,  _BLU,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _BLU,  _BLU,  _BLU,  _BLU,  _BLU,  _WHT,
                              _WHT,  _WHT,  _OFF,      _OFF,  _OFF,  _WHT
    ),

    [_CFG] = LAYOUT_split_3x6_3(
        _YLW,  _WIN,  _MAC,  _LIN,  _OFF,  _OFF,      _OFF,  _GRN,  _GRN,  _GRN,  _OFF,  _OFF,
        _OFF,  _WHT,  _OFF,  _WHT,  _WHT,  _OFF,      _OFF,  _GRN,  _GRN,  _GRN,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _WHT,  _WHT,  _OFF,      _OFF,  _OFF,  _YLW,  _YLW,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _RED,  _OFF,  _OFF
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        _YLW,  _GRN,  _GRN,  _GRN,  _GRN,  _GRN,      _YLW,  _YLW,  _CYN,  _YLW,  _RED,  _RED,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _YLW,      _YLW,  _CYN,  _CYN,  _CYN,  _OFF,  _PRP,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _YLW,      _OFF,  _CYN,  _OFF,  _CYN,  _WHT,  _GRN,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _WHT
    ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _CYN,  _GRN,  _YLW,  _GRN,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _CYN,  _YLW,  _YLW,  _YLW,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _YLW,  _YLW,  _OFF
    ),

    [_FUN] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _RED,  _RED,  _RED,  _RED,      _OFF,  _OFF,  _MAG,  _OFF,  _GRN,  _OFF,
        _OFF,  _OFF,  _RED,  _RED,  _RED,  _RED,      _OFF,  _OFF,  _MAG,  _OFF,  _YLW,  _YLW,
        _OFF,  _OFF,  _RED,  _RED,  _RED,  _RED,      _OFF,  _OFF,  _MAG,  _OFF,  _YLW,  _YLW,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF
    ),

    [_EXTRA] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF
    )
};

static uint8_t get_layer_color_id(uint8_t layer, uint8_t row, uint8_t col) {
    if (layer >= ARRAY_SIZE(layer_pattern_leds)) {
        return _OFF;
    }

    if (row == 3 && col <= 2) {
        col = 5 - col;
    } else if (row == 7 && col <= 2) {
        col = 5 - col;
    }

    return pgm_read_byte(&layer_pattern_leds[layer][row][col]);
}

static void clear_rgb_matrix_keys(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t led = g_led_config.matrix_co[row][col];

            if (led == NO_LED) {
                continue;
            }

            rgb_matrix_set_color(led, 0, 0, 0);
        }
    }
}

void update_rgb_indicators(void) {
    uint8_t layer = get_highest_layer(layer_state);

    if (is_keyboard_locked()) {
        update_rgb_underglow_color(_RED);
        clear_rgb_matrix_keys();
        return;
    }

    if (layer == _GAME || layer == _GNUM) {
        update_rgb_underglow_color(_YLW);
    } else {
        update_rgb_underglow();
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t led = g_led_config.matrix_co[row][col];

            if (led == NO_LED) {
                continue;
            }

            uint8_t color_id = get_layer_color_id(layer, row, col);
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;

            get_rgb_from_id(color_id, &r, &g, &b);
            apply_user_matrix_brightness(&r, &g, &b);
            rgb_matrix_set_color(led, r, g, b);
        }
    }
}

void apply_layer_color(uint8_t layer) {
    (void)layer;
}

#ifdef SPLIT_KEYBOARD
static void rgb_state_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    (void)out_buflen;
    (void)out_data;

    if (in_buflen != sizeof(user_rgb_state)) {
        return;
    }

    user_rgb_state = *(const user_rgb_state_t *)in_data;
}

void init_rgb_sync(void) {
    transaction_register_rpc(RGB_STATE_SYNC, rgb_state_sync_slave_handler);
    rgb_state_sync_dirty = true;
}

void sync_rgb_state_task(void) {
    if (!is_keyboard_master() || timer_elapsed32(rgb_state_sync_timer) < 50) {
        return;
    }

    if (!rgb_state_sync_dirty && timer_elapsed32(rgb_state_sync_timer) < 1000) {
        return;
    }

    rgb_state_sync_timer = timer_read32();

    if (transaction_rpc_send(RGB_STATE_SYNC, sizeof(user_rgb_state), &user_rgb_state)) {
        rgb_state_sync_dirty = false;
    }
}
#else
void init_rgb_sync(void) {}
void sync_rgb_state_task(void) {}
#endif
