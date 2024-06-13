#include "game.h"
#include <SDL2/SDL_stdinc.h>

char front_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT] = {0};
char back_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT] = {0};

#define mod(x, N) (x % N + N) % N

char count_neighbours(Uint16 x, Uint16 y) {
  char count = 0;

  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (dy == 0 && dx == 0)
        continue;

      Uint32 pos = mod(y + dy, SIMULATION_HEIGHT) * SIMULATION_WIDTH +
                   mod(x + dx, SIMULATION_WIDTH);
      if (front_buffer[pos])
        count++;
    }
  }

  return count;
}

void swap_buffers() {
  memcpy(front_buffer, back_buffer, sizeof(back_buffer));
}

void step() {
  for (int y = 0; y < SIMULATION_HEIGHT; y++) {
    for (int x = 0; x < SIMULATION_HEIGHT; x++) {
      Uint32 pos = y * SIMULATION_WIDTH + x;

      char n = count_neighbours(x, y);
      if (n < 2) {
        // underpopulation
        back_buffer[pos] = 0;
      } else if (n == 2) {
        // stays alive
        back_buffer[pos] = front_buffer[pos];
      } else if (n == 3) {
        // reproduction
        back_buffer[pos] = 1;
      } else if (n > 3) {
        // overpopulation
        back_buffer[pos] = 0;
      }
    }
  }

  swap_buffers();
}
