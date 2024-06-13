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

char text_buffer[100] = "";

TTF_Font *font;
SDL_Color font_color = {255, 255, 255};
SDL_Surface* input_text_surface;
SDL_Texture* input_text_texture;
SDL_Rect input_text_rect = {0, WINDOW_HEIGHT/2 - 49/2, 300, 100};

SDL_Surface*  file_text_surface;
SDL_Texture*  file_text_texture;
SDL_Rect      file_text_rect = {0, WINDOW_HEIGHT/2 - 49/2 - 49, 300, 100};

char InitialiseText() {
  if (TTF_Init()) {
    fprintf(stderr, "Error initialising TTF. \n");
    return 0;
  }

  font = TTF_OpenFont("assets/fonts/" FONT_FILE_NAME, 48);
  input_text_surface = TTF_RenderText_Solid(font, text_buffer, font_color);
  input_text_texture = SDL_CreateTextureFromSurface(renderer, input_text_surface);

  #define FILE_TEXT "FILE NAME:"
  file_text_surface = TTF_RenderText_Solid(font, FILE_TEXT, font_color);
  file_text_texture = SDL_CreateTextureFromSurface(renderer, file_text_surface);
  TTF_SizeText(font, FILE_TEXT, &file_text_rect.w, &file_text_rect.h);

  input_text_rect.y = WINDOW_HEIGHT/2 - file_text_rect.h / 2;
  file_text_rect.y = input_text_rect.y - file_text_rect.h;

  return 1;
}

void UpdateTextTexture() {
  input_text_surface = TTF_RenderText_Solid(font, text_buffer, font_color);
  input_text_texture = SDL_CreateTextureFromSurface(renderer, input_text_surface);

  TTF_SizeText(font, text_buffer, &input_text_rect.w, &input_text_rect.h);
}

void RenderCentreText() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, file_text_texture, NULL, &file_text_rect);
  SDL_RenderCopy(renderer, input_text_texture, NULL, &input_text_rect);

  SDL_RenderPresent(renderer);
}
