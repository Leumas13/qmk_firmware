#include "shared.h"

void update_rgb_underglow_color(uint8_t color_id) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    get_rgb_from_id(color_id, &r, &g, &b);
    apply_user_underglow_brightness(&r, &g, &b);

    for (uint8_t led = 0; led < RGB_MATRIX_LED_COUNT; ++led) {
        if (g_led_config.flags[led] & LED_FLAG_UNDERGLOW) {
            rgb_matrix_set_color(led, r, g, b);
        }
    }
}

void update_rgb_underglow(void) {
    update_rgb_underglow_color(_OS_C);
}
