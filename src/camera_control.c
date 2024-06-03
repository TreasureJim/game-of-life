#include "camera_control.h"
#include "config.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>

float camera_offset_x = 0;
float camera_offset_y = 0;

Uint8 cell_size = 20;

extern float delta_time;

void UpdatePanning(void) {
  const Uint8* keystate = SDL_GetKeyboardState(NULL);

  if (keystate[SDL_SCANCODE_W])
    camera_offset_y -= CAMERA_SPEED * delta_time;
  if (keystate[SDL_SCANCODE_A])
    camera_offset_x -= CAMERA_SPEED * delta_time;
  if (keystate[SDL_SCANCODE_S])
    camera_offset_y += CAMERA_SPEED * delta_time;
  if (keystate[SDL_SCANCODE_D])
    camera_offset_x += CAMERA_SPEED * delta_time;
}

void HandleZooming(char zoom_in) {
  if (zoom_in) {
    cell_size += ZOOM_SPEED;
  } else {
    cell_size -= ZOOM_SPEED;
  }
}
