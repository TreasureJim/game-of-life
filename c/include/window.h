#include <SDL2/SDL.h>

#ifndef WINDOW_h_
#define WINDOW_h_

typedef struct WindowTexture
{
	SDL_Texture* texture;
	SDL_PixelFormat* pixel_format;
	uint32_t width;
	uint32_t height;
} Window_Texture;

int Window_Init(SDL_Window** window, uint16_t screen_width, uint16_t screen_height);

void Window_Close(SDL_Window* window);

int Window_CopyPixels(SDL_Renderer* renderer, Window_Texture* texture, uint32_t* pixels);

Window_Texture* Window_CreateTexture(SDL_Renderer* renderer, uint32_t width, uint32_t height);

typedef struct WindowText_Options {
	uint16_t x;
	uint16_t y;
	uint8_t fix_right : 1;
	uint8_t fix_bottom : 1;
} WindowText_Options;

int Window_RenderText(SDL_Renderer* renderer, char* text, WindowText_Options options);

#endif