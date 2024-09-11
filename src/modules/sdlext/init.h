#ifndef SDLEXT_INIT_H
#define SDLEXT_INIT_H

#include "sdlext.h"
#include "keys.h"
#include "mouse.h"
#include "window.h"

#define WINDOW_INIT_WIDTH 800
#define WINDOW_INIT_HEIGHT 600

void sdlext_init(
    SDL_Window** window, 
    SDL_GLContext* context, 
    SDL_Event* event, 
    SDL_bool* quit, 
    SDLEXT_Keys* keys, 
    SDLEXT_Mouse* mouse,
    SDLEXT_Window* window2
);
void sdlext_exit(SDL_Window** window, SDL_GLContext* context);

#endif