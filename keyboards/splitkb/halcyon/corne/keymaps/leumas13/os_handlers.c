#include "shared.h"

static uint8_t current_os_mode = OS_WIN;

typedef struct {
    uint16_t win;
    uint16_t mac;
    uint16_t linux;
} os_keycode_map_t;

static const os_keycode_map_t os_keycode_maps[] = {
    [OS_UNDO - OS_UNDO]       = {C(KC_Z),    G(KC_Z),    C(KC_Z)},
    [OS_REDO - OS_UNDO]       = {C(KC_Y),    G(S(KC_Z)), C(KC_Y)},
    [OS_CUT - OS_UNDO]        = {C(KC_X),    G(KC_X),    C(KC_X)},
    [OS_COPY - OS_UNDO]       = {C(KC_C),    G(KC_C),    C(KC_C)},
    [OS_PASTE - OS_UNDO]      = {C(KC_V),    G(KC_V),    C(KC_V)},
    [OS_WORD_LEFT - OS_UNDO]  = {C(KC_LEFT), A(KC_LEFT), C(KC_LEFT)},
    [OS_WORD_RIGHT - OS_UNDO] = {C(KC_RGHT), A(KC_RGHT), C(KC_RGHT)},
    [OS_HOME - OS_UNDO]       = {KC_HOME,    G(KC_LEFT), KC_HOME},
    [OS_END - OS_UNDO]        = {KC_END,     G(KC_RGHT), KC_END},
};

static void apply_os_mod_mapping(void) {
    bool mac_mode = current_os_mode == OS_MAC;

    keymap_config.swap_lctl_lgui = mac_mode;
    keymap_config.swap_rctl_rgui = mac_mode;
}

static uint16_t get_os_keycode(uint16_t keycode) {
    if (keycode < OS_UNDO || keycode > OS_END) {
        return KC_NO;
    }

    os_keycode_map_t map = os_keycode_maps[keycode - OS_UNDO];

    switch (current_os_mode) {
        case OS_MAC:
            return map.mac;
        case OS_LINUX:
            return map.linux;
        case OS_WIN:
        default:
            return map.win;
    }
}

void set_os_mode(uint8_t mode) {
    if (mode <= OS_LINUX) {
        current_os_mode = mode;
        apply_os_mod_mapping();
    }
}

uint8_t get_os_mode(void) {
    return current_os_mode;
}

bool process_record_os(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case OS_SWITCH:
                set_os_mode((current_os_mode + 1) % 3);
                return false;
            case OS_WIN_MODE:
                set_os_mode(OS_WIN);
                return false;
            case OS_MAC_MODE:
                set_os_mode(OS_MAC);
                return false;
            case OS_LINUX_MODE:
                set_os_mode(OS_LINUX);
                return false;
        }

        uint16_t os_keycode = get_os_keycode(keycode);
        if (os_keycode != KC_NO) {
            tap_code16(os_keycode);
            return false;
        }
    }

    return true;
}
