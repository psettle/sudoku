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
  Cell();
  Cell(Digit const& other, uint8_t row, uint8_t column);

  uint16_t GetRow() const;
  uint16_t GetColumn() const;
  void Set(Digit const& other);
  std::string PositionString() const;

 private:
  uint8_t row_;
  uint8_t column_;
};
}  // namespace data
}  // namespace sdk
#endif /* _SDK_CELL */