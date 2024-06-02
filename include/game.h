#pragma once

#define SIMULATION_HEIGHT 100
#define SIMULATION_WIDTH 100

extern char front_buffer[SIMULATION_WIDTH * SIMULATION_HEIGHT];

void step();

#define POS(x, y) y*SIMULATION_WIDTH + x
