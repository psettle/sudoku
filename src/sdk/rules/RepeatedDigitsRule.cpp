/**
 * RepeatedDigitsRule.cpp - Repeated Digits Rule
 *
 * Digits aren't allowed to repeat in a collection
 */
#include "sdk/rules/RepeatedDigitsRule.hpp"

using namespace sdk::rules;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

bool RepeatedDigitsRule::Apply(Collection& collection) {
  bool progress = false;

  // For each solved digit,
  for (Digit* i : collection) {
    if (i->IsSolved()) {
      // eliminate that digit from all other members of the collection
      for (Digit* j : collection) {
        if (i == j) {
          continue;
        }

        progress |= j->Remove(*i);
      }
    }
  }

  return progress;
}