#include "shared.h"

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
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        _PRP,  _OFF,  _OFF,  _OFF,  _OFF,  _PRP,      _OFF,  _PRP,  _PRP,  _PRP,  _PRP,  _PRP,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _PRP,  _PRP,  _PRP,  _PRP,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _PRP,  _PRP,  _PRP,  _PRP,  _PRP,  _OFF,
                              _OFF,  _OFF,  _OFF,      _OFF,  _PRP,  _WHT
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        _BLU,  _OFF,  _OFF,  _OFF,  _OFF,  _BLU,      _BLU,  _BLU,  _BLU,  _BLU,  _OFF,  _BLU,
        _ORG,  _BLU,  _BLU,  _BLU,  _BLU,  _BLU,      _BLU,  _BLU,  _BLU,  _BLU,  _BLU,  _BLU,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _BLU,  _BLU,  _BLU,  _BLU,  _BLU,  _WHT,
                              _WHT,  _WHT,  _OFF,      _OFF,  _OFF,  _WHT
    ),

    [_CFG] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _GRN,  _GRN,  _GRN,  _OFF,  _OFF,
        _OFF,  _WHT,  _WHT,  _WHT,  _WHT,  _OFF,      _OFF,  _GRN,  _GRN,  _GRN,  _OFF,  _OFF,
        _OFF,  _WHT,  _WHT,  _WHT,  _WHT,  _OFF,      _OFF,  _OFF,  _YLW,  _YLW,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _RED,  _OFF,  _OFF
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        _YLW,  _GRN,  _GRN,  _GRN,  _GRN,  _GRN,      _YLW,  _YLW,  _CYN,  _YLW,  _RED,  _RED,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _YLW,      _YLW,  _CYN,  _CYN,  _CYN,  _OFF,  _YLW,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _YLW,      _OFF,  _CYN,  _OFF,  _CYN,  _OFF,  _YLW,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _WHT
    ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _YLW,  _YLW,  _YLW,  _YLW,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _YLW,  _YLW,  _YLW,  _YLW,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _YLW,  _YLW,  _OFF
    ),

    [_FUN] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _RED,  _RED,  _RED,  _RED,      _OFF,  _OFF,  _MAG,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _RED,  _RED,  _RED,  _RED,      _OFF,  _OFF,  _MAG,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _RED,  _RED,  _RED,  _RED,      _OFF,  _OFF,  _MAG,  _OFF,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF
    ),

    [_EXTRA] = LAYOUT_split_3x6_3(
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
        _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF,  _OFF,  _OFF,  _OFF,
                              _OFF,  _OFF,  _OFF,      _OFF,  _OFF,  _OFF
    )
};

void update_rgb_indicators(void) {
    uint8_t layer = get_highest_layer(layer_state);

    update_rgb_underglow();

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t led = g_led_config.matrix_co[row][col];

            if (led == NO_LED) {
                continue;
            }

            uint8_t color_id = _OFF;
            if (layer < ARRAY_SIZE(layer_pattern_leds)) {
                color_id = pgm_read_byte(&layer_pattern_leds[layer][row][col]);
            }

            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;
            get_rgb_from_id(color_id, &r, &g, &b);
            rgb_matrix_set_color(led, r, g, b);
        }
    }
}

void apply_layer_color(uint8_t layer) {
    (void)layer;
}
