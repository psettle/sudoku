/**
 * sdk_Collection.hpp
 *
 * Set of digits that see each other. i.e a row, column, or box.
 */
#ifndef _SDK_COLLECTION
#define _SDK_COLLECTION
#include <array>

#include "sdk_Digit.hpp"

namespace sdk {
class Collection {
 public:
  Collection(){};
  Collection(std::array<Digit*, 9> const& digits);

  Digit& At(size_t index) { return *cells_[index]; }

 private:
  std::array<Digit*, 9> cells_;
};
}  // namespace sdk

#endif /* _SDK_COLLECTION */