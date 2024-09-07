#include "SDL3/SDL_scancode.h"

#include "toolkit/toolkit.h"
#include "toolkit/time.h"

/* HINT: There's stuff waaaaaay down there. ↓ */

#define X_ALL_SDL_KEYCODES \
    X(SDL_SCANCODE_UNKNOWN) \
    X(SDL_SCANCODE_A) \
    X(SDL_SCANCODE_B) \
    X(SDL_SCANCODE_C) \
    X(SDL_SCANCODE_D) \
    X(SDL_SCANCODE_E) \
    X(SDL_SCANCODE_F) \
    X(SDL_SCANCODE_G) \
    X(SDL_SCANCODE_H) \
    X(SDL_SCANCODE_I) \
    X(SDL_SCANCODE_J) \
    X(SDL_SCANCODE_K) \
    X(SDL_SCANCODE_L) \
    X(SDL_SCANCODE_M) \
    X(SDL_SCANCODE_N) \
    X(SDL_SCANCODE_O) \
    X(SDL_SCANCODE_P) \
    X(SDL_SCANCODE_Q) \
    X(SDL_SCANCODE_R) \
    X(SDL_SCANCODE_S) \
    X(SDL_SCANCODE_T) \
    X(SDL_SCANCODE_U) \
    X(SDL_SCANCODE_V) \
    X(SDL_SCANCODE_W) \
    X(SDL_SCANCODE_X) \
    X(SDL_SCANCODE_Y) \
    X(SDL_SCANCODE_Z) \
    X(SDL_SCANCODE_1) \
    X(SDL_SCANCODE_2) \
    X(SDL_SCANCODE_3) \
    X(SDL_SCANCODE_4) \
    X(SDL_SCANCODE_5) \
    X(SDL_SCANCODE_6) \
    X(SDL_SCANCODE_7) \
    X(SDL_SCANCODE_8) \
    X(SDL_SCANCODE_9) \
    X(SDL_SCANCODE_0) \
    X(SDL_SCANCODE_RETURN) \
    X(SDL_SCANCODE_ESCAPE) \
    X(SDL_SCANCODE_BACKSPACE) \
    X(SDL_SCANCODE_TAB) \
    X(SDL_SCANCODE_SPACE) \
    X(SDL_SCANCODE_MINUS) \
    X(SDL_SCANCODE_EQUALS) \
    X(SDL_SCANCODE_LEFTBRACKET) \
    X(SDL_SCANCODE_RIGHTBRACKET) \
    X(SDL_SCANCODE_BACKSLASH) \
    X(SDL_SCANCODE_NONUSHASH) \
    X(SDL_SCANCODE_SEMICOLON) \
    X(SDL_SCANCODE_APOSTROPHE) \
    X(SDL_SCANCODE_GRAVE) \
    X(SDL_SCANCODE_COMMA) \
    X(SDL_SCANCODE_PERIOD) \
    X(SDL_SCANCODE_SLASH) \
    X(SDL_SCANCODE_CAPSLOCK) \
    X(SDL_SCANCODE_F1) \
    X(SDL_SCANCODE_F2) \
    X(SDL_SCANCODE_F3) \
    X(SDL_SCANCODE_F4) \
    X(SDL_SCANCODE_F5) \
    X(SDL_SCANCODE_F6) \
    X(SDL_SCANCODE_F7) \
    X(SDL_SCANCODE_F8) \
    X(SDL_SCANCODE_F9) \
    X(SDL_SCANCODE_F10) \
    X(SDL_SCANCODE_F11) \
    X(SDL_SCANCODE_F12) \
    X(SDL_SCANCODE_PRINTSCREEN) \
    X(SDL_SCANCODE_SCROLLLOCK) \
    X(SDL_SCANCODE_PAUSE) \
    X(SDL_SCANCODE_INSERT) \
    X(SDL_SCANCODE_HOME) \
    X(SDL_SCANCODE_PAGEUP) \
    X(SDL_SCANCODE_DELETE) \
    X(SDL_SCANCODE_END) \
    X(SDL_SCANCODE_PAGEDOWN) \
    X(SDL_SCANCODE_RIGHT) \
    X(SDL_SCANCODE_LEFT) \
    X(SDL_SCANCODE_DOWN) \
    X(SDL_SCANCODE_UP) \
    X(SDL_SCANCODE_NUMLOCKCLEAR) \
    X(SDL_SCANCODE_KP_DIVIDE) \
    X(SDL_SCANCODE_KP_MULTIPLY) \
    X(SDL_SCANCODE_KP_MINUS) \
    X(SDL_SCANCODE_KP_PLUS) \
    X(SDL_SCANCODE_KP_ENTER) \
    X(SDL_SCANCODE_KP_1) \
    X(SDL_SCANCODE_KP_2) \
    X(SDL_SCANCODE_KP_3) \
    X(SDL_SCANCODE_KP_4) \
    X(SDL_SCANCODE_KP_5) \
    X(SDL_SCANCODE_KP_6) \
    X(SDL_SCANCODE_KP_7) \
    X(SDL_SCANCODE_KP_8) \
    X(SDL_SCANCODE_KP_9) \
    X(SDL_SCANCODE_KP_0) \
    X(SDL_SCANCODE_KP_PERIOD) \
    X(SDL_SCANCODE_NONUSBACKSLASH) \
    X(SDL_SCANCODE_APPLICATION) \
    X(SDL_SCANCODE_POWER) \
    X(SDL_SCANCODE_KP_EQUALS) \
    X(SDL_SCANCODE_F13) \
    X(SDL_SCANCODE_F14) \
    X(SDL_SCANCODE_F15) \
    X(SDL_SCANCODE_F16) \
    X(SDL_SCANCODE_F17) \
    X(SDL_SCANCODE_F18) \
    X(SDL_SCANCODE_F19) \
    X(SDL_SCANCODE_F20) \
    X(SDL_SCANCODE_F21) \
    X(SDL_SCANCODE_F22) \
    X(SDL_SCANCODE_F23) \
    X(SDL_SCANCODE_F24) \
    X(SDL_SCANCODE_EXECUTE) \
    X(SDL_SCANCODE_HELP) \
    X(SDL_SCANCODE_MENU) \
    X(SDL_SCANCODE_SELECT) \
    X(SDL_SCANCODE_STOP) \
    X(SDL_SCANCODE_AGAIN) \
    X(SDL_SCANCODE_UNDO) \
    X(SDL_SCANCODE_CUT) \
    X(SDL_SCANCODE_COPY) \
    X(SDL_SCANCODE_PASTE) \
    X(SDL_SCANCODE_FIND) \
    X(SDL_SCANCODE_MUTE) \
    X(SDL_SCANCODE_VOLUMEUP) \
    X(SDL_SCANCODE_VOLUMEDOWN) \
    X(SDL_SCANCODE_KP_COMMA) \
    X(SDL_SCANCODE_KP_EQUALSAS400) \
    X(SDL_SCANCODE_INTERNATIONAL1) \
    X(SDL_SCANCODE_INTERNATIONAL2) \
    X(SDL_SCANCODE_INTERNATIONAL3) \
    X(SDL_SCANCODE_INTERNATIONAL4) \
    X(SDL_SCANCODE_INTERNATIONAL5) \
    X(SDL_SCANCODE_INTERNATIONAL6) \
    X(SDL_SCANCODE_INTERNATIONAL7) \
    X(SDL_SCANCODE_INTERNATIONAL8) \
    X(SDL_SCANCODE_INTERNATIONAL9) \
    X(SDL_SCANCODE_LANG1) \
    X(SDL_SCANCODE_LANG2) \
    X(SDL_SCANCODE_LANG3) \
    X(SDL_SCANCODE_LANG4) \
    X(SDL_SCANCODE_LANG5) \
    X(SDL_SCANCODE_LANG6) \
    X(SDL_SCANCODE_LANG7) \
    X(SDL_SCANCODE_LANG8) \
    X(SDL_SCANCODE_LANG9) \
    X(SDL_SCANCODE_ALTERASE) \
    X(SDL_SCANCODE_SYSREQ) \
    X(SDL_SCANCODE_CANCEL) \
    X(SDL_SCANCODE_CLEAR) \
    X(SDL_SCANCODE_PRIOR) \
    X(SDL_SCANCODE_RETURN2) \
    X(SDL_SCANCODE_SEPARATOR) \
    X(SDL_SCANCODE_OUT) \
    X(SDL_SCANCODE_OPER) \
    X(SDL_SCANCODE_CLEARAGAIN) \
    X(SDL_SCANCODE_CRSEL) \
    X(SDL_SCANCODE_EXSEL) \
    X(SDL_SCANCODE_KP_00) \
    X(SDL_SCANCODE_KP_000) \
    X(SDL_SCANCODE_THOUSANDSSEPARATOR) \
    X(SDL_SCANCODE_DECIMALSEPARATOR) \
    X(SDL_SCANCODE_CURRENCYUNIT) \
    X(SDL_SCANCODE_CURRENCYSUBUNIT) \
    X(SDL_SCANCODE_KP_LEFTPAREN) \
    X(SDL_SCANCODE_KP_RIGHTPAREN) \
    X(SDL_SCANCODE_KP_LEFTBRACE) \
    X(SDL_SCANCODE_KP_RIGHTBRACE) \
    X(SDL_SCANCODE_KP_TAB) \
    X(SDL_SCANCODE_KP_BACKSPACE) \
    X(SDL_SCANCODE_KP_A) \
    X(SDL_SCANCODE_KP_B) \
    X(SDL_SCANCODE_KP_C) \
    X(SDL_SCANCODE_KP_D) \
    X(SDL_SCANCODE_KP_E) \
    X(SDL_SCANCODE_KP_F) \
    X(SDL_SCANCODE_KP_XOR) \
    X(SDL_SCANCODE_KP_POWER) \
    X(SDL_SCANCODE_KP_PERCENT) \
    X(SDL_SCANCODE_KP_LESS) \
    X(SDL_SCANCODE_KP_GREATER) \
    X(SDL_SCANCODE_KP_AMPERSAND) \
    X(SDL_SCANCODE_KP_DBLAMPERSAND) \
    X(SDL_SCANCODE_KP_VERTICALBAR) \
    X(SDL_SCANCODE_KP_DBLVERTICALBAR) \
    X(SDL_SCANCODE_KP_COLON) \
    X(SDL_SCANCODE_KP_HASH) \
    X(SDL_SCANCODE_KP_SPACE) \
    X(SDL_SCANCODE_KP_AT) \
    X(SDL_SCANCODE_KP_EXCLAM) \
    X(SDL_SCANCODE_KP_MEMSTORE) \
    X(SDL_SCANCODE_KP_MEMRECALL) \
    X(SDL_SCANCODE_KP_MEMCLEAR) \
    X(SDL_SCANCODE_KP_MEMADD) \
    X(SDL_SCANCODE_KP_MEMSUBTRACT) \
    X(SDL_SCANCODE_KP_MEMMULTIPLY) \
    X(SDL_SCANCODE_KP_MEMDIVIDE) \
    X(SDL_SCANCODE_KP_PLUSMINUS) \
    X(SDL_SCANCODE_KP_CLEAR) \
    X(SDL_SCANCODE_KP_CLEARENTRY) \
    X(SDL_SCANCODE_KP_BINARY) \
    X(SDL_SCANCODE_KP_OCTAL) \
    X(SDL_SCANCODE_KP_DECIMAL) \
    X(SDL_SCANCODE_KP_HEXADECIMAL) \
    X(SDL_SCANCODE_LCTRL) \
    X(SDL_SCANCODE_LSHIFT) \
    X(SDL_SCANCODE_LALT) \
    X(SDL_SCANCODE_LGUI) \
    X(SDL_SCANCODE_RCTRL) \
    X(SDL_SCANCODE_RSHIFT) \
    X(SDL_SCANCODE_RALT) \
    X(SDL_SCANCODE_RGUI) \
    X(SDL_SCANCODE_MODE) \
    X(SDL_SCANCODE_AC_SEARCH) \
    X(SDL_SCANCODE_AC_HOME) \
    X(SDL_SCANCODE_AC_BACK) \
    X(SDL_SCANCODE_AC_FORWARD) \
    X(SDL_SCANCODE_AC_STOP) \
    X(SDL_SCANCODE_AC_REFRESH) \
    X(SDL_SCANCODE_AC_BOOKMARKS) \
    X(SDL_SCANCODE_AC_NEW) \
    X(SDL_SCANCODE_AC_OPEN) \
    X(SDL_SCANCODE_AC_EXIT) \
    X(SDL_SCANCODE_AC_SAVE) \
    X(SDL_SCANCODE_AC_PRINT) \
    X(SDL_SCANCODE_AC_CLOSE) \
    X(SDL_SCANCODE_AC_PROPERTIES) \
    X(SDL_SCANCODE_SLEEP) \
    X(SDL_SCANCODE_WAKE) \
    X(SDL_SCANCODE_CHANNEL_INCREMENT) \
    X(SDL_SCANCODE_CHANNEL_DECREMENT) \
    X(SDL_SCANCODE_MEDIA_PLAY) \
    X(SDL_SCANCODE_MEDIA_PAUSE) \
    X(SDL_SCANCODE_MEDIA_RECORD) \
    X(SDL_SCANCODE_MEDIA_FAST_FORWARD) \
    X(SDL_SCANCODE_MEDIA_REWIND) \
    X(SDL_SCANCODE_MEDIA_NEXT_TRACK) \
    X(SDL_SCANCODE_MEDIA_PREVIOUS_TRACK) \
    X(SDL_SCANCODE_MEDIA_STOP) \
    X(SDL_SCANCODE_MEDIA_EJECT) \
    X(SDL_SCANCODE_MEDIA_PLAY_PAUSE) \
    X(SDL_SCANCODE_MEDIA_SELECT) \
    X(SDL_SCANCODE_SOFTLEFT) \
    X(SDL_SCANCODE_SOFTRIGHT) \
    X(SDL_SCANCODE_CALL) \
    X(SDL_SCANCODE_ENDCALL) \
    X(SDL_SCANCODE_RESERVED) \
    X(SDL_NUM_SCANCODES)


typedef struct SDLEXT_Key {
    timestamp_t last_down; /* Time of last key down event as monotonic. */
    timestamp_t last_up; /* Time of last key up event as monotonic. */
    bool is_down; /* Whether the key is currently held. */

    int _sdl_scancode; /* The internal SDL scancode associated with this key struct. */
} SDLEXT_Key;

typedef struct SDLEXT_Keys {
    #define SDL_SCANCODE_TO_SDLEXT_KEY(sdl_scancode) key_##sdl_scancode
    #define X(key) SDLEXT_Key SDL_SCANCODE_TO_SDLEXT_KEY(key);
        X_ALL_SDL_KEYCODES
    #undef X
} SDLEXT_Keys;