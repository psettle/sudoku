/**
 * LimitedTupleDatabase.hpp - Limit Tuple Database
 *
 * Collection of limited tuples that have been identified
 */
#include "sdk/data/LimitedTupleDatabase.hpp"

using namespace sdk::data;

/**
 * Create an empty database
 */
LimitedTupleDatabase::LimitedTupleDatabase() : tuples_() {}

/**
 * At a new limited tuple to the collection
 */
bool LimitedTupleDatabase::Add(LimitedTuple* limited_tuple) {
  // Check if we already have an equivalent tuple
  for (auto& tuple : tuples_) {
    if (*tuple == *limited_tuple) {
      // We already have this one
      delete limited_tuple;
      return false;
    }
  }

  tuples_.push_back(std::unique_ptr<LimitedTuple>(limited_tuple));
  return true;
}

/**
 * Remove an existing limited tuple from the collection
 */
void LimitedTupleDatabase::Remove(std::unique_ptr<LimitedTuple> const& tuple) {
  for (auto it = tuples_.begin(); it != tuples_.end(); it++) {
    if ((*it).get() == tuple.get()) {
      tuples_.erase(it);
      break;
    }
  }
}

/**
 * Get all the existing limited tuples
 */
std::vector<std::unique_ptr<LimitedTuple>> const& LimitedTupleDatabase::GetTuples() const {
  return tuples_;
}