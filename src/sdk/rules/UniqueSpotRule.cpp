/**
 * UniqueSpotRule.cpp - Unique Spot Rule
 *
 * If there is only one place left for a digit in a collection,
 * it must go there.
 */
#include "sdk/rules/UniqueSpotRule.hpp"

using namespace sdk::rules;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

/**
 * Apply the unique spot rule to the provided collection
 */
bool UniqueSpotRule::Apply(Collection& collection) {
  bool progress = false;
  // For each possible digit
  for (Digit const& digit : data::kDigits) {
    // Count how many positions it can exist in, including solved positions
    size_t valid_positions = 0;
    Digit* unsolved = nullptr;
    for (Digit* i : collection) {
      if (i->CanBe(digit)) {
        // This spot could be digit
        valid_positions++;
        if (!i->IsSolved()) {
          // This spot is not solved yet, so save it as a potential unique spot
          unsolved = i;
        }
      }
    }

    if (1 == valid_positions && unsolved) {
      // Only one option for this digit
      *unsolved = Digit(digit);
      progress = true;
    }
  }

  return progress;
}