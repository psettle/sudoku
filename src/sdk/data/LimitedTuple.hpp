/**
 * LimitedTuple.hpp - Limit Tuple
 *
 * A set of digits where one of them must be a specific digit
 */
#ifndef _SDK_LIMITEDTUPLE
#define _SDK_LIMITEDTUPLE

#include <set>
#include <vector>
#include "sdk/data/Cell.hpp"
#include "sdk/data/Digit.hpp"

namespace sdk {
namespace data {

class LimitedTuple {
 public:
  LimitedTuple(std::vector<Cell*> selection, Digit const& digit)
      : selection_(selection), digit_(digit) {}

  std::vector<Cell*> const& GetSelection() const { return selection_; }
  Digit const& GetDigit() const { return digit_; }

  bool operator==(LimitedTuple const& other) const {
    // Check that order and digit match
    if (digit_ != other.digit_) {
      return false;
    }

    if (selection_.size() != other.selection_.size()) {
      return false;
    }

    // Now we need to check if these sets reference all the same digits
    std::set<Digit*> temp;

    for (Digit* digit : other.selection_) {
      temp.emplace(digit);
    }

    for (Digit* digit : selection_) {
      temp.erase(digit);
    }

    // If temp is empty the tuples contained the same elements
    return temp.size() == 0;
  }

 private:
  std::vector<Cell*> selection_;
  Digit const& digit_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLE */