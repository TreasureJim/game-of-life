#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <stdbool.h>
#include <stdio.h>

#include "globals.h"
#include "input_handler.h"

static bool mouse_pressed = false;
static int mouse_x, mouse_y;

void Window_HandleInput(SDL_Event e) {
	// Mouse inputs
	if (e.type == SDL_MOUSEBUTTONDOWN) mouse_pressed = true;
	if (e.type == SDL_MOUSEBUTTONUP) mouse_pressed = false;

	if (mouse_pressed) Window_HandleMouseInput();

	// Keyboard inputs
	// TODO
}

void Window_HandleMouseInput() {
	static int x, y;
	SDL_GetMouseState(&x, &y);

	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT || (mouse_x == x && mouse_y == y)) {
		return;
	}

	mouse_x = x;
	mouse_y = y;
	Game_HandleClick(x, y);
}
