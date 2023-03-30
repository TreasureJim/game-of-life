#include <stdint.h>
#include <SDL2/SDL.h>
#include "window.h"
#include <math.h>
#include "globals.h"
#include <pthread.h>
#include <unistd.h>

void Game_NextStep() {
	// TODO
}

void* FixedUpdate() {
	uint8_t on = 0;
	while (1) {
		pthread_mutex_lock(&m_game_running);
		pthread_mutex_unlock(&m_game_running);
		usleep(1000000);

		Game_NextStep();
	}
}

void Texture_InvertBit(uint32_t pixel_num)
{
	if (game_pixels[pixel_num] == 0xFFFFFFFF) {
		game_pixels[pixel_num] = 0x000000FF;
	}
	else {
		game_pixels[pixel_num] = 0xFFFFFFFF;
	}
}

/**
	@param x x pos of cursor
	@param y y pos of cursor
	@return the pixel index or if not in window then -1
**/
uint32_t MousePosToPixel(Window_Container* container, int x, int y) {
	if (x < 0 || y < 0) return -1;

	uint16_t pixel_width = SCREEN_WIDTH / container->game_texture->width, pixel_height = SCREEN_HEIGHT / container->game_texture->height;
	uint16_t pixel_x = x / pixel_width, pixel_y = y / pixel_height;
	return pixel_y * container->game_texture->width + pixel_x;
}

static uint32_t last_pixel;
void Game_HandleClick(int x, int y) {
	static uint32_t pixel_index;
	pixel_index = MousePosToPixel(window_container, x, y);
	if (pixel_index < 0 || pixel_index == last_pixel) {
		return;
	}

	last_pixel = pixel_index;
	Texture_InvertBit(pixel_index);
}
