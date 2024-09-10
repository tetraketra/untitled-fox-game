#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "toolkit/toolkit.h"
#include "toolkit/time.h"
#include "sdlext/init.h"
#include "sdlext/keys.h"

int main(void) {
    /* SDL setup. */
    SDL_Window* window;
    SDL_GLContext context;
    SDL_Event event;
    SDL_bool quit;
    SDLEXT_Keys keys;

    sdlext_init(&window, &context, &keys, &event, &quit);

    while (SDL_PollEvent(&event) || !quit) {
        sdlext_keys_update(&event, &keys);

        switch (event.type) {
            case SDL_EVENT_QUIT: 
                INFO("User quit the app via SDL_EVENT_QUIT.\n");
                quit = true;
                break;
        }
    }

    sdlext_exit(&window, &context);
}