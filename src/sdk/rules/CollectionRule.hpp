/**
 * CollectionRule.hpp - Collection Rule
 *
 * Rule that applies to a collection
 */
#ifndef _SDK_COLLECTIONRULE
#define _SDK_COLLECTIONRULE

#include <memory>
#include <vector>
#include "sdk/data/Grid.hpp"
#include "sdk/interfaces/ICollectionRule.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
namespace rules {
class CollectionRule : public interfaces::IRule {
 public:
  virtual ~CollectionRule() {}
  CollectionRule(data::Grid* puzzle, interfaces::ICollectionRule* rule);
  bool Apply() override;

 private:
  data::Grid* puzzle_;
  std::unique_ptr<interfaces::ICollectionRule> rule_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_COLLECTIONRULE */