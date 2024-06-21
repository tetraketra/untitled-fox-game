#ifndef TGH_H
#define TGH_H

#include "ttk/ttk.h"
#include <glad/glad.h> /* This order is required! glad > glfw */
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

/*
    === INFO ===
    1. Tetra's GL, "tgl", is an OpenGL & GLFW wrapper utility library built by @TetraKetra.
    2. This file contains macros for use in all tgl sublibraries, plus wherever else you want.
*/

typedef struct state_window_t {
    GLFWmonitor*        monitor;
    const GLFWvidmode*  vidmode;
    GLFWwindow*         window;
    const char*         title;
    int                 x;
    int                 y;
    int                 w;
    int                 h;

    int                 hint_v_maj;
    int                 hint_v_min;
} state_window_t;

typedef struct tgl_state_t {
    state_window_t window;
} tgl_state_t;

extern tgl_state_t tgl_state;

/* 
    === DEFAULTS ===
*/

#define TGL_DEFAULT__WINDOW_TITLE "Congrats, you have a window!"
#define TGL_DEFAULT__WINDOW_HINT_V_MAJ 4
#define TGL_DEFAULT__WINDOW_HINT_V_MIN 6
#define TGL_DEFAULT__WINDOW_H 720
#define TGL_DEFAULT__WINDOW_W 1280

#endif