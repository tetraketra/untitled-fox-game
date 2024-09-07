#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

#include "toolkit/toolkit.h"
#include "toolkit/time.h"
#include "sdlext/keys.h"

int main(void) {
    /* SDL setup. */
    SDL_Window* window = NULL;
    SDL_GLContext context = {0};

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == SDL_FALSE) {
        ERROR("Could not initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if ((window=SDL_CreateWindow("!yippie!", 800, 600, SDL_WINDOW_OPENGL)) == NULL) {
        ERROR("Could not initialize SDL_Window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if ((context=SDL_GL_CreateContext(window)) == NULL) {
        ERROR("Could not create SDL_GLContext: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* SDLEXT setup. */
    SDLEXT_Keys keys = {0};

    if (keys.key_SDL_SCANCODE_0.is_down != false) {
        ERROR("Failed to initialize SDLEXT_Keys.\n");
        exit(EXIT_FAILURE);
    }

    /* Events loop. */
    SDL_Event event = {0};
    bool quit = false;
    while (SDL_WaitEvent(&event) && !quit) {
        switch (event.type) {

            /* Quit the app. */
            case SDL_EVENT_QUIT: 
                INFO("User quit the app via SDL_EVENT_QUIT.\n");
                quit = true;
                break;

            /* Keyboard input. */
            case SDL_EVENT_KEY_DOWN: /* =768 */
            case SDL_EVENT_KEY_UP:   /* =769 */ /* no gap, safe fallthrough! */
                if (event.key.repeat) break;
                switch (event.key.scancode) {
                    #define KEY_VAR(sdl_scancode) keys.SDL_SCANCODE_TO_SDLEXT_KEY(sdl_scancode)
                    #define X(sdl_scancode) \
                    case sdl_scancode: \
                        KEY_VAR(sdl_scancode).is_down = ( event.type == SDL_EVENT_KEY_DOWN ); \
                        event.type == SDL_EVENT_KEY_DOWN \
                            ? ( KEY_VAR(sdl_scancode).last_down = timestamp_get(true) ) \
                            : ( KEY_VAR(sdl_scancode).last_up   = timestamp_get(true) ); \
                        break;

                    X_ALL_SDL_SCANCODES

                    #undef X
                    #undef KEY_VAR
                }
                break;
        }
    }

    /* Teardown. */
    SDL_DestroyWindow(window);
    SDL_GL_DestroyContext(context);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}