#ifndef INPUT_HANDLER_h_
#define INPUT_HANDLER_h_

#include <SDL2/SDL_events.h>

void Window_HandleInput(SDL_Event e);
void Window_HandleMouseInput();
void Game_HandleClick(int x, int y);

#endif
