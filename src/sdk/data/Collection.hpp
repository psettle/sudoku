/**
 * Collection.hpp
 *
 * Set of digits that see each other. i.e a row, column, or box.
 */
#ifndef _SDK_COLLECTION
#define _SDK_COLLECTION
#include <array>
#include "sdk/data/Cell.hpp"

namespace sdk {
namespace data {
typedef std::array<Cell*, 9> Collection;
typedef std::array<Collection, 9> View;

}  // namespace data
}  // namespace sdk

#endif /* _SDK_COLLECTION */