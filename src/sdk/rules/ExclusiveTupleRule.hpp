/**
 * ExclusiveTupleRule.hpp - Exclusive Tuple Rule
 *
 * If N cells consist of N possible digits, those digits cannot exist
 * in any other cells
 */
#ifndef _SDK_EXCLUSIVETUPLERULE
#define _SDK_EXCLUSIVETUPLERULE

#include "sdk/interfaces/ICollectionRule.hpp"
#include "sdk/interfaces/IExclusiveTupleListener.hpp"
#include "sdk/utility/SelectionIterator.hpp"

namespace sdk {
namespace rules {
class ExclusiveTupleRule : public interfaces::ICollectionRule {
 public:
  virtual ~ExclusiveTupleRule() {}

  ExclusiveTupleRule(uint8_t order) : order_(order) {}
  void AddListener(interfaces::IExclusiveTupleListener* listener) {
    if (nullptr != listener) {
      listeners_.push_back(listener);
    }
  }

  /**
   * Implements ICollectionRule::Apply
   */
  bool Apply(data::Collection& collection) override;

 private:
  void SendProgress(utility::SelectionIterator<data::Collection::iterator> const& exclusive_tuple,
                    data::Digit const& exclusive_values, data::Cell const& removed_from) const;

  uint8_t order_;
  std::vector<interfaces::IExclusiveTupleListener*> listeners_;
};
}  // namespace rules
}  // namespace sdk

#endif /* _SDK_EXCLUSIVETUPLERULE */