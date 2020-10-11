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
  enum DigitBitField {
    kN = 0,
    k1 = (1 << 0),
    k2 = (1 << 1),
    k3 = (1 << 2),
    k4 = (1 << 3),
    k5 = (1 << 4),
    k6 = (1 << 5),
    k7 = (1 << 6),
    k8 = (1 << 7),
    k9 = (1 << 8),
  };

  Digit();
  Digit(DigitBitField val);

  bool Intersect(Digit const& other);
  bool Remove(Digit const& other);
  bool Add(Digit const& other);

  bool IsSolved() const;
  bool CanBe(Digit const& digit) const;
  uint8_t PossibleValues() const;
  bool operator==(Digit const& other) const;
  bool operator!=(Digit const& other) const;
  std::string ToString() const;

 private:
  uint16_t val_;
};  // namespace sdk

static Digit const k1 = Digit::DigitBitField::k1;
static Digit const k2 = Digit::DigitBitField::k2;
static Digit const k3 = Digit::DigitBitField::k3;
static Digit const k4 = Digit::DigitBitField::k4;
static Digit const k5 = Digit::DigitBitField::k5;
static Digit const k6 = Digit::DigitBitField::k6;
static Digit const k7 = Digit::DigitBitField::k7;
static Digit const k8 = Digit::DigitBitField::k8;
static Digit const k9 = Digit::DigitBitField::k9;
static Digit const kU;
static Digit const kN = Digit::DigitBitField::kN;
static Digit const kDigits[] = {k1, k2, k3, k4, k5, k6, k7, k8, k9};

}  // namespace data
}  // namespace sdk
#endif /* _SDK_DIGIT */