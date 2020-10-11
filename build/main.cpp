#include <iostream>
#include "SolveObserver.hpp"
#include "puzzles.hpp"
#include "sdk/sdk.hpp"

using namespace sdk::data;

#include "sdk/utility/SelectionIterator.hpp"

int main() {
  SolveObserver observer;

  sdk::Solve(swordfish);
  std::cout << "swordfish" << std::endl << swordfish.ToString() << std::endl;
  // sdk::Solve(diabolical);
  // std::cout << "diabolical" << std::endl << diabolical.ToString() << std::endl;

  return 0;
}