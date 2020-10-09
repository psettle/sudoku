/**
 * Digit.cpp
 *
 * Sudoku digit/cell
 */
#include "sdk/data/Digit.hpp"

using namespace sdk::data;

std::string Digit::ToString() const {
  std::string str = "";
  if (val_ & k1.val_) {
    str += "1";
  }
  if (val_ & k2.val_) {
    str += "2";
  }
  if (val_ & k3.val_) {
    str += "3";
  }
  if (val_ & k4.val_) {
    str += "4";
  }
  if (val_ & k5.val_) {
    str += "5";
  }
  if (val_ & k6.val_) {
    str += "6";
  }
  if (val_ & k7.val_) {
    str += "7";
  }
  if (val_ & k8.val_) {
    str += "8";
  }
  if (val_ & k9.val_) {
    str += "9";
  }
  return str;
}