/**
 * Grid.hpp - Sudoku Grid
 */
#ifndef _SDK_GRID
#define _SDK_GRID
#include <array>
#include <sstream>
#include <string>

#include "sdk/data/Collection.hpp"
#include "sdk/data/Digit.hpp"

namespace sdk {
namespace data {

class Grid {
 public:
  Grid(std::initializer_list<std::initializer_list<Digit>> const& digits);

  std::array<Collection, 9>& GetRowView() { return rows_; }
  std::array<Collection, 9>& GetColumnView() { return columns_; }
  std::array<Collection, 9>& GetBoxView() { return boxes_; }

  bool IsSolved() const;
  std::string ToString() const {
    std::ostringstream str;
    for (size_t i = 0; i < 9; ++i) {
      for (size_t j = 0; j < 9; ++j) {
        str << '\t' << cells_[9 * i + j].ToString();
      }
      str << std::endl;
    }
    str << std::endl;
    return str.str();
  }

 private:
  std::array<Digit, 9 * 9> cells_;

  std::array<Collection, 9> rows_;
  std::array<Collection, 9> columns_;
  std::array<Collection, 9> boxes_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_GRID */