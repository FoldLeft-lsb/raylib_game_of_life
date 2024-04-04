#ifndef GAME_H_
#define GAME_H_

#include "constants.h"
#include <stdbool.h>

typedef struct Grid {
  int cells[CELLS_WIDTH][CELLS_WIDTH];
  int temp_cells[CELLS_WIDTH][CELLS_WIDTH];
} Grid;

typedef struct Props {
  int target_fps;
} Props;

typedef struct State {
  Props props;
  Grid grid;
  bool running;
} State;

void init_cells(State *state);
void update_grid(State *state);
void draw(State *state);
void collect_inputs(State *state);

#endif