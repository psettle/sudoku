/**
 * Cell.cpp
 *
 * Sudoku digit/cell
 */
#include "sdk/data/Cell.hpp"

using namespace sdk::data;

/**
 * Construct an invalid cell.
 */
Cell::Cell() : Digit(), row_(0xFF), column_(0xFF) {}

/**
 * Construct an valid cell with a position on the grid.
 */
Cell::Cell(Digit const& other, uint8_t row, uint8_t column)
    : Digit(other), row_(row), column_(column) {}

/**
 * Get the row this cell is on.
 */
uint16_t Cell::GetRow() const { return row_; }

/**
 * Get the column this cell is on.
 */
uint16_t Cell::GetColumn() const { return column_; }

/**
 * Set the value of this cell to the value of other.
 */
void Cell::Set(Digit const& other) {
  Remove(kU);
  Add(other);
}

/**
 * Get a string representing the position of the cell in the grid.
 */
std::string Cell::PositionString() const {
  return "r" + std::to_string(GetRow()) + "c" + std::to_string(GetColumn());
}