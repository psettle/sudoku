/**
 * sdk.hpp - Sudoku Solver
 */
#ifndef _SDK
#define _SDK
#include "sdk/data/Grid.hpp"
#include "sdk/interfaces/ISolveObserver.hpp"

namespace sdk {
bool Solve(data::Grid& puzzle, interfaces::ISolveObserver* observer = nullptr);
}  // namespace sdk

#endif /* _SDK */