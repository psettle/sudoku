/**
 * IExclusiveTupleListener.hpp - Exclusive Tuple Listener
 *
 * Listener for progress made by exclusive tuple logic
 */
#ifndef _SDK_IEXCLUSIVETUPLELISTENER
#define _SDK_IEXCLUSIVETUPLELISTENER

#include <vector>
#include "sdk/data/Cell.hpp"
#include "sdk/data/Digit.hpp"

namespace sdk {
namespace interfaces {
class IExclusiveTupleListener {
 public:
  virtual ~IExclusiveTupleListener() {}

  virtual void OnExclusiveTupleProgress(std::vector<data::Cell const*> const& exlusive_tuple,
                                        data::Digit const& exclusive_values,
                                        data::Cell const& removed_from) {}
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_IEXCLUSIVETUPLELISTENER */