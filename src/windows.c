#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "camera_control.h"
#include "config.h"
#include "game.h"
#include "globals.h"

SDL_Rect rectangles[SIMULATION_HEIGHT * SIMULATION_WIDTH];
SDL_Rect borders[4];

void (*render_func)();

void RenderGame() {
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

TTF_Font *font;
SDL_Color font_color = {255, 255, 255};
SDL_Surface* text_surface;
SDL_Texture* text_texture;
SDL_Rect text_rect = {0, 0, 300, 100};

char InitialiseText() {
  if (TTF_Init()) {
    fprintf(stderr, "Error initialising TTF. \n");
    return 0;
  }

  font = TTF_OpenFont("assets/fonts/arcadeclassic.ttf", 48);
  text_surface = TTF_RenderText_Solid(font, "aaaaahhhhh", font_color);
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

  return 1;
}

char centre_text[100] = {0};
void RenderCentreText() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

  SDL_RenderPresent(renderer);
}
