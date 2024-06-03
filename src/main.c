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

#include "camera_control.h"
#include "game.h"

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

void HandleKeyDown(SDL_KeyCode keycode) {
  switch (keycode) {
  case SDLK_ESCAPE:
    game_running = 0;
    break;
  case SDLK_SPACE:
  case SDLK_n:
    step();
    break;
  case SDLK_w:
  case SDLK_a:
  case SDLK_s:
  case SDLK_d:
    // UpdatePanning(keycode);
    break;
  case SDLK_EQUALS:
    HandleZooming(1);
    break;
  case SDLK_MINUS:
    HandleZooming(0);
    break;
  default:
    break;
  }
}

void HandleKeyUp(SDL_Keycode keycode) {
  switch (keycode) {}
}

void ProcessEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      game_running = 0;
      break;
    case SDL_KEYDOWN:
      HandleKeyDown(event.key.keysym.sym);
    case SDL_KEYUP:
      HandleKeyUp(event.key.keysym.sym);
    }
  }
}

SDL_Rect rectangles[SIMULATION_HEIGHT * SIMULATION_WIDTH];
SDL_Rect borders[4];

void RenderWindow() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  Uint32 n_rects = 0;
  for (int y = 0; y < SIMULATION_HEIGHT; y++) {
    for (int x = 0; x < SIMULATION_HEIGHT; x++) {
      Uint32 pos = POS(x, y);
      if (!front_buffer[pos])
        continue;
      n_rects++;

      SDL_Rect s = {x * cell_size + camera_offset_x,
                    y * cell_size + camera_offset_y, cell_size, cell_size};
      rectangles[n_rects - 1] = s;
    }
  }
  SDL_RenderDrawRects(renderer, rectangles, n_rects);

  SDL_RenderFillRects(renderer, borders, 4);

  SDL_RenderPresent(renderer);
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

  UpdatePanning();
}

void Setup() {
  front_buffer[POS(0, 2)] = 1;
  front_buffer[POS(1, 2)] = 1;
  front_buffer[POS(2, 2)] = 1;
  front_buffer[POS(1, 0)] = 1;
  front_buffer[POS(2, 1)] = 1;

  // top
  borders[0] = (SDL_Rect){-1, -1, cell_size * SIMULATION_WIDTH, 1};
  // right
  borders[1] = (SDL_Rect){cell_size * SIMULATION_WIDTH + 1, -1, 1,
                          cell_size * SIMULATION_HEIGHT};
  // bottom
  borders[2] = (SDL_Rect){-1, cell_size * SIMULATION_WIDTH + 1,
                          cell_size * SIMULATION_WIDTH, 1};
  // left
  borders[3] = (SDL_Rect){-1, -1, 1, cell_size * SIMULATION_HEIGHT};
}

int main() {
  game_running = InitialiseWindow();

  Setup();

  while (game_running) {
    ProcessEvents();
    Update();
    RenderWindow();
  }

  DestroyWindow();
}
