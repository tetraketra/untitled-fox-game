#include "tgl.h"
#include "tgl/callbacks.h"
#include "tgl/state.h"

/*
    Initializes TGL with a basic window.

    @note If this fails, something is *very* wrong.
*/
void tgl_init(void) {

    /* Initialize GLFW. */
    if (glfwInit() == GLFW_FALSE) {
        FATAL("Failed to initialize GLFW!");
        exit(EXIT_FAILURE);
    }

    /* Initialize window. */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, tgls.window.hint_v_maj);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, tgls.window.hint_v_min);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    tgls.window.gflw_window = glfwCreateWindow(
        tgls.window.w, tgls.window.h,
        tgls.window.title, NULL, NULL
    );

    if (tgls.window.gflw_window == NULL){
        FATAL("Failed to create GLFW window!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(tgls.window.gflw_window);

    /* Initialize GLAD. */
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0){
        FATAL("Failed to initialize GLAD and link to GLFW!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Initialize monitor. */
    tgls.window.glfw_monitor = glfwGetPrimaryMonitor();
    if (tgls.window.glfw_monitor == NULL) {
        FATAL("Failed to get primary monitor!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Initialize monitor's viewmode. */
    tgls.window.gflw_vidmode = glfwGetVideoMode(tgls.window.glfw_monitor);
    if (tgls.window.gflw_vidmode == NULL) {
        FATAL("Failed to get primary monitor video mode!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Initialize keys. */
    #define X(glfw_key) TGLS_KEY_VAR(glfw_key)._glfw_key = glfw_key;
    X_ALL_GLFW_KEYS
    #undef X

    /* Configure default callbacks. */
    glfwSetFramebufferSizeCallback(tgls.window.gflw_window, tgl_callback_window_resize);
    glfwSetWindowPosCallback(tgls.window.gflw_window, tgl_callback_window_pos);
    glfwSetKeyCallback(tgls.window.gflw_window, tgl_callback_key);

    /* Configure textures. */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* Configure miscellaneous. */
    glViewport(0, 0, tgls.window.w, tgls.window.h);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
}


/*
    Most-basic run loop with exit termination.
    For testing initialization.

    @note If this fails, something is *very* wrong.
*/
void tgl_run_minimal(void) {
    while (!glfwWindowShouldClose(tgls.window.gflw_window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(tgls.window.gflw_window);
        glfwPollEvents();
    };

    glfwTerminate();
    exit(EXIT_SUCCESS);
}