#pragma once
#include <vector>

class Grid {
public:
  Grid(int width, int height, int cellSize)
      : rows(height / cellSize), columns(width / cellSize), cellSize(cellSize),
        cells(rows, std::vector<int>(columns, 0)){};
  void draw();
  void set_value(int row, int column, int value);
  int get_value(int row, int column);
  int get_n_rows() { return rows; };
  int get_n_columns() { return columns; };
  void fill_random();
  void clear();
  void toggle_cell(int row, int column);

private:
  int rows;
  int columns;
  int cellSize;
  std::vector<std::vector<int>> cells;

private:
  bool is_within_bounds(int row, int column);
};
