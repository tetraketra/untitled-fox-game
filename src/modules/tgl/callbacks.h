#ifndef TGH_CALLBACKS_H
#define TGH_CALLBACKS_H

#include "tgl.h"
#include "state.h"

/*
    === INFO ===
    1. TGL's built-in GLFW callbacks.
    2. Ideally, the end user won't need to touch any `glfwSet...Callback` functions themselves.
*/

extern void     tgl_callback_window_resize(GLFWwindow* window, int w, int h);
extern void     tgl_callback_window_pos(GLFWwindow* window, int x, int y);
extern void     tgl_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif