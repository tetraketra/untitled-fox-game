#include "toolkit/toolkit.h"
#include "toolkit/time.h"
#include "sdlext/init.h"
#include "sdlext/keys.h"
#include "sdlext/mouse.h"
#include "sdlext/window.h"

int main(void) {

    /* SDL setup. */
    SDL_Window* window;
    SDL_GLContext context;
    SDL_Event event;
    SDL_bool quit;
    SDLEXT_Keys sdlext_keys;
    SDLEXT_Mouse sdlext_mouse;
    SDLEXT_Window sdlext_window;

    sdlext_init(
        &window, 
        &context, 
        &event, 
        &quit, 
        &sdlext_keys, 
        &sdlext_mouse, 
        &sdlext_window
    );

    /* Event loop. */
    while (SDL_PollEvent(&event) || !quit) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        sdlext_window_update(&event, &sdlext_window);
        sdlext_keys_update(&event, &sdlext_keys);
        sdlext_mouse_update(&event, &sdlext_mouse, &sdlext_window);

        switch (event.type) {
            case SDL_EVENT_QUIT: 
                INFO("User quit the app via SDL_EVENT_QUIT.\n");
                quit = true;
                break;
        }

        SDL_GL_SwapWindow(window);
    }

    sdlext_exit(&window, &context);
}