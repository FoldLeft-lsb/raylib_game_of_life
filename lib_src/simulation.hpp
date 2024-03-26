#pragma once
#include "grid.hpp"

class Simulation {
public:
  Simulation(int width, int height, int cellSize)
      : grid(width, height, cellSize), tempGrid(width, height, cellSize),
        run(false){};
  void draw();
  void update();
  void start() { run = true; };
  void stop() { run = false; };
  void clear_grid();
  void create_random_state();
  void toggle_cell(int row, int column);
  bool is_running() { return run; };

private:
  Grid grid;
  Grid tempGrid;
  bool run;

private:
  int count_live_neighbors(int row, int column);
};