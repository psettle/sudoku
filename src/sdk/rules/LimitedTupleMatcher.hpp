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
#include "sdk/interfaces/ILimitedTupleObserver.hpp"

namespace sdk {
namespace rules {
class LimitedTupleMatcher : public interfaces::ICollectionRule {
 public:
  virtual ~LimitedTupleMatcher() {}
  LimitedTupleMatcher(data::LimitedTupleDatabase* database);
  void SetObserver(interfaces::ILimitedTupleObserver* observer);
  bool Apply(data::Collection& collection) override;

 private:
  bool UseTuple(data::Collection& collection, data::LimitedTuple const& tuple);
  void SendProgress(data::LimitedTuple const& tuple, data::Cell const& progressed_cell) const;

  data::LimitedTupleDatabase* database_;
  interfaces::ILimitedTupleObserver* observer_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLEMATCHER */