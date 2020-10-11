/**
 * LimitedTupleDatabase.hpp - Limit Tuple Database
 *
 * Collection of limited tuples that have been identified
 */
#ifndef _SDK_LIMITEDTUPLEDATABASE
#define _SDK_LIMITEDTUPLEDATABASE

#include <memory>
#include <vector>
#include "sdk/data/LimitedTuple.hpp"
namespace sdk {
namespace data {

class LimitedTupleDatabase {
 public:
  LimitedTupleDatabase();
  bool Add(LimitedTuple* limited_tuple);
  void Remove(std::unique_ptr<LimitedTuple> const& tuple);
  std::vector<std::unique_ptr<LimitedTuple>> const& GetTuples() const;

 private:
  std::vector<std::unique_ptr<LimitedTuple>> tuples_;
};
}  // namespace data
}  // namespace sdk

#endif /* _SDK_LIMITEDTUPLEDATABASE */