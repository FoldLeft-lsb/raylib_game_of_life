#include "entry.h"
#include <raylib.h>
#include <stdbool.h>

const int screen_width = 750;
const int screen_height = 750;
const int cell_size = 10;

const unsigned int cells_width = (screen_width / cell_size);

typedef struct Grid {
  int cells[cells_width][cells_width];
} Grid;

typedef struct Props {

  int target_fps;
} Props;

typedef struct State {
  Props props;
  Grid grid;
  bool running;
} State;

void init(State *state) {
  for (int i = 0; i < cells_width; i += 1) {
    for (int j = 0; j < cells_width; j += 1) {
      state->grid.cells[i][j] = 0;
    }
  }
}

void fill_random(State *state) {
  for (int i = 0; i < cells_width; i += 1) {
    for (int j = 0; j < cells_width; j += 1) {
      if (GetRandomValue(0, 4) == 4) {
        state->grid.cells[i][j] = 1;
      } else {
        state->grid.cells[i][j] = 0;
      }
    }
  }
}

void update(State *state) {
  for (int i = 0; i < cells_width; i += 1) {
    for (int j = 0; j < cells_width; j += 1) {
      // state->grid.cells[i][j] = 0;
    }
  }
}

void draw_cells(State *state) {
  for (int x = 0; x < cells_width; x += 1) {
    for (int y = 0; y < cells_width; y += 1) {
      Color color = (state->grid.cells[x][y]) ? (Color){0, 255, 0, 255}
                                              : (Color){55, 55, 55, 255};
      DrawRectangle(x * cell_size, (y * cell_size), cell_size - 1,
                    cell_size - 1, color);
    }
  }
}

void draw(State *state) {
  BeginDrawing();
  ClearBackground(BLACK);

  draw_cells(state);
  DrawText("Game of Life", 20, 20, 24, GREEN);

  EndDrawing();
}

int loop(void) {
  State state = {
      .running = false,
      .props =
          {
              .target_fps = 12,
          },
      .grid =
          {
              .cells = {},
          },
  };

  init(&state);

  SetTargetFPS(state.props.target_fps);
  InitWindow(screen_width, screen_height, "Game of Life");
  while (!WindowShouldClose()) {
    draw(&state);
    update(&state);
  }

  CloseWindow();
  return 0;
}