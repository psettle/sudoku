#include <iostream>
#include "SolveObserver.hpp"
#include "puzzles.hpp"
#include "sdk/sdk.hpp"

using namespace sdk::data;

#include "sdk/utility/SelectionIterator.hpp"

int main() {
  SolveObserver observer;

  sdk::Solve(ctc);
  std::cout << "ctc" << std::endl << ctc.ToString() << std::endl;
  sdk::Solve(ywing);
  std::cout << "ywing" << std::endl << ywing.ToString() << std::endl;
  sdk::Solve(swordfish);
  std::cout << "swordfish" << std::endl << swordfish.ToString() << std::endl;

  return 0;
}