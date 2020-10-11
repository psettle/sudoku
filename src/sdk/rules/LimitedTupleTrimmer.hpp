/**
 * LimitedTupleTrimmer.hpp - Limited Tuple Trimmer
 *
 * Check for limited tuples that have been resolved and delete them.
 */
#ifndef _SDK_LIMITEDTUPLETRIMMER
#define _SDK_LIMITEDTUPLETRIMMER

#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/ILimitedTupleObserver.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
namespace rules {
class LimitedTupleTrimmer : public interfaces::IRule {
 public:
  virtual ~LimitedTupleTrimmer() {}
  LimitedTupleTrimmer(data::LimitedTupleDatabase* database);
  void SetObserver(interfaces::ILimitedTupleObserver* observer);
  bool Apply() override;

 private:
  void SendProgress(data::LimitedTuple const& tuple, data::Cell const& breaking_member) const;

  data::LimitedTupleDatabase* database_;
  interfaces::ILimitedTupleObserver* observer_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLETRIMMER */