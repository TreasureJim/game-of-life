#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include "globals.h"

#include "window.h"

/*
	Initialization functions
*/

int Window_Init(Window_Container** p_window_container, uint16_t screen_width, uint16_t screen_height)
{
	Window_Container* window_container = malloc(sizeof(Window_Container));
	*p_window_container = window_container;

	// Initialize SDL
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL could not initialize. SDL error: %s\n", SDL_GetError());
		return -1;
	}

	if (Window_Initialize_Font() == -1) return -1;

	// This setting hides the cursor
	/*SDL_SetRelativeMouseMode(SDL_TRUE);*/

	// Initialize window
	window_container->window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (!window_container->window) {
		fprintf(stderr, "Could not be created. SDL error: %s", SDL_GetError());
		return -1;
	}

	window_container->renderer = SDL_CreateRenderer(window_container->window, -1, 0);
	if (!window_container->renderer) {
		fprintf(stderr, "Renderer could not be created. SDL error: %s\n", SDL_GetError());
		return -1;
	}

	window_container->game_texture = Window_CreateTexture(window_container->renderer, screen_width / 10, screen_height / 10);
	if (!window_container->game_texture) {
		fprintf(stderr, "Game texture could not be created. SDL error: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

Window_Texture* Window_CreateTexture(SDL_Renderer* renderer, uint32_t width, uint32_t height)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!texture) {
		fprintf(stderr, "Cant create texture. SDL error: %s", SDL_GetError());
		return NULL;
	}

	SDL_PixelFormat* texture_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	Window_Texture* p_window_texture = (Window_Texture*)malloc(sizeof(Window_Texture));
	Window_Texture window_texture = { texture, texture_format, width, height };
	*p_window_texture = window_texture;

	return p_window_texture;
}

int Window_Initialize_Font() {
	if (TTF_Init() < 0) {
		fprintf(stderr, "Couldn't initialise TTF. SDL error: %s", SDL_GetError());
		return -1;
	}
	g_font = TTF_OpenFont("./fonts/Minimal5x7.ttf", 48);
	if (!g_font) {
		fprintf(stderr, "Failed to load font. SDL error: %s", SDL_GetError());
		return -1;
	}

	return 0;
}


/*
	Functional functions
*/

void Window_CopyPixels(SDL_Renderer* renderer, Window_Texture* texture, uint32_t* pixels)
{
	uint32_t* texture_pixels;
	int pitch;
	SDL_LockTexture(texture->texture, NULL, (void**)&texture_pixels, &pitch);

	memcpy(texture_pixels, pixels, texture->height * pitch);

	SDL_UnlockTexture(texture->texture);
}

void Window_RenderText(SDL_Renderer* renderer, char* text, WindowText_Options options) {
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

void Window_Container_Render(Window_Container* container)
{
	SDL_RenderClear(container->renderer);
	Window_CopyPixels(container->renderer, container->game_texture, game_pixels);
	SDL_RenderCopy(container->renderer, container->game_texture->texture, NULL, NULL);

	/*SDL_SetRenderDrawColor(container->renderer, 255, 0, 255, 255);*/
	/*WindowText_Options text_options = { 0, 0, 0, 1 };*/
	/*Window_RenderText(container->renderer, "Hello :D", text_options);*/

	SDL_RenderPresent(container->renderer);
}


/*
	Cleanup
*/

void Window_Container_Close(Window_Container* container) {
	TTF_CloseFont(g_font);
	TTF_Quit();

	SDL_DestroyTexture(container->game_texture->texture);
	SDL_DestroyRenderer(container->renderer);

	SDL_DestroyWindow(container->window);
	SDL_Quit();
	free(container);
}
