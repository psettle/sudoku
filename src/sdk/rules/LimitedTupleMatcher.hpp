/**
 * LimitedTupleMatcher.hpp - Limited Tuple Matcher
 *
 * Use limited tuples that have already been found to
 * eliminate possible values from collections.
 */
#ifndef _SDK_LIMITEDTUPLEMATCHER
#define _SDK_LIMITEDTUPLEMATCHER

#include <vector>
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/ICollectionRule.hpp"

namespace sdk {
namespace rules {
class LimitedTupleMatcher : public interfaces::ICollectionRule {
 public:
  virtual ~LimitedTupleMatcher() {}
  LimitedTupleMatcher(data::LimitedTupleDatabase& database) : database_(database) {}

  /**
   * Implements ICollectionRule::Apply
   */
  bool Apply(data::Collection& collection) override;

 private:
  static bool UseTuple(data::Collection& collection, data::LimitedTuple const& tuple);

  data::LimitedTupleDatabase& database_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLEMATCHER */