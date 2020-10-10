/**
 * AlignedLimitedTupleRule.hpp - Aligned Limit Tuple Rule
 *
 * If N limited tuples of the same digit together touch exactly N
 * distinct collections, then that digit cannot exist withing the
 * touched collections outside the members of the limited tuples.
 *
 * (More commonly known as X-wing, Swordfish, etc.)
 */
#ifndef _SDK_ALIGNEDLIMITEDTUPLERULE
#define _SDK_ALIGNEDLIMITEDTUPLERULE

#include <stdint.h>
#include "sdk/data/Collection.hpp"
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/IRule.hpp"
#include "sdk/utility/SelectionIterator.hpp"

namespace sdk {
namespace rules {

class AlignedLimitedTupleRule : public interfaces::IRule {
 public:
  virtual ~AlignedLimitedTupleRule() {}

  AlignedLimitedTupleRule(uint8_t order, data::LimitedTupleDatabase& database, data::View& view);

  /**
   * Implements IRule::Apply
   */
  bool Apply() override;

 private:
  using LimitedTupleList = std::vector<std::unique_ptr<data::LimitedTuple>>;

  bool CheckSelection(std::vector<LimitedTupleList::const_iterator> const& selection);

  uint8_t order_;
  data::LimitedTupleDatabase& database_;
  data::View& view_;
};

}  // namespace rules
}  // namespace sdk
#endif /* _SDK_ALIGNEDLIMITEDTUPLERULE */