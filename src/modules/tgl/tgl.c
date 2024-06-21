#include "tgl.h"

tgl_state_t tgl_state = {
    .window = {
        .title = TGL_DEFAULT__WINDOW_TITLE,
        .hint_v_maj = TGL_DEFAULT__WINDOW_HINT_V_MAJ,
        .hint_v_min = TGL_DEFAULT__WINDOW_HINT_V_MIN,
        .w = TGL_DEFAULT__WINDOW_W,
        .h = TGL_DEFAULT__WINDOW_H
    }
};

static void __attribute__((constructor)) tgl_init(void) {

    /* Initialize GLFW. */
    if (glfwInit() == GLFW_FALSE) {
        ERROR("Failed to initialize GLFW!");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, tgl_state.window.hint_v_maj);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, tgl_state.window.hint_v_min);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Initialize window. */
    tgl_state.window.window  = glfwCreateWindow(
        tgl_state.window.w, tgl_state.window.h,
        tgl_state.window.title, NULL, NULL
    );

    if (tgl_state.window.window == NULL){
        ERROR("Failed to create GLFW window!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(tgl_state.window.window);

    /* Initialize GLAD. */
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0){
        ERROR("Failed to initialize GLAD and link to GLFW!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* get primary monitor and its attributes */
    tgl_state.window.monitor = glfwGetPrimaryMonitor();
    if (tgl_state.window.monitor == NULL) {
        ERROR("Failed to get primary monitor!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    tgl_state.window.vidmode = glfwGetVideoMode(tgl_state.window.monitor);
    if (tgl_state.window.vidmode == NULL) {
        ERROR("Failed to get primary monitor video mode!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while (!glfwWindowShouldClose(tgl_state.window.window)) {
        glfwPollEvents();
    };
    glfwTerminate();
    exit(EXIT_SUCCESS);
}