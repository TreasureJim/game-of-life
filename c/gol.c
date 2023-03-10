#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "window.h"
#include "macros.h"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 900;

int main(int argc, char *argv[])
{
	int result = EXIT_SUCCESS;

	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	// Initialize SDL
	if (Window_Init(&window, SCREEN_WIDTH, SCREEN_HEIGHT) < 0)
		return 1;

	// screenSurface = SDL_GetWindowSurface(window);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Renderer could not be created. SDL error: %s\n", SDL_GetError());
		defer(EXIT_FAILURE);
	}

	Window_Texture *texture = Window_CreateTexture(renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
	if (!texture)
		defer(1);

	// Edit raw pixel data
	uint32_t *pixels = malloc(texture->width * 4 * texture->height);

	// for (int i = 0; i < texture->height * texture->width; i++)
	// {
	// 	pixels[i] = SDL_MapRGB(texture->pixel_format, i, 0, 0);
	// }
	// Window_UpdatePixels(renderer, texture, pixels);

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
	SDL_DestroyTexture(texture->texture);
	SDL_DestroyRenderer(renderer);
	Window_Close(window);
	return result;
}
