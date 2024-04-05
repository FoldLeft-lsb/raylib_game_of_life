#include "game.h"
#include "cell.h"
#include "constants.h"

#include <raylib.h>

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
