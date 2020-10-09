/**
 * sdk_IRule.hpp - Sudoku Rule Interface
 */
#ifndef _SDK_ICOLLECTIONRULE
#define _SDK_ICOLLECTIONRULE

#include "sdk/data/Collection.hpp"

namespace sdk {
namespace interfaces {
class ICollectionRule {
 public:
  virtual ~ICollectionRule() {}

  /**
   * Apply the rule to the provided collection.
   */
  virtual bool Apply(data::Collection& collection) = 0;
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_ICOLLECTIONRULE */