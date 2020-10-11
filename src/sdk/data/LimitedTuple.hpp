/**
 * LimitedTuple.hpp - Limit Tuple
 *
 * A set of digits where one of them must be a specific digit
 */
#ifndef _SDK_LIMITEDTUPLE
#define _SDK_LIMITEDTUPLE

#include <vector>
#include "sdk/data/Cell.hpp"
#include "sdk/data/Digit.hpp"

namespace sdk {
namespace data {

class LimitedTuple {
 public:
  LimitedTuple(std::vector<Cell const*> selection, Digit const& digit);

  std::vector<Cell const*> const& GetSelection() const;
  Digit const& GetDigit() const;

  bool operator==(LimitedTuple const& other) const;

 private:
  std::vector<Cell const*> selection_;
  Digit digit_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLE */