/**
 * sdk_IRule.hpp - Sudoku Rule Interface
 */
#ifndef _SDK_IRULE
#define _SDK_IRULE

namespace sdk {
namespace interfaces {
class IRule {
 public:
  virtual ~IRule() {}

  /**
   * Apply the rule to the provided puzzle, return true if progress was made.
   */
  virtual bool Apply() = 0;
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_IRULE */