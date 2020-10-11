
#include <iostream>
#include "sdk/interfaces/ISolveObserver.hpp"

namespace sdk {
namespace data {
class SolveObserver : public sdk::interfaces::ISolveObserver {
 public:
  virtual ~SolveObserver() {}

  void OnExclusiveTupleProgress(std::vector<Cell const*> const& exlusive_tuple,
                                Digit const& exclusive_values, Cell const& removed_from) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Found exclusive tuple of:";
    for (auto cell : exlusive_tuple) {
      std::cout << " " << cell->PositionString();
    }
    std::cout << " with values: " << exclusive_values.ToString();
    std::cout << " removed those options from " << removed_from.PositionString();
    std::cout << " which leaves " << removed_from.ToString() << " as possible value(s)"
              << std::endl;

    steps_++;
  }
  void OnLimitedTupleIdentified(LimitedTuple const& tuple) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Found limited tuple of:";
    for (auto cell : tuple.GetSelection()) {
      std::cout << " " << cell->PositionString();
    }
    std::cout << " of value: " << tuple.GetDigit().ToString() << std::endl;
    steps_++;
  }

  void OnLimitedTupleTrimmed(LimitedTuple const& tuple, Cell const& breaking_member) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Removed limited tuple of:";
    for (auto cell : tuple.GetSelection()) {
      std::cout << " " << cell->PositionString();
    }
    std::cout << " because " << breaking_member.PositionString() << " can no longer be "
              << tuple.GetDigit().ToString() << std::endl;
    steps_++;
  }

  void OnLimitedTupleProgress(LimitedTuple const& tuple, Cell const& progressed_cell) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Used limited tuple of:";
    for (auto cell : tuple.GetSelection()) {
      std::cout << " " << cell->PositionString();
    }
    std::cout << " to eliminate " << tuple.GetDigit().ToString() << " from "
              << progressed_cell.PositionString() << std::endl;

    steps_++;
  }

  virtual void OnAlignedLimitedTupleProgress(
      std::vector<data::LimitedTuple const*> const& aligned_tuples,
      std::vector<data::Collection const*> const& matched_collections,
      data::Cell const& removed_from) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Used limited tuples of:";
    for (auto tuple : aligned_tuples) {
      for (auto cell : tuple->GetSelection()) {
        std::cout << " " << cell->PositionString();
      }
      std::cout << " and";
    }

    std::cout << " to remove " << aligned_tuples[0]->GetDigit().ToString() << " from "
              << removed_from.PositionString() << std::endl;

    steps_++;
  }

  void OnBisectStart(data::Cell const& target) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Starting bisect of " << target.PositionString() << " using values "
              << target.ToString() << std::endl;

    steps_++;
  }

  void OnBisectBreak(data::Cell const& target, data::Digit const& impossible_value) override {
    std::cout << "step " << steps_ << ": ";
    std::cout << "Bisect of " << target.PositionString() << " using value "
              << impossible_value.ToString() << " broke the puzzle" << std::endl;

    steps_++;
  }

  void OnBisectComplete(data::Grid const& impossible_values) override {
    std::cout << "step " << steps_ << ": ";

    std::cout << "Bisect complete, found impossible values" << std::endl
              << impossible_values.ToString() << std::endl;

    steps_++;
  };

 private:
  int steps_ = 0;
};
}  // namespace data
}  // namespace sdk