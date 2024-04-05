#ifndef CELL_H_
#define CELL_H_

#include "constants.h"
#include "game.h"

void toggle_cell(State *state, int x, int y);
void init_cell(int x, int y, State *state);
void random_cell(int x, int y, State *state);
void copy_temp_grid_cell(int x, int y, State *state);
void progress_cell_lifecycle(int x, int y, State *state);
void draw_cell(int x, int y, State *state);

#endif