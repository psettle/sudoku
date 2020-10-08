/**
 * RepeatedDigitsRule.cpp - Repeated Digits Rule
 *
 * Digits aren't allowed to repeat in a collection
 */
#include "sdk_RepeatedDigitsRule.hpp"

using namespace sdk;

RepeatedDigitsRule::RepeatedDigitsRule(std::array<Collection, 9>* view) : view_(view) {}

bool RepeatedDigitsRule::Apply() {
  bool progress = false;
  // Apply rule to each element of the view
  for (auto& collection : *view_) {
    progress |= ApplyToCollection(&collection);
  }

  return progress;
}

bool RepeatedDigitsRule::ApplyToCollection(Collection* collection) {
  bool progress = false;
  // For each known digit,
  for (size_t i = 0; i < 9; ++i) {
    if (collection->At(i).IsSolved()) {
      // eliminate that digit from all other members of the collection
      for (size_t j = 0; j < 9; ++j) {
        if (i == j) {
          continue;
        }

        progress |= collection->At(j).Remove(collection->At(i));
      }
    }
  }

  return progress;
}