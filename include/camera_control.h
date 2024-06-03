#pragma once

#include <SDL2/SDL_keycode.h>

// void UpdatePanning(SDL_Keycode keycode);
void UpdatePanning(void);
extern float camera_offset_x;
extern float camera_offset_y;

void HandleZooming(char zoom_in);
extern Uint8 cell_size;
