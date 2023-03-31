#include <cstdlib>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>

#include "window.h"
#include "macros.h"
#include "game.h"

uint32_t SCREEN_WIDTH = 720;
uint32_t SCREEN_HEIGHT = 900;

Window_Container* window_container = NULL;

TTF_Font* g_font;

uint8_t game_frequency;
pthread_mutex_t m_game_running;
pthread_mutex_t m_game_pixels;
uint32_t* game_pixels = NULL;

int main(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;
	window_container = NULL;

	// Initialize SDL
	if (Window_Init(&window_container, SCREEN_WIDTH, SCREEN_HEIGHT) < 0)
		return 1;

	// Edit raw pixel data
	game_pixels = (uint32_t*)malloc(window_container->game_texture->width * window_container->game_texture->height * 4);
	if (!game_pixels) defer(EXIT_FAILURE);

	pthread_mutex_init(&m_game_running, NULL);
	pthread_t thread_fixed_update;
	pthread_create(&thread_fixed_update, NULL, &FixedUpdate, NULL);

	// keep window up
	SDL_Event e;
	while (true) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			break;

		Window_HandleInput(e);

		Window_Container_Render(window_container);
	}

defer:
	Window_Container_Close(window_container);
	pthread_mutex_destroy(&m_game_running);
	return result;
}
