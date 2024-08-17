#ifndef TGL_STATE_H
#define TGL_STATE_H

#include "tgl.h"

/*
    === INFO ===
    1. TGL state structs and defaults for use in (?almost?) all TGL internals
    2. Don't touch these yourself.
*/

/* ---------------------------------------------------- */
typedef struct tgls_window_t {
    GLFWmonitor*        glfw_monitor;
    const GLFWvidmode*  gflw_vidmode;
    GLFWwindow*         gflw_window;
    const char*         title;

    int                 x;
    int                 y;
    int                 w;
    int                 h;

    int                 x_restore;
    int                 y_restore;
    int                 w_restore;
    int                 h_restore;

    int                 hint_v_maj;
    int                 hint_v_min;
} tgls_window_t;

/* ---------------------------------------------------- */
typedef struct tgls_flags_t {
    bool debug;
    bool freecam;
    bool vsync;
    bool focus;
    bool mouse_capture;
    bool focus_regained;
} tgls_flags_t;

/* ---------------------------------------------------- */
typedef struct timespec timespec_t;
typedef struct tgls_key_t {
    timestamp_t last_down; /* Time of last key down event as monotonic. */
    timestamp_t last_up; /* Time of last key up event as monotonic. */
    bool is_down; /* Whether the key is currently held. */

    int _glfw_key; /* The internal glfw keycode associated with this tgls key struct. */
} tgls_key_t;

#define X_ALL_GLFW_KEYS \
    /* Keyboard Numbers */ \
    X(GLFW_KEY_0) \
    X(GLFW_KEY_1) \
    X(GLFW_KEY_2) \
    X(GLFW_KEY_3) \
    X(GLFW_KEY_4) \
    X(GLFW_KEY_5) \
    X(GLFW_KEY_6) \
    X(GLFW_KEY_7) \
    X(GLFW_KEY_8) \
    X(GLFW_KEY_9) \
    /* Keyboard Specials */ \
    X(GLFW_KEY_ESCAPE) \
    X(GLFW_KEY_TAB) \
    X(GLFW_KEY_SPACE) \
    X(GLFW_KEY_BACKSPACE) \
    X(GLFW_KEY_DELETE) \
    X(GLFW_KEY_ENTER) \
    /* Keyboard Modifiers */ \
    X(GLFW_KEY_LEFT_SHIFT) \
    X(GLFW_KEY_RIGHT_SHIFT) \
    X(GLFW_KEY_LEFT_CONTROL) \
    X(GLFW_KEY_RIGHT_CONTROL) \
    X(GLFW_KEY_LEFT_ALT) \
    X(GLFW_KEY_RIGHT_ALT) \
    X(GLFW_KEY_LEFT_SUPER) \
    X(GLFW_KEY_RIGHT_SUPER) \
    /* Keyboard Letters */ \
    X(GLFW_KEY_Q) \
    X(GLFW_KEY_W) \
    X(GLFW_KEY_E) \
    X(GLFW_KEY_R) \
    X(GLFW_KEY_T) \
    X(GLFW_KEY_Y) \
    X(GLFW_KEY_U) \
    X(GLFW_KEY_I) \
    X(GLFW_KEY_O) \
    X(GLFW_KEY_P) \
    X(GLFW_KEY_A) \
    X(GLFW_KEY_S) \
    X(GLFW_KEY_D) \
    X(GLFW_KEY_F) \
    X(GLFW_KEY_G) \
    X(GLFW_KEY_H) \
    X(GLFW_KEY_J) \
    X(GLFW_KEY_K) \
    X(GLFW_KEY_L) \
    X(GLFW_KEY_Z) \
    X(GLFW_KEY_X) \
    X(GLFW_KEY_C) \
    X(GLFW_KEY_V) \
    X(GLFW_KEY_B) \
    X(GLFW_KEY_N) \
    X(GLFW_KEY_M) \
    /* Keyboard Other */ \
    X(GLFW_KEY_MINUS) \
    X(GLFW_KEY_EQUAL) \
    X(GLFW_KEY_LEFT_BRACKET) \
    X(GLFW_KEY_RIGHT_BRACKET) \
    X(GLFW_KEY_BACKSLASH) \
    X(GLFW_KEY_SLASH) \
    X(GLFW_KEY_SEMICOLON) \
    X(GLFW_KEY_APOSTROPHE) \
    X(GLFW_KEY_COMMA) \
    X(GLFW_KEY_PERIOD) \
    /* Keypad Numbers */ \
    X(GLFW_KEY_KP_0) \
    X(GLFW_KEY_KP_1) \
    X(GLFW_KEY_KP_2) \
    X(GLFW_KEY_KP_3) \
    X(GLFW_KEY_KP_4) \
    X(GLFW_KEY_KP_5) \
    X(GLFW_KEY_KP_6) \
    X(GLFW_KEY_KP_7) \
    X(GLFW_KEY_KP_8) \
    X(GLFW_KEY_KP_9) \
    /* Keypad Other */ \
    X(GLFW_KEY_KP_ADD) \
    X(GLFW_KEY_KP_SUBTRACT) \
    X(GLFW_KEY_KP_DECIMAL) \
    X(GLFW_KEY_KP_MULTIPLY) \
    X(GLFW_KEY_KP_DIVIDE) \
    X(GLFW_KEY_KP_ENTER) \
    X(GLFW_KEY_KP_EQUAL)

typedef struct tgls_keys_t {
    #define TGLS_KEY(glfw_key) key_##glfw_key
    #define TGLS_KEY_VAR(glfw_key) tgls.keys.TGLS_KEY(glfw_key)

    #define X(glfw_key) tgls_key_t TGLS_KEY(glfw_key);
    X_ALL_GLFW_KEYS
    #undef X
} tgls_keys_t;

/* ---------------------------------------------------- */
typedef struct tgls_t {
    tgls_window_t   window;
    tgls_flags_t    flags;
    tgls_keys_t     keys;
} tgls_t;

extern tgls_t tgls;

/* ---------------------------------------------------- */
#define TGLS_DEFAULT__WINDOW_TITLE "Congrats, you have a window!"
#define TGLS_DEFAULT__WINDOW_HINT_V_MAJ 4
#define TGLS_DEFAULT__WINDOW_HINT_V_MIN 6
#define TGLS_DEFAULT__WINDOW_H 720
#define TGLS_DEFAULT__WINDOW_W 1280

#endif