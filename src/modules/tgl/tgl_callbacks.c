#include "tgl_callbacks.h"

/*
    TGL's standard callback for handling window resizing.

    @param `window`: Your glfw window. Ignored.
    @param `w`: The new width of the window.
    @param `h`: The new height of the window.

    @note Intended for use in `glfwSet...Callback` and *nowhere else*.
*/
void tgl_callback_window_resize(GLFWwindow* window, int w, int h) {
    IGNORE(window);

    tgls.window.w_restore = tgls.window.w;
    tgls.window.h_restore = tgls.window.h;

    tgls.window.w = w;
    tgls.window.h = h;

    glViewport(0, 0, w, h);
    /* TODO insert fov preserving function here (set_fov) when written and relevant. */
}

/*
    TGL's standard callback for handling window movement.

    @param `window`: Your glfw window. Ignored.
    @param `x`: The new x coordinate of the window.
    @param `y`: The new y coordinate of the window.

    @note Intended for use in `glfwSet...Callback` and *nowhere else*.
*/
void tgl_callback_window_pos(GLFWwindow* window, int x, int y) {
    IGNORE(window);

    tgls.window.x_restore = tgls.window.x;
    tgls.window.y_restore = tgls.window.y;

    tgls.window.x = x;
    tgls.window.y = y;
}

/*
    TGL's standard callback for handling key events.

    @param `window`: Your glfw window. Ignored.
    @param `key`: The `GLFW_KEY_*` of the key event.
    @param `scancode`: The platform-specific scancode for the key.
    @param `action`: `GLFW_PRESS` or `GLFW_RELEASE` (or technically `GLFW_REPEAT`).
    @param `mods`: The `GLFW_MOD_*`s of the key event.

    @note Intended for use in `glfwSet...Callback` and *nowhere else*.
*/
void tgl_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    IGNORE(window);
    IGNORE(scancode);
    IGNORE(mods); /* For now... */

    #define X(glfw_key) \
        case glfw_key: \
            switch (action) { \
                case GLFW_PRESS: \
                    TGLS_KEY_VAR(glfw_key).is_down = true; \
                    clock_gettime(CLOCK_MONOTONIC, &TGLS_KEY_VAR(glfw_key).last_key_down); \
                    break; \
                case GLFW_RELEASE: \
                    TGLS_KEY_VAR(glfw_key).is_down = false; \
                    clock_gettime(CLOCK_MONOTONIC, &TGLS_KEY_VAR(glfw_key).last_key_up); \
                    break; \
            } \
            break;

    switch (key) {
        X_ALL_GLFW_KEYS
    }
}