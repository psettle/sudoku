/**
 * RepeatedDigitsRule.hpp - Repeated Digits Rule
 *
 * Digits aren't allowed to repeat in a collection
 */
#ifndef _SDK_REPEATEDDIGITSRULE
#define _SDK_REPEATEDDIGITSRULE

#include "sdk/interfaces/ICollectionRule.hpp"

namespace sdk {
namespace rules {
class RepeatedDigitsRule : public interfaces::ICollectionRule {
 public:
  virtual ~RepeatedDigitsRule() {}

  /**
   * Implements ICollectionRule::Apply
   */
  bool Apply(data::Collection& collection) override;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_REPEATEDDIGITSRULE */