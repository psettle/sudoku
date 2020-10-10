/**
 * LimitedTupleIdentifier.hpp - Limited Tuple Identifier
 *
 * Identify cases where a digit is restricted to a subset of
 * cells within a collection.
 */
#ifndef _SDK_LIMITEDTUPLEIDENTIFIER
#define _SDK_LIMITEDTUPLEIDENTIFIER

#include <vector>
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/ICollectionRule.hpp"
#include "sdk/interfaces/ILimitedTupleObserver.hpp"

namespace sdk {
namespace rules {
class LimitedTupleIdentifier : public interfaces::ICollectionRule {
 public:
  virtual ~LimitedTupleIdentifier() {}
  LimitedTupleIdentifier(uint8_t order, data::LimitedTupleDatabase& database)
      : order_(order), database_(database) {}

  void AddObserver(interfaces::ILimitedTupleObserver* observer) {
    if (nullptr != observer) {
      observers_.push_back(observer);
    }
  }

  /**
   * Implements ICollectionRule::Apply
   */
  bool Apply(data::Collection& collection) override;

 private:
  bool CheckSelection(data::Collection& collection,
                      std::vector<data::Collection::iterator>& selection, data::Digit const& digit);

  void SendProgress(data::LimitedTuple const& tuple) const;

  uint8_t order_;
  data::LimitedTupleDatabase& database_;
  std::vector<interfaces::ILimitedTupleObserver*> observers_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLEIDENTIFIER */