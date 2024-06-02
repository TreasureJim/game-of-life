# Conway's Game of Life

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It's a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. This program simulates the Game of Life on a 2D grid, visualized using the SDL2 library.

## Features

- Simple and clean implementation in pure C.
- Graphical display using SDL2.
- Configurable grid size and initial configuration.
- Real-time simulation of the Game of Life rules.

## Requirements

To compile and run this program, you will need:

- A C compiler (GCC recommended)
- SDL2 library installed on your system

## Installation

```sh
git clone https://github.com/treasurejim/game-of-life.git
cd game-of-life
make
```

## Usage

After compilation, you can run the program using:

```sh
make run
```

## Configuration

You can configure the simulation parameters by editing the `config.h` file. Key parameters include:

- `SIMULATION_WIDTH` and `SIMULATION_HEIGHT` to set the size of the grid.
- `CELL_SIZE` to adjust the size of each cell on the screen in pixels.

---

Thank you for checking out this implementation of Conway's Game of Life in C using SDL2. Enjoy coding and happy simulating!
