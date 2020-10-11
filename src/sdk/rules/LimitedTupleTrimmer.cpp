/**
 * LimitedTupleTrimmer.cpp - Limited Tuple Trimmer
 *
 * Check for limited tuples that have been resolved and delete them.
 */
#include "sdk/rules/LimitedTupleTrimmer.hpp"
#include <memory>
#include <vector>

using namespace sdk::rules;

/**
 * LimitedTupleTrimmer ctor
 */
LimitedTupleTrimmer::LimitedTupleTrimmer(data::LimitedTupleDatabase* database)
    : database_(database), observer_(nullptr) {}

/**
 * Set an observer for limited tuple trimming
 */
void LimitedTupleTrimmer::SetObserver(interfaces::ILimitedTupleObserver* observer) {
  if (observer) {
    observer_ = observer;
  }
}

/**
 * Look throuhg identified limited tuples and delete any that
 * have been reduced.
 */
bool LimitedTupleTrimmer::Apply() {
  std::vector<std::unique_ptr<data::LimitedTuple> const*> to_remove;

  for (std::unique_ptr<data::LimitedTuple> const& tuple : database_->GetTuples()) {
    data::Digit const& digit = tuple->GetDigit();

    for (data::Cell const* member : tuple->GetSelection()) {
      if (!member->CanBe(digit)) {
        // A member of this tuple can't be the assigned digit, so it isn't valid
        to_remove.push_back(&tuple);
        SendProgress(*tuple, *member);
        break;
      }
    }
  }

  for (std::unique_ptr<data::LimitedTuple> const* tuple : to_remove) {
    database_->Remove(*tuple);
  }

  // Trimming tuples is not real progress
  return false;
}

/**
 * Send a notification describing the logical progress that was made to observer
 */
void LimitedTupleTrimmer::SendProgress(data::LimitedTuple const& tuple,
                                       data::Cell const& breaking_member) const {
  if (observer_) {
    observer_->OnLimitedTupleTrimmed(tuple, breaking_member);
  }
}