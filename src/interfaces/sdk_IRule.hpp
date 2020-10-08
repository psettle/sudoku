/**
 * sdk_IRule.hpp - Sudoku Rule Interface
 */
#ifndef _SDK_IRULE
#define _SDK_IRULE

#include "sdk_Grid.hpp"

namespace sdk {
class IRule {
 public:
  virtual ~IRule() {}

  /**
   * Apply the rule to the provided puzzle, return true if progress was made.
   */
  virtual bool Apply() = 0;
};
}  // namespace sdk

#endif /* _SDK_IRULE */