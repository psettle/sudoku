/**
 * Grid.cpp - Sudoku Grid
 */
#include "sdk/data/Grid.hpp"

using namespace sdk::data;

/**
 * Populate grid with digits
 */
Grid::Grid(std::initializer_list<std::initializer_list<Digit>> const& digits) {
  // Populate cells with values
  size_t index = 0;
  for (auto const& row : digits) {
    for (auto const& cell : row) {
      cells_[index++] = cell;
    }
  }

  // Populate row lookup table
  for (size_t row_index = 0; row_index < 9; ++row_index) {
    Collection& row = rows_[row_index];
    for (size_t row_offset = 0; row_offset < 9; ++row_offset) {
      row[row_offset] = &cells_[9 * row_index + row_offset];
    }
  }

  // Populate column lookup table
  for (size_t column_index = 0; column_index < 9; ++column_index) {
    Collection& column = columns_[column_index];
    for (size_t column_offset = 0; column_offset < 9; ++column_offset) {
      column[column_offset] = &cells_[column_index + 9 * column_offset];
    }
  }

  // Populate box lookup table
  for (size_t box_row = 0; box_row < 3; ++box_row) {
    for (size_t box_column = 0; box_column < 3; ++box_column) {
      size_t box_offset = 3 * box_column + 27 * box_row;
      Collection& box = boxes_[3 * box_column + box_row];

      for (size_t row_offset = 0; row_offset < 3; ++row_offset) {
        for (size_t column_offset = 0; column_offset < 3; ++column_offset) {
          box[3 * row_offset + column_offset] =
              &cells_[box_offset + 9 * row_offset + column_offset];
        }
      }
    }
  }
}

/**
 * Check if the puzzle is solved.
 */
bool Grid::IsSolved() const {
  // Check that each digit is solved
  for (Digit const& cell : cells_) {
    if (!cell.IsSolved()) {
      return false;
    }
  }

  // All digits solved
  return true;
}