/**
 * Grid.hpp - Sudoku Grid
 */
#ifndef _SDK_GRID
#define _SDK_GRID
#include <array>
#include <string>
#include "sdk/data/Cell.hpp"
#include "sdk/data/Collection.hpp"
#include "sdk/data/Digit.hpp"

namespace sdk {
namespace data {

class Grid {
 public:
  Grid(Grid const& other);
  Grid(std::initializer_list<std::initializer_list<Digit>> const& digits);

  bool RemoveOptions(Grid const& other);
  void IntersectOptions(Grid const& other);

  View& GetRowView() { return rows_; }
  View& GetColumnView() { return columns_; }
  View& GetBoxView() { return boxes_; }

  enum class SolveResult {
    kSolved,
    kBroken,
    kNotSolved,
  };

  SolveResult IsSolved() const;
  std::string ToString() const;

 private:
  void Copy(Grid const& other);
  void InitCollections();

  std::array<Cell, 9 * 9> cells_;

  View rows_;
  View columns_;
  View boxes_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_GRID */