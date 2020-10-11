/**
 * LimitedTupleIdentifier.hpp - Limited Tuple Identifier
 *
 * Identify cases where a digit is restricted to a subset of
 * cells within a collection.
 */
#ifndef _SDK_LIMITEDTUPLEIDENTIFIER
#define _SDK_LIMITEDTUPLEIDENTIFIER

#include <stdint.h>
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/ICollectionRule.hpp"
#include "sdk/interfaces/ILimitedTupleObserver.hpp"

namespace sdk {
namespace rules {
class LimitedTupleIdentifier : public interfaces::ICollectionRule {
 public:
  virtual ~LimitedTupleIdentifier() {}
  LimitedTupleIdentifier(uint8_t order, data::LimitedTupleDatabase* database);
  void SetObserver(interfaces::ILimitedTupleObserver* observer);
  bool Apply(data::Collection& collection) override;

 private:
  bool CheckSelection(data::Collection& collection,
                      std::vector<data::Collection::iterator>& selection, data::Digit const& digit);
  void SendProgress(data::Cell const& progress) const;
  void SendIdentified(data::LimitedTuple const& tuple) const;

  uint8_t order_;
  data::LimitedTupleDatabase* database_;
  interfaces::ILimitedTupleObserver* observer_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLEIDENTIFIER */