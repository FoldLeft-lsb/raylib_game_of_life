#include "game.h"
#include "constants.h"

#include <raylib.h>

static bool is_in_bounds(int x, int y) {
  return x >= 0 && x < CELLS_WIDTH && y >= 0 && y < CELLS_WIDTH;
}

static void toggle_cell(State *state, int x, int y) {
  if (is_in_bounds(x, y)) {
    int cell = state->grid.cells[x][y];
    state->grid.cells[x][y] = (cell == 1) ? 0 : 1;
  }
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

static void init_cell(int x, int y, State *state) {
  state->grid.cells[x][y] = 0;
}

static void random_cell(int x, int y, State *state) {
  if (GetRandomValue(0, 4) == 4) {
    state->grid.cells[x][y] = 1;
  } else {
    state->grid.cells[x][y] = 0;
  }
}

static void copy_temp_grid_cell(int x, int y, State *state) {
  state->grid.cells[x][y] = state->grid.temp_cells[x][y];
}

static void progress_cell_lifecycle(int x, int y, State *state) {
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

static void draw_cell(int x, int y, State *state) {
  Color color = (state->grid.cells[x][y]) ? (Color){0, 255, 0, 255}
                                          : (Color){55, 55, 55, 255};
  DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1,
                color);
}

static grid_update *init_cell_p = init_cell;
static grid_update *random_cell_p = random_cell;
static grid_update *copy_temp_grid_cell_p = copy_temp_grid_cell;
static grid_update *progress_cell_lifecycle_p = progress_cell_lifecycle;
static grid_update *draw_cell_p = draw_cell;

static void traverse_grid(State *state, grid_update *update) {
  for (int x = 0; x < CELLS_WIDTH; x++) {
    for (int y = 0; y < CELLS_WIDTH; y++) {
      (update)(x, y, state);
    }
  }
}

static void draw_cells(State *state) { traverse_grid(state, draw_cell_p); }
static void fill_random(State *state) { traverse_grid(state, random_cell_p); }

void init_cells(State *state) { traverse_grid(state, init_cell_p); }

void update_grid(State *state) {
  traverse_grid(state, progress_cell_lifecycle_p);
  traverse_grid(state, copy_temp_grid_cell_p);
}

void draw(State *state) {
  BeginDrawing();
  ClearBackground(BLACK);

  draw_cells(state);

  EndDrawing();
}

void collect_inputs(State *state) {
  if (state->running) {
    if (IsKeyPressed(KEY_SPACE))
      state->running = false;
  } else {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 mousePos = GetMousePosition();
      toggle_cell(state, mousePos.x / CELL_SIZE, mousePos.y / CELL_SIZE);
    }

    if (IsKeyPressed(KEY_R))
      fill_random(state);
    if (IsKeyPressed(KEY_C))
      init_cells(state);
    if (IsKeyPressed(KEY_SPACE))
      state->running = true;
  }

  if (IsKeyPressed(KEY_LEFT_BRACKET)) {
    if (state->props.target_fps > 5) {
      state->props.target_fps -= 2;
      SetTargetFPS(state->props.target_fps);
    }
  }
  if (IsKeyPressed(KEY_RIGHT_BRACKET)) {
    state->props.target_fps += 2;
    SetTargetFPS(state->props.target_fps);
  }
}
