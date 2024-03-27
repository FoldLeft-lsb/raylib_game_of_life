
#include "entry.hpp"
#include "simulation.hpp"
#include <iostream>
#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

const int screenWidth = 750;
const int screenHeight = 750;
const int cellSize = 10;
int target_fps = 12;

Simulation simulation{screenWidth, screenHeight, cellSize};

void update_draw_frame() {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mousePos = GetMousePosition();
    simulation.toggle_cell(mousePos.y / cellSize, mousePos.x / cellSize);
  };

  if (IsKeyPressed(KEY_SPACE)) {
    if (simulation.is_running()) {
      simulation.stop();
    } else {
      simulation.start();
    }
  } else if (IsKeyPressed(KEY_RIGHT_BRACKET)) {
    target_fps += 2;
    SetTargetFPS(target_fps);
  } else if (IsKeyPressed(KEY_LEFT_BRACKET)) {
    if (target_fps > 5) {
      target_fps -= 2;
      SetTargetFPS(target_fps);
    }
  } else if (IsKeyPressed(KEY_R)) {
    simulation.create_random_state();
  } else if (IsKeyPressed(KEY_C)) {
    simulation.clear_grid();
  };

  simulation.update();

  BeginDrawing();
  ClearBackground(BLACK);
  simulation.draw();
  EndDrawing();
};

int loop() {

  SetTargetFPS(target_fps);
  InitWindow(screenWidth, screenHeight, "Game of Life");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(update_draw_frame, 0, 1);
#else
  std::cout << "Failed to load Platform correctly" << std::endl;
#endif

  CloseWindow();

  return 0;
};
