/**
 * Collection.hpp
 *
 * Set of digits that see each other. i.e a row, column, or box.
 */
#ifndef _SDK_COLLECTION
#define _SDK_COLLECTION
#include <array>

#include "sdk/data/Digit.hpp"

namespace sdk {
namespace data {
typedef std::array<Digit*, 9> Collection;

}  // namespace data
}  // namespace sdk

#endif /* _SDK_COLLECTION */