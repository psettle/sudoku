/**
 * Collection.cpp
 *
 * Set of digits that see each other. i.e a row, column, or box.
 */
#include "sdk_Collection.hpp"

using namespace sdk;

/**
 * Populate collection with digits
 */
Collection::Collection(std::array<Digit*, 9> const& digits) : cells_(digits) {}