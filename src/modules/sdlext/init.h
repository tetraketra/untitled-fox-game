#ifndef SDLEXT_INIT_H
#define SDLEXT_INIT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "toolkit/toolkit.h"
#include "sdlext/keys.h"

void sdlext_init(SDL_Window** window, SDL_GLContext* context, SDLEXT_Keys* keys, SDL_Event* event, SDL_bool* quit);
void sdlext_exit(SDL_Window** window, SDL_GLContext* context);

#endif