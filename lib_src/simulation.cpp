#include "simulation.hpp"
#include <utility>
#include <vector>

void Simulation::draw() { grid.draw(); };

int Simulation::count_live_neighbors(int row, int column) {
  int liveNeighbors = 0;
  std::vector<std::pair<int, int>> neighborOffsets = {
      {-1, 0},  // above
      {1, 0},   // below
      {0, -1},  // left
      {0, 1},   // right
      {-1, -1}, // up left
      {-1, 1},  // up right
      {1, -1},  // down left
      {1, 1},   // down right
  };
  for (const auto &offset : neighborOffsets) {
    int neighborRow =
        (row + offset.first + grid.get_n_rows()) % grid.get_n_rows();
    int neighborColumn =
        (column + offset.second + grid.get_n_columns()) % grid.get_n_columns();
    liveNeighbors += grid.get_value(neighborRow, neighborColumn);
  }
  return liveNeighbors;
};

void Simulation::update() {
  if (is_running()) {
    for (int row = 0; row < grid.get_n_rows(); row++) {
      for (int column = 0; column < grid.get_n_columns(); column++) {
        int liveNeighbors = count_live_neighbors(row, column);
        int cellValue = grid.get_value(row, column);
        if (cellValue == 1) {
          if (liveNeighbors > 3 || liveNeighbors < 2) {
            tempGrid.set_value(row, column, 0);
          } else {
            tempGrid.set_value(row, column, 1);
          }
        } else {
          if (liveNeighbors == 3) {
            tempGrid.set_value(row, column, 1);
          } else {
            tempGrid.set_value(row, column, 0);
          }
        }
      }
    }
    grid = tempGrid;
  }
};

void Simulation::clear_grid() {
  if (!is_running()) {
    grid.clear();
  }
};

void Simulation::create_random_state() {
  if (!is_running()) {
    grid.fill_random();
  }
};

void Simulation::toggle_cell(int row, int column) {
  if (!is_running()) {
    grid.toggle_cell(row, column);
  }
};