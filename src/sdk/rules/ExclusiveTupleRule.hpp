/**
 * ExclusiveTupleRule.hpp - Exclusive Tuple Rule
 *
 * If N cells consist of N possible digits, those digits cannot exist
 * in any other cells
 */
#ifndef _SDK_EXCLUSIVETUPLERULE
#define _SDK_EXCLUSIVETUPLERULE

#include "sdk/interfaces/ICollectionRule.hpp"

namespace sdk {
namespace rules {
class ExclusiveTupleRule : public interfaces::ICollectionRule {
 public:
  virtual ~ExclusiveTupleRule() {}

  ExclusiveTupleRule(uint8_t order) : order_(order) {}

  /**
   * Implements ICollectionRule::Apply
   */
  bool Apply(data::Collection& collection) override;

 private:
  uint8_t order_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_EXCLUSIVETUPLERULE */