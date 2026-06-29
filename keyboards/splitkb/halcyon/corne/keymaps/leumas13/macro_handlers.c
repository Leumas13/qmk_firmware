#include "shared.h"

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
        }
    }

    return true;
}
