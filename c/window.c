#include <SDL2/SDL.h>
#include "window.h"
#include <SDL2/SDL_ttf.h>
#include "globals.h"

int Window_Init(SDL_Window** window, uint16_t screen_width, uint16_t screen_height)
{
	// Initialize SDL
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0)
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

void Window_Close(SDL_Window* window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Window_CopyPixels(SDL_Renderer* renderer, Window_Texture* texture, uint32_t* pixels)
{
	uint32_t* texture_pixels;
	int texture_width;
	SDL_LockTexture(texture->texture, NULL, (void**)&texture_pixels, &texture_width);

	memcpy(texture_pixels, pixels, texture->height * texture_width);

	SDL_UnlockTexture(texture->texture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture->texture, NULL, NULL);
}

Window_Texture* Window_CreateTexture(SDL_Renderer* renderer, uint32_t width, uint32_t height)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!texture)
	{
		fprintf(stderr, "Cant create texture. SDL error: %s", SDL_GetError());
		return NULL;
	}

	SDL_PixelFormat* texture_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	Window_Texture* p_window_texture = (Window_Texture*)malloc(sizeof(Window_Texture));
	Window_Texture window_texture = { texture, texture_format, width, height };
	*p_window_texture = window_texture;

	return p_window_texture;
}

int Window_RenderText(SDL_Renderer* renderer, char* text, WindowText_Options options) {
	SDL_Color fg = { 255, 255, 255, 255 }, bg = { 0,0,0,0 };
	SDL_Surface* text_surface = TTF_RenderUTF8_Solid(g_font, text, fg);

	if (options.fix_right) options.x = SCREEN_WIDTH - text_surface->w;
	if (options.fix_bottom) options.y = SCREEN_HEIGHT - text_surface->h;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	SDL_Rect dest = { options.x,options.y, text_surface->w, text_surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dest);

	// clean up
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text_surface);
}