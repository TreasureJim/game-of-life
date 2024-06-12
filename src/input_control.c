#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <string.h>

#include "camera_control.h"
#include "game.h"
#include "globals.h"
#include "input_control.h"
#include "modes.h"

void (*process_events_func)() = &ProcessGameEvents;

void ProcessEvents() { process_events_func(); }

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

  case SDLK_l:
    SwitchMode(MODE_LOAD);
    break;
  case SDLK_o:
    SwitchMode(MODE_SAVE);
    break;
  default:
    break;
  }
}

void HandleKeyUp(SDL_Keycode keycode) {
  switch (keycode) {}
}

void ProcessGameEvents() {
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

void ProcessTextEventsKeyDown(SDL_Keysym keysym) {}

char text_buffer[TEXT_BUFFER_SIZE] = "";

void ProcessTextEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN:
      ProcessTextEventsKeyDown(event.key.keysym);
      break;
    case SDL_TEXTINPUT:
      strlcat(text_buffer, event.text.text, sizeof(text_buffer));
      break;
    }
  }
}
