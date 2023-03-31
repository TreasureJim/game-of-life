#ifndef GAME_h_
#define GAME_h_

#include <SDL2/SDL.h>
#include "window.h"

void Game_RunFrame(SDL_Renderer* renderer, Window_Texture* texture, uint32_t* pixels);

void* FixedUpdate(void*);

#endif
