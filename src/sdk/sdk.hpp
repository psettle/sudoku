/**
 * sdk.hpp - Sudoku Solver
 */
#ifndef _SDK
#define _SDK
#include "sdk/data/Grid.hpp"

namespace sdk {
bool Solve(data::Grid& puzzle);
}  // namespace sdk

#endif /* _SDK */