/**
 * UniqueSpotRule.hpp - Unique Spot Rule
 *
 * If there is only one place left for a digit in a collection,
 * it must go there.
 */
#ifndef _SDK_UNIQUESPOTRULE
#define _SDK_UNIQUESPOTRULE

#include "sdk/interfaces/ICollectionRule.hpp"

namespace sdk {
namespace rules {
class UniqueSpotRule : public interfaces::ICollectionRule {
 public:
  virtual ~UniqueSpotRule() {}

  /**
   * Implements ICollectionRule::Apply
   */
  bool Apply(data::Collection& collection) override;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_UNIQUESPOTRULE */