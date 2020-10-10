/**
 * sdk_ILimitedTupleObserver.hpp - Limited Tuple Observer
 *
 * Listener for progress made by limited tuple logic
 */
#ifndef _SDK_ILIMITEDTUPLEOBSERVER
#define _SDK_ILIMITEDTUPLEOBSERVER

#include <vector>
#include "sdk/data/Cell.hpp"
#include "sdk/data/LimitedTuple.hpp"

namespace sdk {
namespace interfaces {
class ILimitedTupleObserver {
 public:
  virtual ~ILimitedTupleObserver() {}

  virtual void OnLimitedTupleIdentified(data::LimitedTuple const& tuple) {}
  virtual void OnLimitedTupleTrimmed(data::LimitedTuple const& tuple,
                                     data::Cell const& breaking_member) {}
  virtual void OnLimitedTupleProgress(data::LimitedTuple const& tuple,
                                      data::Cell const& progressed_cell) {}
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_ILIMITEDTUPLEOBSERVER */