#ifndef TGL_STATE_H
#define TGL_STATE_H

#include "tgl.h"

/*
    === INFO ===
    1. TGL state structs and defaults for use in (?almost?) all TGL internals
    2. Don't touch these yourself.
*/

typedef struct tgls_window_t {
    GLFWmonitor*        glfw_monitor;
    const GLFWvidmode*  gflw_vidmode;
    GLFWwindow*         gflw_window;
    const char*         title;

    /* Window positioning. */
    int                 x;
    int                 y;
    int                 w;
    int                 h;

    /* For sensible unfullscreening. */
    int                 x_restore; 
    int                 y_restore;
    int                 w_restore;
    int                 h_restore;

    /* Version hints. */
    int                 hint_v_maj;
    int                 hint_v_min;
} tgls_window_t;

typedef struct tgls_flags_t {
    bool debug;
    bool freecam;
    bool vsync;
    bool focus;
    bool mouse_capture;
    bool focus_regained; /* For clicking into the window. */
} tgls_flags_t;

typedef struct tgls_t {
    tgls_window_t   window;
    tgls_flags_t    flags;
} tgls_t;

extern tgls_t tgls;

#define TGLS_DEFAULT__WINDOW_TITLE "Congrats, you have a window!"
#define TGLS_DEFAULT__WINDOW_HINT_V_MAJ 4
#define TGLS_DEFAULT__WINDOW_HINT_V_MIN 6
#define TGLS_DEFAULT__WINDOW_H 720
#define TGLS_DEFAULT__WINDOW_W 1280

#endif