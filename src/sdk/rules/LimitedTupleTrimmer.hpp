/**
 * LimitedTupleTrimmer.hpp - Limited Tuple Trimmer
 *
 * Check for limited tuples that have been resolved and delete them.
 */
#ifndef _SDK_LIMITEDTUPLETRIMMER
#define _SDK_LIMITEDTUPLETRIMMER

#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
namespace rules {
class LimitedTupleTrimmer : public interfaces::IRule {
 public:
  virtual ~LimitedTupleTrimmer() {}
  LimitedTupleTrimmer(data::LimitedTupleDatabase& database) : database_(database) {}

  /**
   * Implements IRule::Apply
   */
  bool Apply() override;

 private:
  data::LimitedTupleDatabase& database_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLETRIMMER */