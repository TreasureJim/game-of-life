#pragma once

#include "config.h"

extern char front_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT];

void step();

#define POS(x, y) y*SIMULATION_WIDTH + x
