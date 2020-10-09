/**
 * LimitedTupleDatabase.hpp - Limit Tuple Database
 *
 * Collection of limited tuples that have been identified
 */
#ifndef _SDK_LIMITEDTUPLEDATABASE
#define _SDK_LIMITEDTUPLEDATABASE

#include <memory>
#include <unordered_set>
#include "sdk/data/LimitedTuple.hpp"
namespace sdk {
namespace data {

class LimitedTupleDatabase {
 public:
  bool Add(LimitedTuple* limited_tuple) {
    // Check if we already have an equivalent tuple
    for (auto& tuple : tuples_) {
      if (*tuple == *limited_tuple) {
        // We already have this one
        delete limited_tuple;
        return false;
      }
    }

    tuples_.emplace(std::unique_ptr<LimitedTuple>(limited_tuple));
    return true;
  }

  void Remove(std::unique_ptr<LimitedTuple> const& tuple) { tuples_.erase(tuple); }

  std::unordered_set<std::unique_ptr<LimitedTuple>> const& GetTuples() const { return tuples_; }

 private:
  std::unordered_set<std::unique_ptr<LimitedTuple>> tuples_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLEDATABASE */