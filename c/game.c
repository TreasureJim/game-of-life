#include <stdint.h>
#include <SDL2/SDL.h>
#include "window.h"

void Game_RunFrame(SDL_Renderer *renderer, Window_Texture *texture, uint32_t *pixels)
{
	static uint32_t frame_num = 0;

	for (uint32_t row = 0; row < texture->height; row++)
	{
		uint32_t color = SDL_MapRGB(texture->pixel_format, row + frame_num, 0, 0);
		for (uint32_t column = 0; column < texture->width; column++)
		{
			pixels[row * texture->width + column] = color;
		}
	}

	Window_UpdatePixels(renderer, texture, pixels);

	frame_num++;
}