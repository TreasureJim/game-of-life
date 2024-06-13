#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "game.h"
#include "globals.h"

void load_pattern(char *file_name) {
  char path[200];
  sprintf(path, "./patterns/%s.gol", file_name);

  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "ERROR: couldn't read %s.\n", path);
    return;
  }

  uint16_t max_width = 0, y = 0, i = 0;

  memset(back_buffer, 0, SIMULATION_WIDTH * SIMULATION_HEIGHT);

  char c = fgetc(file);
  while (c != '\n' && c != EOF) {
    max_width++;

    if (c == '0') {
      back_buffer[i] = 0;
    } else if (c == '1') {
      back_buffer[i] = 1;
    } else {
      fprintf(stderr, "ERROR: %s has invalid symbols in it.\n", path);
      return;
    }

    i++;
    c = fgetc(file);
  }

  if (c == EOF) {
    fprintf(stderr, "ERROR: while reading %s", path);
    return;
  }

  i = POS(0, 1);
  y = 1;

  c = fgetc(file);
  while (c != EOF) {
    if (c == '\n') {
      y++;
      i = POS(0, y);
      c = fgetc(file);
      continue;
    }

    if (c == '0') {
      back_buffer[i] = 0;
    } else if (c == '1') {
      back_buffer[i] = 1;
    } else {
      fprintf(stderr, "ERROR: %s has invalid symbols in it.\n", path);
      return;
    }

    i++;
    c = fgetc(file);
  }

  swap_buffers();
}
