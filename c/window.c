#include <SDL2/SDL.h>
#include "window.h"

int Window_Init(SDL_Window **window, uint16_t screen_width, uint16_t screen_height)
{
	// Initialize SDL
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize. SDL error: %s\n", SDL_GetError());
		return -1;
	}

	// Initialize window
	*window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Could not be created. SDL error: %s", SDL_GetError());
		return -1;
	}

	return 0;
}

void Window_Close(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Window_UpdatePixels(SDL_Renderer *renderer, Window_Texture *texture, uint32_t *pixels)
{
	uint32_t *texture_pixels;
	int texture_width;
	SDL_LockTexture(texture->texture, NULL, (void **)&texture_pixels, &texture_width);

	memcpy(texture_pixels, pixels, texture->height * texture_width);

	SDL_UnlockTexture(texture->texture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture->texture, NULL, NULL);

	SDL_RenderPresent(renderer);
}

Window_Texture *Window_CreateTexture(SDL_Renderer *renderer, uint32_t width, uint32_t height)
{
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!texture)
	{
		fprintf(stderr, "Cant create texture. SDL error: %s", SDL_GetError());
		return NULL;
	}

	SDL_PixelFormat *texture_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	Window_Texture *p_window_texture = malloc(sizeof(Window_Texture));
	Window_Texture window_texture = {texture, texture_format, width, height};
	*p_window_texture = window_texture;

	return p_window_texture;
}