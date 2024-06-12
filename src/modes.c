#include "input_control.h"
#include "windows.h"
#include <SDL2/SDL_keyboard.h>
#include <stdio.h>

typedef enum { MODE_GAME, MODE_LOAD, MODE_SAVE } Mode;

Mode current_mode = MODE_GAME;

void SwitchMode(Mode mode) {
  // exiting mode events
  switch (current_mode) {
  case MODE_LOAD:
    SDL_StopTextInput();
    fprintf(stderr, "TODO: loading");
    break;
  case MODE_SAVE:
    SDL_StopTextInput();
    fprintf(stderr, "TODO: saving");
    break;
  case MODE_GAME:
    break;
  }

  current_mode = mode;

  switch (mode) {
  case MODE_GAME:
    render_func = &RenderGame;
    process_events_func = &ProcessGameEvents;
    break;
  case MODE_LOAD:
  case MODE_SAVE:
    SDL_StartTextInput();
    render_func = &RenderCentreText;
    process_events_func = &ProcessTextEvents;
    break;
  }
}
