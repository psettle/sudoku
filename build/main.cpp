#include <iostream>
#include "SolveObserver.hpp"
#include "puzzles.hpp"
#include "sdk/sdk.hpp"

using namespace sdk::data;

#include "sdk/utility/SelectionIterator.hpp"

int main() {
  // SolveObserver observer;

  sdk::Solve(easy);
  std::cout << "easy" << std::endl << easy.ToString() << std::endl;
  sdk::Solve(hard);
  std::cout << "hard" << std::endl << hard.ToString() << std::endl;
  sdk::Solve(expert);
  std::cout << "expert" << std::endl << expert.ToString() << std::endl;
  sdk::Solve(ctc2);
  std::cout << "ctc2" << std::endl << ctc2.ToString() << std::endl;
  sdk::Solve(ctc3);
  std::cout << "ctc3" << std::endl << ctc3.ToString() << std::endl;
  sdk::Solve(xwing);
  std::cout << "xwing" << std::endl << xwing.ToString() << std::endl;

  return 0;
}