#pragma once 

#include <SDL2/SDL.h>
#include "config.h"

extern char front_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT];

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern const Uint8 *keystate;

extern char game_running;

extern char centre_text[100];
