#include "shared.h"

#ifndef VM_TEXT
#    define VM_TEXT ""
#endif

#ifndef HOST_TEXT
#    define HOST_TEXT ""
#endif

bool process_record_macros(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case M_PAREN:
                SEND_STRING("()" SS_TAP(X_LEFT));
                return false;
            case M_BRACK:
                SEND_STRING("[]" SS_TAP(X_LEFT));
                return false;
            case M_CURLY:
                SEND_STRING("{}" SS_TAP(X_LEFT));
                return false;
            case M_VM:
                send_string(VM_TEXT);
                return false;
            case M_HOST:
                send_string(HOST_TEXT);
                return false;
            case MIN_MV:
                tap_code16(C(A(KC_PAUS)));
                return false;
        }
    }

    return true;
}
