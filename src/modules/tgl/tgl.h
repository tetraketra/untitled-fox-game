#ifndef TGH_H
#define TGH_H

#include "ttk/ttk.h"
#include <glad/glad.h> /* This order is required! (1) glad, (2) glfw */
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

/*
    === INFO ===
    1. TGL, Tetra's GL, is an OpenGL & GLFW wrapper utility library built by @TetraKetra.
    2. This file contains macros and includes for use in all TGL sublibraries.
    3. Component breakdown:
        * `tgl.c/h`: What's exposed to the user, plus required includes.
        * `tgl_state.c/h`: Internal state structs and their defaults.
        - `tgl_callbacks.c/h`: Built-in GLFW callbacks.
*/

extern void tgl_init(void);
extern void tgl_run_minimal(void);

#endif