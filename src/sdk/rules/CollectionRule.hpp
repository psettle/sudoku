/**
 * CollectionRule.hpp - Collection Rule
 *
 * Rule that applies to a collection
 */
#ifndef _SDK_COLLECTIONRULE
#define _SDK_COLLECTIONRULE

#include <array>
#include <memory>
#include <vector>

#include "sdk/data/Collection.hpp"
#include "sdk/interfaces/ICollectionRule.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
namespace rules {
class CollectionRule : public interfaces::IRule {
 public:
  virtual ~CollectionRule() {}

  CollectionRule(std::array<data::Collection, 9>& view);
  void AddRule(interfaces::ICollectionRule* rule) {
    rules_.push_back(std::unique_ptr<interfaces::ICollectionRule>(rule));
  }

  /**
   * Implements IRule::Apply
   */
  bool Apply() override;

 private:
  std::array<data::Collection, 9>& view_;
  std::vector<std::unique_ptr<interfaces::ICollectionRule>> rules_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_COLLECTIONRULE */