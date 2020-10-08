/**
 * sdk_Digit.hpp - Sudoku Digit
 */
#ifndef _SDK_DIGIT
#define _SDK_DIGIT
#include <iostream>

#include "stdint.h"
namespace sdk {
class Digit {
 public:
  Digit() : val_(0x1FF) {}
  Digit(uint16_t val) : val_(val) {}

  bool IsSolved() const { return (val_ & (val_ - 1)) == 0; }
  bool Remove(Digit const& other) {
    if (val_ & other.val_) {
      static int i = 0;
      std::cout << i++ << std::endl;
      val_ &= ~other.val_;
      return true;
    } else {
      return false;
    }
  }

 private:
  uint16_t val_;
};  // namespace sdk

static Digit const k1 = (1 << 0);
static Digit const k2 = (1 << 1);
static Digit const k3 = (1 << 2);
static Digit const k4 = (1 << 3);
static Digit const k5 = (1 << 4);
static Digit const k6 = (1 << 5);
static Digit const k7 = (1 << 6);
static Digit const k8 = (1 << 7);
static Digit const k9 = (1 << 8);
static Digit const kU;

}  // namespace sdk
#endif /* _SDK_DIGIT */