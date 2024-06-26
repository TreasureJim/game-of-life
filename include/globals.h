#pragma once 

#include <SDL2/SDL.h>
#include "config.h"

#define MAX_FRAME_LENGTH 1/(float)FRAME_MAX

extern char front_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT];
extern char back_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT];

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern const Uint8 *keystate;

extern char game_running;

extern char text_buffer[TEXT_BUFFER_SIZE];
