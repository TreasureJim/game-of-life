#include <stdint.h>
#include <SDL2/SDL.h>
#include "window.h"
#include <math.h>
#include "globals.h"

float ColorCurve(float t)
{
	return -4 * t * (t - 1);
}

void Game_RunFrame(SDL_Renderer* renderer, Window_Texture* texture, uint32_t* pixels)
{
	static uint8_t frame_num = 0;

	for (uint32_t row = 0; row < texture->height; row++)
	{
		uint32_t color = SDL_MapRGB(texture->pixel_format, frame_num, 0, 0);
		for (uint32_t column = 0; column < texture->width; column++)
		{
			pixels[row * texture->width + column] = color;
		}
	}

	Window_CopyPixels(renderer, texture, pixels);
	WindowText_Options text_options = { 0, 0, 0, 1 };
	Window_RenderText(renderer, "Hello :D", text_options);
	SDL_RenderPresent(renderer);

	frame_num++;
}