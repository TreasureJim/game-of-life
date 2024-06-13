#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "config.h"
#include "globals.h"

#include "windows.h"
#include "input_control.h"
#include "serialisation.h"

SDL_Window *window;
SDL_Renderer *renderer;

const Uint8 *keystate;

char game_running;

int InitialiseWindow() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initialising SDL.\n");
    return 0;
  }

  window =
      SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    fprintf(stderr, "Error initialising window.\n");
    return 0;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Error initialising renderer.\n");
    return 0;
  }

  return 1;
}

void DestroyWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

Uint32 last_frame_tick;
float delta_time;
void Update() {
  delta_time = (SDL_GetTicks64() - last_frame_tick) / 1000.0f;
  last_frame_tick = SDL_GetTicks64();
}

void Setup() {
  render_func = &RenderGame;
  load_pattern("glider");
}


int main() {
  game_running = InitialiseWindow() & InitialiseText();

  Setup();

  while (game_running) {
    process_events_func();
    Update();
    render_func();
  }

  DestroyWindow();
}
