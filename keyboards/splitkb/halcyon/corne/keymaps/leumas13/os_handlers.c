#include "shared.h"

#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#endif

static uint8_t current_os_mode = OS_WIN;

#ifdef SPLIT_KEYBOARD
static bool     os_mode_sync_dirty = true;
static uint32_t os_mode_sync_timer = 0;
#endif

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

static void apply_os_mode(uint8_t mode) {
    if (mode <= OS_LINUX) {
        current_os_mode = mode;
        apply_os_mod_mapping();
    }
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
        apply_os_mode(mode);

#ifdef SPLIT_KEYBOARD
        os_mode_sync_dirty = true;
#endif
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
                layer_off(_GAME);
                return false;
            case OS_MAC_MODE:
                set_os_mode(OS_MAC);
                layer_off(_GAME);
                return false;
            case OS_LINUX_MODE:
                set_os_mode(OS_LINUX);
                layer_off(_GAME);
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

#ifdef SPLIT_KEYBOARD
static void os_mode_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    (void)out_buflen;
    (void)out_data;

    if (in_buflen != sizeof(current_os_mode)) {
        return;
    }

    apply_os_mode(*(const uint8_t *)in_data);
}

void init_os_sync(void) {
    transaction_register_rpc(OS_MODE_SYNC, os_mode_sync_slave_handler);
    os_mode_sync_dirty = true;
}

void sync_os_mode_task(void) {
    if (!is_keyboard_master() || timer_elapsed32(os_mode_sync_timer) < 50) {
        return;
    }

    if (!os_mode_sync_dirty && timer_elapsed32(os_mode_sync_timer) < 1000) {
        return;
    }

    os_mode_sync_timer = timer_read32();

    if (transaction_rpc_send(OS_MODE_SYNC, sizeof(current_os_mode), &current_os_mode)) {
        os_mode_sync_dirty = false;
    }
}
#else
void init_os_sync(void) {}
void sync_os_mode_task(void) {}
#endif
