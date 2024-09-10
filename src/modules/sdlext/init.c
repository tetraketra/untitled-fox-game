#include "init.h"

/*
    Initialize SDL and necessary SDLEXT structs.

    @param window Address of the SDL_Window to initialize. You'll have to define this yourself.
    @param context Address of the SDL_GLContext to initialize. (^) Define yourself.
    @param keys Address of the SDLEXT_Keys to initialize. (^) Define yourself.
*/
void sdlext_init(
    SDL_Window** window, 
    SDL_GLContext* context, 
    SDLEXT_Keys* keys,
    SDL_Event* event,
    SDL_bool* quit
) {
    atexit(SDL_Quit);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == SDL_FALSE) {
        ERROR("Could not initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *window = NULL;
    if ((*window=SDL_CreateWindow("!yippie!", 800, 600, SDL_WINDOW_OPENGL)) == NULL) {
        ERROR("Could not initialize SDL_Window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *context = (SDL_GLContext){0};
    if ((*context=SDL_GL_CreateContext(*window)) == NULL) {
        ERROR("Could not create SDL_GLContext: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *keys = (SDLEXT_Keys){0};
    if (keys->key_SDL_SCANCODE_0.is_down != false) {
        ERROR("Failed to initialize SDLEXT_Keys.\n");
        exit(EXIT_FAILURE);
    }

    *event = (SDL_Event){0};
    if (event->type != 0) {
        ERROR("Failed to initialize SDL_Event.\n");
        exit(EXIT_FAILURE);
    }

    *quit = false;
    if (*quit) {
        ERROR("Failed to initialize SDL_bool.\n");
        INFO("If this doesn't work on your computer, seek help.");
        exit(EXIT_FAILURE);
    }
}

/*
    Tears down SDL and necessary SDLEXT structs, then exits.

    @param window Address of the SDL_Window to tear down.
    @param context Address of the SDL_GLContext to tear down.
*/
void sdlext_exit(
    SDL_Window** window, 
    SDL_GLContext* context
) {
    SDL_GL_DestroyContext(*context);
    SDL_DestroyWindow(*window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}