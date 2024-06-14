# Conway's Game of Life

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It's a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. This program simulates the Game of Life on a 2D grid, visualized using the SDL2 library.

## Features

- Simple and clean implementation in pure C.
- Graphical display using SDL2.
- Configurable grid size and initial configuration.
- Real-time simulation of the Game of Life rules.

## Controls

    Panning:
        WASD keys to pan the view.

    Zooming:
        `+` to zoom in.
        `-` to zoom out.

    Simulation:
        `Space` or `N` to step to the next generation manually.

    Loading patterns:
        `l` to load a pattern from `patterns/`

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
- `FONT_FILE_NAME` - change the font loaded in `/assets/fonts/`
- `WINDOW_HEIGHT` and `WINDOW_WIDTH` - changes the window size
- `CAMERA_SPEED` - how fast the camera pans
- `ZOOM_SPEED` - how fast the camera zooms
- `FRAME_MAX` - the frame rate cap

---

Thank you for checking out this implementation of Conway's Game of Life. Enjoy coding and happy simulating!
