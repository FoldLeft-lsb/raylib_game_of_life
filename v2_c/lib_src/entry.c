#include <raylib.h>

typedef struct State {
  int screen_width;
  int screen_height;
  int cell_size;
  int target_fps;
} State;

void setup(State *state) {

  state->screen_width = 750;
  state->screen_height = 750;
  state->cell_size = 10;
  state->target_fps = 12;

  SetTargetFPS(state->target_fps);
  InitWindow(state->screen_width, state->screen_height, "Game of Life");
}

void update(State *state) {}

void draw(State *state) {
  BeginDrawing();
  ClearBackground(BLACK);

  DrawText("Game of Life", 20, 20, 24, GREEN);

  EndDrawing();
}

int loop(void) {
  State state;
  setup(&state);

  while (!WindowShouldClose()) {
    draw(&state);
    update(&state);
  }

  CloseWindow();
  return 0;
}