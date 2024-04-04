#include "entry.h"
#include "constants.h"
#include "game.h"

#include <raylib.h>

int loop(void) {
  State state = {
      .running = false,
      .props =
          {
              .target_fps = 12,
          },
  };

  init_cells(&state);

  SetTargetFPS(state.props.target_fps);
  InitWindow(WIDTH, HEIGHT, "Game of Life");

  while (!WindowShouldClose()) {

    draw(&state);

    collect_inputs(&state);
    if (state.running)
      update_grid(&state);
  }

  CloseWindow();
  return 0;
}