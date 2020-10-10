/**
 * IAlignedLimitedTupleListener.hpp - Aligned Limited Tuple Listener
 *
 * Listener for progress made by aligned limited tuple logic
 */
#ifndef _SDK_IALIGNEDLIMITEDTUPLELISTENER
#define _SDK_IALIGNEDLIMITEDTUPLELISTENER

#include "sdk/data/Collection.hpp"
#include "sdk/data/LimitedTuple.hpp"

namespace sdk {
namespace interfaces {
class IAlignedLimitedTupleListener {
 public:
  virtual ~IAlignedLimitedTupleListener() {}

  virtual void OnAlignedLimitedTupleProgress(
      std::vector<data::LimitedTuple const*> const& aligned_tuples,
      std::vector<data::Collection const*> const& matched_collections,
      data::Cell const& removed_from) {}
};
}  // namespace interfaces
}  // namespace sdk

#endif /* _SDK_IALIGNEDLIMITEDTUPLELISTENER */