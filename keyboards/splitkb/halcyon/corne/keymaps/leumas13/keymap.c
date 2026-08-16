#include QMK_KEYBOARD_H
#include "shared.h"

#include "keydefs.c"
#include "security_handlers.c"
#include "os_handlers.c"
#include "macro_handlers.c"
#include "tap_dance.c"
#include "combos.c"
#include "key_overrides.c"
#include "rgb_underglow.c"
#include "rgb_handlers.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPC,
        LCTL_T(KC_ESC), LGUI_T(KC_A),   LALT_T(KC_S),   LCTL_T(KC_D),   LSFT_T(KC_F),   KC_G,           KC_H,           RSFT_T(KC_J),   RCTL_T(KC_K),   LALT_T(KC_L),   RGUI_T(KC_SCLN), KC_QUOT,
        KC_RALT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,         KC_RALT,
                                                        MO(_NAV),       MO(_NUM),       KC_SPC,         KC_ENT,         MO(_SYM),       MO(_FUN)
    ),

    [_GAME] = LAYOUT_split_3x6_3(
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPC,
        KC_LSFT,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
        KC_LCTL,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,         KC_LCTL,
                                                        KC_LALT,        KC_SPC,         MO(_GNUM),      KC_ENT,         MO(_SYM),       MO(_FUN)
    ),

    [_GNUM] = LAYOUT_split_3x6_3(
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,           KC_1,           KC_4,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,           KC_2,           KC_5,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,           KC_3,           KC_6,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                        KC_LALT,        KC_SPC,         MO(_GNUM),      KC_ENT,         MO(_SYM),       MO(_FUN)
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        MIN_MV,        XXXX,          KC_F5,          KC_F6,          KC_F8,           KC_PSCR,        XXXX,           KC_7,           KC_8,           KC_9,           KC_DEL,         KC_BSPC,
        ____,           ____,           ____,           ____,           ____,           ____,           KC_PPLS,        KC_4,           KC_5,           KC_6,           XXXX,           XXXX,
        ____,           XXXX,           ____,           ____,           ____,           ____,           KC_PMNS,        KC_1,           KC_2,           KC_3,           KC_PSLS,        XXXX,
                                                        ____,           ____,           ____,           ____,           KC_0,           KC_RALT
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        ____,           XXXX,           XXXX,           XXXX,           XXXX,           S(KC_6),        S(KC_7),        S(KC_8),        S(KC_9),        S(KC_0),        XXXX,           KC_BSPC,
        MO(_CFG),       S(KC_1),        S(KC_2),        S(KC_3),        S(KC_4),        S(KC_5),        KC_MINS,        KC_EQL,         KC_LBRC,        KC_RBRC,        S(KC_BSLS),     KC_GRV,
        ____,           XXXX,           XXXX,           XXXX,           XXXX,           XXXX,           S(KC_MINS),     S(KC_EQL),      S(KC_LBRC),     S(KC_RBRC),     KC_BSLS,        S(KC_GRV),
                                                        KC_LGUI,        KC_LALT,        KC_SPC,         KC_ENT,         ____,           KC_RALT
    ),

    [_CFG] = LAYOUT_split_3x6_3(
        TG(_GAME),       OS_WIN_MODE,    OS_MAC_MODE,  OS_LINUX_MODE,      KB_LOCK,           XXXX,         XXXX,           KC_MPLY,        KC_MPRV,        KC_MNXT,        XXXX,           XXXX,
        XXXX,           RM_TOGG,           XXXX,     UGL_BRI_UP,   RGB_BRI_UP,           XXXX,              XXXX,           KC_MUTE,        KC_VOLD,        KC_VOLU,        XXXX,           XXXX,
        XXXX,           XXXX,              XXXX,     UGL_BRI_DN,   RGB_BRI_DN,           XXXX,              XXXX,           XXXX,           KC_BRID,        KC_BRIU,        XXXX,           XXXX,
                                                        XXXX,            XXXX,           XXXX,           QK_BOOT,        XXXX,           XXXX
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        MO(_MOUSE),     OS_UNDO,        OS_CUT,         OS_COPY,        OS_PASTE,       OS_REDO,        KC_PGUP,        OS_HOME,        KC_UP,          OS_END,         KC_DEL,         KC_BSPC,
        ____,           ____,           ____,           ____,           ____,           KC_CALC,        KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RGHT,        XXXX,           KC_PSCR,
        ____,           XXXX,           XXXX,           XXXX,           XXXX,           KC_MYCM,        XXXX,           OS_WORD_LEFT,   XXXX,           OS_WORD_RIGHT,  CW_TOGG,           KC_CAPS,
                                                        ____,           ____,           ____,           ____,           ____,           KC_LALT
    ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        ____,           ____,           ____,           ____,           ____,           ____,           MS_WHLU,        MS_WHLL,        MS_UP,          MS_WHLR,        ____,           ____,
        ____,           ____,           ____,           ____,           ____,           ____,           MS_WHLD,        MS_LEFT,        MS_DOWN,        MS_RGHT,        ____,           ____,
        ____,           ____,           ____,           ____,           ____,           ____,           XXXX,           XXXX,           XXXX,           XXXX,           ____,           ____,
                                                        ____,           ____,           ____,           MS_BTN1,        MS_BTN2,        ____
    ),

    [_FUN] = LAYOUT_split_3x6_3(
        ____,           ____,           KC_F7,          KC_F8,          KC_F9,          KC_F12,         XXXX,           ____,           M_PAREN,        ____,           M_VM,         M_HOST,
        ____,           ____,           KC_F4,          KC_F5,          KC_F6,          KC_F11,         ____,           ____,           M_BRACK,        ____,           XXXX,           XXXX,
        ____,           ____,           KC_F1,          KC_F2,          KC_F3,          KC_F10,         ____,           ____,           M_CURLY,        ____,           XXXX,           XXXX,
                                                        ____,           ____,           ____,           ____,           ____,           ____
    ),

    [_EXTRA] = LAYOUT_split_3x6_3(
        ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,
        ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,
        ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,           ____,
                                                        ____,           ____,           ____,           ____,           ____,           ____
    )
};

#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x6_3(
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
                        'L', 'L', 'L', 'R', 'R', 'R'
);
#endif

void keyboard_post_init_user(void) {
    init_security_sync();
    init_os_sync();
    init_rgb_sync();
    set_os_mode(OS_WIN);
}

void housekeeping_task_user(void) {
    security_task();
    sync_os_mode_task();
    sync_rgb_state_task();
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
            return TAPPING_TERM + 40;

        case LGUI_T(KC_A):
        case LALT_T(KC_S):
        case LCTL_T(KC_D):
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
        case RCTL_T(KC_K):
        case RALT_T(KC_L):
        case RGUI_T(KC_SCLN):
            return TAPPING_TERM + 25;

        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_security(keycode, record)) {
        return false;
    }

    if (!process_record_os(keycode, record)) {
        return false;
    }

    if (!process_record_macros(keycode, record)) {
        return false;
    }

#ifdef RGB_MATRIX_ENABLE
    if (!process_record_rgb(keycode, record)) {
        return false;
    }
#endif

    return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    update_rgb_indicators();
    return true;
}
#endif
