/**
 * sdk.hpp - Sudoku Solver
 */
#ifndef _SDK
#define _SDK
#include "sdk/data/Grid.hpp"
#include "sdk/interfaces/ISolveObserver.hpp"

namespace sdk {
// private
data::Grid::SolveResult Solve(data::Grid& puzzle, interfaces::ISolveObserver* observer = nullptr,
                              uint8_t bisect_order = 2, uint32_t bisect_depth = 1);
}  // namespace sdk

#endif /* _SDK */