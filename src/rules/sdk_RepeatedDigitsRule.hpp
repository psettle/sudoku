/**
 * sdk_RepeatedDigitsRule.hpp - Repeated Digits Rule
 *
 * Digits aren't allowed to repeat in a collection
 */
#ifndef _SDK_REPEATEDDIGITSRULE
#define _SDK_REPEATEDDIGITSRULE

#include <array>
#include <memory>

#include "sdk_IRule.hpp"

namespace sdk {
class RepeatedDigitsRule : public IRule {
 public:
  virtual ~RepeatedDigitsRule() {}

  RepeatedDigitsRule(std::array<Collection, 9>* view);

  /**
   * Implements IRule::Apply
   */
  bool Apply() override;

 private:
  static bool ApplyToCollection(Collection* collection);

  std::array<Collection, 9>* view_;
};
}  // namespace sdk

#endif /* _SDK_REPEATEDDIGITSRULE */