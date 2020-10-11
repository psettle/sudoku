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

/**
 * A set of cells that must contain mutually exclusive values.
 */
typedef std::array<Cell*, 9> Collection;

/**
 * A set of collections that do not intersect and that cover the whole grid.
 */
typedef std::array<Collection, 9> View;

}  // namespace data
}  // namespace sdk

#endif /* _SDK_COLLECTION */