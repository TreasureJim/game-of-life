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

#include "camera_control.h"
#include "game.h"
#include "windows.h"

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
  // render_func = &RenderGame;
  render_func = &RenderCentreText;

  front_buffer[POS(0, 2)] = 1;
  front_buffer[POS(1, 2)] = 1;
  front_buffer[POS(2, 2)] = 1;
  front_buffer[POS(1, 0)] = 1;
  front_buffer[POS(2, 1)] = 1;
}


int main() {
  game_running = InitialiseWindow() & InitialiseText();

  Setup();

  while (game_running) {
    ProcessEvents();
    Update();
    render_func();
  }

  DestroyWindow();
}
