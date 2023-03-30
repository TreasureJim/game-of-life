#include <SDL2/SDL.h>

#ifndef WINDOW_h_
#define WINDOW_h_

#include "input_handler.h"

typedef struct {
	SDL_Texture* texture;
	SDL_PixelFormat* pixel_format;
	uint32_t width;
	uint32_t height;
} Window_Texture;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Window_Texture* game_texture;
} Window_Container;

typedef struct WindowText_Options {
	uint16_t x;
	uint16_t y;
	uint8_t fix_right : 1;
	uint8_t fix_bottom : 1;
} WindowText_Options;

// Window Initialization funcs
int Window_Init(Window_Container** container, uint16_t screen_width, uint16_t screen_height);
int Window_Initialize_Font();
Window_Texture* Window_CreateTexture(SDL_Renderer* renderer, uint32_t width, uint32_t height);

// Window use funcs
void Window_CopyPixels(SDL_Renderer* renderer, Window_Texture* texture, uint32_t* pixels);
void Window_Container_Render(Window_Container* container);

void Window_RenderText(SDL_Renderer* renderer, char* text, WindowText_Options options);

void Texture_InvertBit(uint32_t pixel_num);

// Window cleanup 
void Window_Container_Close(Window_Container* container);

#endif
