/**
 * Digit.hpp - Sudoku Digit
 */
#ifndef _SDK_DIGIT
#define _SDK_DIGIT
#include <stdint.h>

#include <string>
namespace sdk {
namespace data {
class Digit {
 public:
  Digit() : val_(0x1FF) {}
  Digit(uint16_t val) : val_(val) {}

  bool IsSolved() const { return PossibleValues() == 1; }

  bool Remove(Digit const& other);
  bool Add(Digit const& other);

  bool CanBe(Digit const& digit) const { return val_ & digit.val_; }
  uint8_t PossibleValues() const { return __builtin_popcount(val_); }

  std::string ToString() const;

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
static Digit const kDigits[] = {k1, k2, k3, k4, k5, k6, k7, k8, k9};

}  // namespace data
}  // namespace sdk
#endif /* _SDK_DIGIT */