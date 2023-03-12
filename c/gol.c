#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "window.h"
#include "macros.h"
#include "game.h"
#include <SDL2/SDL_ttf.h>

const uint32_t SCREEN_WIDTH = 720;
const uint32_t SCREEN_HEIGHT = 900;

TTF_Font* g_font;

int main(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	// Initialize SDL
	if (Window_Init(&window, SCREEN_WIDTH, SCREEN_HEIGHT) < 0)
		return 1;

	if (TTF_Init() < 0)
	{
		fprintf(stderr, "Couldn't initialise TTF. SDL error: %s", SDL_GetError());
		defer(EXIT_FAILURE);
	}
	g_font = TTF_OpenFont("./fonts/Minimal5x7.ttf", 48);
	if (!g_font) {
		fprintf(stderr, "Failed to load font. SDL error: %s", SDL_GetError());
		defer(EXIT_FAILURE);
	}


	// screenSurface = SDL_GetWindowSurface(window);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Renderer could not be created. SDL error: %s\n", SDL_GetError());
		defer(EXIT_FAILURE);
	}

	Window_Texture* texture = Window_CreateTexture(renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
	if (!texture)
		defer(1);

	// Edit raw pixel data
	uint32_t* pixels = malloc(texture->width * 4 * texture->height);

	// keep window up
	SDL_Event e;
	while (true)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			break;

		Game_RunFrame(renderer, texture, pixels);
	}

defer:
	TTF_CloseFont(g_font);
	TTF_Quit();
	SDL_DestroyTexture(texture->texture);
	SDL_DestroyRenderer(renderer);
	Window_Close(window);
	return result;
}
