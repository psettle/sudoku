/**
 * SelectionIterator.hpp - Selection Iterator
 *
 * Iterate over all unique selections of a collection.
 */
#ifndef _SDK_SELECTIONITERATOR
#define _SDK_SELECTIONITERATOR

#include <stdint.h>
#include <vector>

namespace sdk {
namespace utility {
template <class Iterator>
class SelectionIterator {
 public:
  /**
   * Initialize an iterator that will iterate over all collections of size order
   * in the provided container.
   */
  SelectionIterator(Iterator const& begin, Iterator const& end, uint8_t order) : end_(end) {
    while (order--) {
      iterators_.push_back(begin + iterators_.size());
    }
  }

  /**
   * Increment onto the next unique selection of elements.
   *
   * Returns true if the selection is valid, false if not valid.
   */
  bool Increment() { return Increment(0); }

  /**
   * View the currently selected selection
   */
  std::vector<Iterator>& GetSelection() { return iterators_; }

 private:
  bool Increment(uint8_t order);

  std::vector<Iterator> iterators_;
  Iterator const& end_;
};  // namespace utility

/**
 * Private increment that exposes the recursive interface used internally.
 */
template <class Iterator>
bool SelectionIterator<Iterator>::Increment(uint8_t order) {
  if (order == iterators_.size()) {
    // Hit end of possible combinations
    return false;
  }

  // Increment iterator at the provided order
  iterators_[iterators_.size() - order - 1]++;

  if (iterators_[iterators_.size() - order - 1] == end_ - order) {
    // Iterator reached the last viable element, increment the higher order iterator and reset
    // ourselves to right after.
    if (Increment(order + 1)) {
      iterators_[iterators_.size() - order - 1] = iterators_[iterators_.size() - order - 2] + 1;
      return true;
    } else {
      // Incrementing the higher order iterator failed, so we are done.
      return false;
    }
  } else {
    // Iterator landed on a valid element, success.
    return true;
  }
}

}  // namespace utility
}  // namespace sdk
#endif /* _SDK_SELECTIONITERATOR */