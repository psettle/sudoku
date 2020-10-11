/**
 * Digit.cpp
 *
 * Sudoku digit/cell
 */
#include "sdk/data/Digit.hpp"

using namespace sdk::data;

/**
 * Initialize a digit that can be any value
 */
Digit::Digit() : val_(k1 | k2 | k3 | k4 | k5 | k6 | k7 | k8 | k9) {}

/**
 * Initialize a digit that can only be a single value.
 *
 * (Don't call externally, use constants defined in headers.)
 */
Digit::Digit(DigitBitField val) : val_(val) {}

/**
 * Check if this digit has been completely solved.
 */
bool Digit::IsSolved() const { return PossibleValues() == 1; }

/**
 * Set this to only possible options found in self and other.
 *
 * Return true if this operation changed this.
 */
bool Digit::Intersect(Digit const& other) {
  uint8_t before = PossibleValues();
  val_ &= other.val_;
  return PossibleValues() != before;
}

/**
 * Remove options found in other from this.
 *
 * Return true if this operation changed this.
 */
bool Digit::Remove(Digit const& other) {
  uint8_t before = PossibleValues();
  val_ &= ~other.val_;
  return PossibleValues() != before;
}

/**
 * Add options found in other to this.
 *
 * Return true if this operation changed this.
 */
bool Digit::Add(Digit const& other) {
  uint8_t before = PossibleValues();
  val_ |= other.val_;
  return PossibleValues() != before;
}

/**
 * Check if this digit can be all the possible options in digit.
 */
bool Digit::CanBe(Digit const& digit) const { return val_ & digit.val_; }

/**
 * Return the number of possible solutions to this digit.
 */
uint8_t Digit::PossibleValues() const { return __builtin_popcount(val_); }

/**
 * Equality operator.
 */
bool Digit::operator==(Digit const& other) const { return other.val_ == val_; }

/**
 * inequality operator.
 */
bool Digit::operator!=(Digit const& other) const { return !(*this == other); }

/**
 * Get a string representation of this digit.
 */
std::string Digit::ToString() const {
  std::string str = "";
  if (val_ & k1) {
    str += "1";
  }
  if (val_ & k2) {
    str += "2";
  }
  if (val_ & k3) {
    str += "3";
  }
  if (val_ & k4) {
    str += "4";
  }
  if (val_ & k5) {
    str += "5";
  }
  if (val_ & k6) {
    str += "6";
  }
  if (val_ & k7) {
    str += "7";
  }
  if (val_ & k8) {
    str += "8";
  }
  if (val_ & k9) {
    str += "9";
  }
  return str;
}