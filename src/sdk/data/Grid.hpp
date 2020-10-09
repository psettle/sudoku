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

  View& GetRowView() { return rows_; }
  View& GetColumnView() { return columns_; }
  View& GetBoxView() { return boxes_; }

  bool IsSolved() const;
  std::string ToString() const {
    std::ostringstream str;
    char ws = IsSolved() ? ' ' : '\t';
    for (size_t i = 0; i < 9; ++i) {
      for (size_t j = 0; j < 9; ++j) {
        str << ws << cells_[9 * i + j].ToString();
      }
      str << std::endl;
    }
    str << std::endl;
    return str.str();
  }

 private:
  std::array<Digit, 9 * 9> cells_;

  View rows_;
  View columns_;
  View boxes_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_GRID */