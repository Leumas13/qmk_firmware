#include "shared.h"

#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#endif

#ifndef KEYBOARD_UNLOCK_PASSWORD
#    define KEYBOARD_UNLOCK_PASSWORD "yo"
#endif

#ifndef KEYBOARD_UNLOCK_LOG_SIZE
#    define KEYBOARD_UNLOCK_LOG_SIZE 8
#endif

#ifndef KEYBOARD_LOCK_ON_BOOT
#    define KEYBOARD_LOCK_ON_BOOT true
#endif

#ifndef KEYBOARD_IDLE_LOCK_TIMEOUT
#    define KEYBOARD_IDLE_LOCK_TIMEOUT 300000
#endif

static bool     keyboard_locked     = KEYBOARD_LOCK_ON_BOOT;
static uint32_t last_activity_timer = 0;
static uint8_t  unlock_progress     = 0;

#ifdef SPLIT_KEYBOARD
static bool     kb_lock_sync_dirty = true;
static uint32_t kb_lock_sync_timer = 0;
#endif

static void mark_kb_lock_dirty(void) {
#ifdef SPLIT_KEYBOARD
    kb_lock_sync_dirty = true;
#endif
}

static uint16_t normalize_keycode(uint16_t keycode) {
    if (IS_QK_MOD_TAP(keycode)) {
        return QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }

    if (IS_QK_LAYER_TAP(keycode)) {
        return QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }

    return keycode;
}

static uint16_t char_to_keycode(char c) {
    if (c >= 'a' && c <= 'z') {
        return KC_A + (c - 'a');
    }

    if (c >= 'A' && c <= 'Z') {
        return KC_A + (c - 'A');
    }

    if (c >= '1' && c <= '9') {
        return KC_1 + (c - '1');
    }

    if (c == '0') {
        return KC_0;
    }

    return KC_NO;
}

static uint8_t get_password_keycodes(uint16_t *keycodes) {
    const char *password = KEYBOARD_UNLOCK_PASSWORD;
    uint8_t     length   = 0;

    while (*password && length < KEYBOARD_UNLOCK_LOG_SIZE) {
        uint16_t keycode = char_to_keycode(*password);
        if (keycode == KC_NO) {
            break;
        }

        keycodes[length++] = keycode;
        password++;
    }

    return length;
}

static bool unlock_sequence_matches(uint16_t keycode) {
    uint16_t password_keycodes[KEYBOARD_UNLOCK_LOG_SIZE] = {0};
    uint8_t  password_length = get_password_keycodes(password_keycodes);

    if (password_length == 0) {
        return false;
    }

    if (keycode == password_keycodes[unlock_progress]) {
        unlock_progress++;
    } else {
        unlock_progress = (keycode == password_keycodes[0]) ? 1 : 0;
    }

    if (unlock_progress < password_length) {
        return false;
    }

    unlock_progress = 0;
    return true;
}

void lock_keyboard(void) {
    if (keyboard_locked) {
        return;
    }

    keyboard_locked = true;
    unlock_progress = 0;
    clear_keyboard();
    layer_clear();
    mark_kb_lock_dirty();
}

void unlock_keyboard(void) {
    if (!keyboard_locked) {
        return;
    }

    keyboard_locked = false;
    unlock_progress = 0;
    last_activity_timer = timer_read32();
    layer_move(_BASE);
    mark_kb_lock_dirty();
}

bool is_keyboard_locked(void) {
    return keyboard_locked;
}

bool process_record_security(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return !keyboard_locked;
    }

    if (keycode == KB_LOCK) {
        lock_keyboard();
        return false;
    }

    if (!keyboard_locked) {
        last_activity_timer = timer_read32();
        return true;
    }

    if (unlock_sequence_matches(normalize_keycode(keycode))) {
        unlock_keyboard();
    }

    return false;
}

#ifdef SPLIT_KEYBOARD
static void kb_lock_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    (void)out_buflen;
    (void)out_data;

    if (in_buflen != sizeof(keyboard_locked)) {
        return;
    }

    keyboard_locked = *(const bool *)in_data;
    unlock_progress = 0;
    last_activity_timer = timer_read32();
}

void init_security_sync(void) {
    transaction_register_rpc(KB_LOCK_SYNC, kb_lock_sync_slave_handler);
    last_activity_timer = timer_read32();
    mark_kb_lock_dirty();
}

static void sync_kb_lock_task(void) {
    if (!is_keyboard_master() || timer_elapsed32(kb_lock_sync_timer) < 50) {
        return;
    }

    if (!kb_lock_sync_dirty && timer_elapsed32(kb_lock_sync_timer) < 1000) {
        return;
    }

    kb_lock_sync_timer = timer_read32();

    if (transaction_rpc_send(KB_LOCK_SYNC, sizeof(keyboard_locked), &keyboard_locked)) {
        kb_lock_sync_dirty = false;
    }
}
#else
void init_security_sync(void) {
    last_activity_timer = timer_read32();
}

static void sync_kb_lock_task(void) {}
#endif

void security_task(void) {
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master() && !keyboard_locked && timer_elapsed32(last_activity_timer) >= KEYBOARD_IDLE_LOCK_TIMEOUT) {
        lock_keyboard();
    }
#else
    if (!keyboard_locked && timer_elapsed32(last_activity_timer) >= KEYBOARD_IDLE_LOCK_TIMEOUT) {
        lock_keyboard();
    }
#endif

    sync_kb_lock_task();
}
