#include "cell.h"
#include "constants.h"
#include "game.h"
#include <raylib.h>
#include <stdbool.h>

static bool is_in_bounds(int x, int y) {
  return x >= 0 && x < CELLS_WIDTH && y >= 0 && y < CELLS_WIDTH;
}

static int count_live_neighbors(State *state, int x, int y) {
  int neighbors = 0;
  for (int offset_x = -1; offset_x <= 1; offset_x++) {
    for (int offset_y = -1; offset_y <= 1; offset_y++) {
      int neighbor_x = (x + offset_x + CELLS_WIDTH) % CELLS_WIDTH;
      int neighbor_y = (y + offset_y + CELLS_WIDTH) % CELLS_WIDTH;
      if (!(x == neighbor_x && y == neighbor_y) &&
          is_in_bounds(neighbor_x, neighbor_y)) {
        neighbors += state->grid.cells[neighbor_x][neighbor_y];
      }
    }
  }
  return neighbors;
}

void toggle_cell(State *state, int x, int y) {
  if (is_in_bounds(x, y)) {
    int cell = state->grid.cells[x][y];
    state->grid.cells[x][y] = (cell == 1) ? 0 : 1;
  }
}

void init_cell(int x, int y, State *state) { state->grid.cells[x][y] = 0; }

void random_cell(int x, int y, State *state) {
  if (GetRandomValue(0, 4) == 4) {
    state->grid.cells[x][y] = 1;
  } else {
    state->grid.cells[x][y] = 0;
  }
}

void copy_temp_grid_cell(int x, int y, State *state) {
  state->grid.cells[x][y] = state->grid.temp_cells[x][y];
}

void progress_cell_lifecycle(int x, int y, State *state) {
  int neighbors = count_live_neighbors(state, x, y);
  if (state->grid.cells[x][y] == 1) {

    if (neighbors > 3 || neighbors < 2) {
      state->grid.temp_cells[x][y] = 0;
    } else {
      state->grid.temp_cells[x][y] = 1;
    }
  } else {
    if (neighbors == 3) {
      state->grid.temp_cells[x][y] = 1;
    } else {
      state->grid.temp_cells[x][y] = 0;
    }
  }
}

void draw_cell(int x, int y, State *state) {
  Color color = (state->grid.cells[x][y]) ? (Color){0, 255, 0, 255}
                                          : (Color){55, 55, 55, 255};
  DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1,
                color);
}
