/**
 * IBisectListener.hpp - Bisect Listener
 *
 * Listener for progress made by bisect logic
 */
#ifndef _SDK_IBISECTLISTENER
#define _SDK_IBISECTLISTENER

#include "sdk/data/Cell.hpp"
#include "sdk/data/Digit.hpp"
#include "sdk/data/Grid.hpp"

namespace sdk {
namespace interfaces {
class IBisectListener {
 public:
  virtual ~IBisectListener() {}

  virtual void OnBisectStart(data::Cell const& target, data::Digit const& digit) = 0;
  virtual void OnBisectBreak(data::Cell const& target, data::Digit const& impossible_value) {}
  virtual void OnBisectComplete(data::Grid const& impossible_values) = 0;
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_IBISECTLISTENER */