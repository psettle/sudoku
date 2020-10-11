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
#include <set>
#include "sdk/data/Collection.hpp"
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/interfaces/IAlignedLimitedTupleListener.hpp"
#include "sdk/interfaces/IRule.hpp"

namespace sdk {
namespace rules {

class AlignedLimitedTupleRule : public interfaces::IRule {
 public:
  virtual ~AlignedLimitedTupleRule() {}

  AlignedLimitedTupleRule(uint8_t order, data::LimitedTupleDatabase* database, data::View* view);
  void SetListener(interfaces::IAlignedLimitedTupleListener* listener);
  bool Apply() override;

 private:
  using LimitedTupleList = std::vector<std::unique_ptr<data::LimitedTuple>>;

  bool CheckSelection(std::vector<LimitedTupleList::const_iterator> const& selection);
  void SendProgress(std::vector<LimitedTupleList::const_iterator> const& aligned_tuples,
                    std::set<data::Collection*> const& matched_collections,
                    data::Cell const& removed_from);

  uint8_t order_;
  data::LimitedTupleDatabase* database_;
  data::View* view_;
  interfaces::IAlignedLimitedTupleListener* listener_;
};

}  // namespace rules
}  // namespace sdk
#endif /* _SDK_ALIGNEDLIMITEDTUPLERULE */