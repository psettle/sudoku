/**
 * Cell.hpp - Sudoku Cell
 */
#ifndef _SDK_CELL
#define _SDK_CELL

#include <stdint.h>
#include "sdk/data/Digit.hpp"

namespace sdk {
namespace data {
class Cell : public Digit {
 public:
  Cell() : Digit(), row_(0xFF), column_(0xFF) {}
  Cell(Digit const& other, uint8_t row, uint8_t column)
      : Digit(other), row_(row), column_(column) {}

  uint16_t GetRow() const { return row_; }
  uint16_t GetColumn() const { return column_; }

  void Set(Digit const& other) {
    Remove(kU);
    Add(other);
  }

  std::string PositionString() const {
    return "r" + std::to_string(GetRow()) + "c" + std::to_string(GetColumn());
  }

 private:
  uint8_t row_;
  uint8_t column_;
};
}  // namespace data
}  // namespace sdk
#endif /* _SDK_CELL */