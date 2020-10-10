/**
 * ISolveObserver.hpp - Sudoku Solve Observer
 */
#ifndef _SDK_ISOLVEOBSERVER
#define _SDK_ISOLVEOBSERVER

#include "sdk/interfaces/IAlignedLimitedTupleListener.hpp"
#include "sdk/interfaces/IExclusiveTupleListener.hpp"
#include "sdk/interfaces/ILimitedTupleObserver.hpp"

namespace sdk {
namespace interfaces {
class ISolveObserver : public IExclusiveTupleListener,
                       public ILimitedTupleObserver,
                       public IAlignedLimitedTupleListener {
 public:
  virtual ~ISolveObserver() {}
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_ISOLVEOBSERVER */