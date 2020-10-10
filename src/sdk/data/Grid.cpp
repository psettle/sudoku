/**
 * Grid.cpp - Sudoku Grid
 */
#include "sdk/data/Grid.hpp"

using namespace sdk::data;

Grid::Grid(Grid const& other) {
  Copy(other);
  InitCollections();
}

/**
 * Populate grid with digits
 */
Grid::Grid(std::initializer_list<std::initializer_list<Digit>> const& digits) {
  // Populate cells with values
  size_t index = 0;
  auto row_iterator = digits.begin();
  for (size_t row_index = 0; row_index < 9; ++row_index, ++row_iterator) {
    auto column_iterator = (*row_iterator).begin();
    for (size_t column_index = 0; column_index < 9; ++column_index, ++column_iterator) {
      cells_[index++] = Cell(*column_iterator, row_index, column_index);
    }
  }

  InitCollections();
}

/**
 * Copy all cell values from other.
 */
void Grid::Copy(Grid const& other) {
  for (size_t i = 0; i < cells_.size(); ++i) {
    cells_[i].Set(other.cells_[i]);
  }
}

/**
 * Remove all options from other from ourselves
 */
bool Grid::RemoveOptions(Grid const& other) {
  bool progress = false;
  for (size_t i = 0; i < cells_.size(); ++i) {
    progress |= cells_[i].Remove(other.cells_[i]);
  }
  return progress;
}

/**
 * Remove all options not in other
 */
void Grid::IntersectOptions(Grid const& other) {
  for (size_t i = 0; i < cells_.size(); ++i) {
    cells_[i].Intersect(other.cells_[i]);
  }
}

/**
 * Check if the puzzle is solved.
 */
Grid::SolveResult Grid::IsSolved() const {
  // Check that each digit is solved
  bool found_unsolved = false;
  for (Digit const& cell : cells_) {
    if (0 == cell.PossibleValues()) {
      // No values left so this grid is broken
      return SolveResult::kBroken;
    }

    if (!cell.IsSolved()) {
      found_unsolved = true;
    }
  }

  if (found_unsolved) {
    return SolveResult::kNotSolved;
  } else {
    // All digits solved
    return SolveResult::kSolved;
  }
}

void Grid::InitCollections() {
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