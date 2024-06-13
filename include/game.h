#pragma once

#include "config.h"

void step();
void swap_buffers();

#define POS(x, y) y*SIMULATION_WIDTH + x
