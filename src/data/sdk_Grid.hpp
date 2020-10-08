/**
 * sdk_Grid.hpp - Sudoku Grid
 */
#ifndef _SDK_GRID
#define _SDK_GRID
#include <array>

#include "sdk_Collection.hpp"
#include "sdk_Digit.hpp"

namespace sdk {
class Grid {
 public:
  Grid(std::initializer_list<std::initializer_list<Digit>> const& digits);

  std::array<Collection, 9>& GetRowView() { return rows_; }
  std::array<Collection, 9>& GetColumnView() { return columns_; }
  std::array<Collection, 9>& GetBoxView() { return boxes_; }

  bool IsSolved() const;

 private:
  std::array<Digit, 9 * 9> cells_;

  std::array<Collection, 9> rows_;
  std::array<Collection, 9> columns_;
  std::array<Collection, 9> boxes_;
};
}  // namespace sdk

#endif /* _SDK_GRID */