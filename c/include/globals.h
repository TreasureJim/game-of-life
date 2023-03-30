#ifndef GLOBALS_h_
#define GLOBALS_h_

#include <SDL2/SDL_ttf.h>
#include <pthread.h>

#include "window.h"

extern uint32_t SCREEN_WIDTH;
extern uint32_t SCREEN_HEIGHT;

extern TTF_Font* g_font;
extern Window_Container* window_container;

extern pthread_mutex_t m_game_running;
extern uint8_t game_frequency;
extern pthread_mutex_t m_game_pixels;
extern uint32_t* game_pixels;

#endif
