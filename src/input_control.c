#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <string.h>

#include "camera_control.h"
#include "game.h"
#include "globals.h"
#include "input_control.h"
#include "modes.h"
#include "serialisation.h"
#include "windows.h"

void (*process_events_func)() = &ProcessGameEvents;

void ProcessEvents() { process_events_func(); }

void HandleGameKeyDown(SDL_KeyCode keycode) {
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

void ProcessGameEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      game_running = 0;
      break;
    case SDL_KEYDOWN:
      HandleGameKeyDown(event.key.keysym.sym);
      break;
    }
  }

  UpdatePanning();
}

void HandleSaveKeyDown(SDL_Keycode keysym) {
  switch (keysym) {
  case SDLK_RETURN:
    SwitchMode(MODE_GAME);
    fprintf(stderr, "TODO: saving\n");
    break;
  case SDLK_ESCAPE:
    SwitchMode(MODE_GAME);
    break;
  }
}

void AppendTextBuffer(char *text) {
  strlcat(text_buffer, text, sizeof(text_buffer));
  UpdateTextTexture();
}

void ProcessSaveEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      SwitchMode(MODE_GAME);
      break;
    case SDL_KEYDOWN:
      HandleSaveKeyDown(event.key.keysym.sym);
      break;
    case SDL_TEXTINPUT:
      AppendTextBuffer(event.text.text);
      break;
    }
  }
}

void HandleLoadKeyDown(SDL_Keycode keysym) {
  switch (keysym) {
  case SDLK_BACKSPACE:
    int len = strlen(text_buffer);
    text_buffer[len - 1] = '\0';
    UpdateTextTexture();
    break;
  case SDLK_RETURN:
    load_pattern(text_buffer);
    SwitchMode(MODE_GAME);
    break;
  case SDLK_ESCAPE:
    SwitchMode(MODE_GAME);
    break;
  }
}

void ProcessLoadEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      SwitchMode(MODE_GAME);
      break;
    case SDL_KEYDOWN:
      HandleLoadKeyDown(event.key.keysym.sym);
      break;
    case SDL_TEXTINPUT:
      AppendTextBuffer(event.text.text);
      break;
    }
  }
}
