#include <iostream>

#include "sdk/sdk.hpp"

using namespace sdk::data;

static Grid easy = Grid({{kU, kU, k3, k2, kU, kU, kU, kU, kU},
                         {k2, k8, k1, k6, kU, kU, k3, kU, kU},
                         {kU, k6, kU, kU, k1, k3, kU, kU, k8},
                         {kU, kU, k9, k5, kU, k6, kU, k2, kU},
                         {kU, kU, kU, kU, k3, kU, kU, kU, k1},
                         {k5, kU, kU, kU, k2, kU, k4, k6, k3},
                         {k4, k5, kU, k8, kU, k1, k9, kU, kU},
                         {kU, k9, kU, kU, kU, kU, kU, k1, kU},
                         {k3, kU, kU, kU, k9, k7, k6, k8, kU}});

static Grid hard = Grid({{k4, kU, k7, k1, kU, k3, kU, kU, kU},
                         {k9, k1, kU, kU, kU, kU, kU, kU, kU},
                         {k6, kU, kU, kU, kU, k4, kU, k9, kU},
                         {k1, k3, kU, kU, kU, kU, kU, kU, k5},
                         {kU, k9, k8, kU, kU, k2, k7, kU, kU},
                         {k7, kU, kU, kU, k5, k8, k2, kU, kU},
                         {kU, kU, kU, kU, kU, kU, kU, k7, k3},
                         {kU, kU, k9, kU, k7, k6, kU, k5, kU},
                         {kU, kU, kU, k4, kU, k5, kU, kU, kU}});

static Grid expert = Grid({{k7, kU, kU, kU, kU, kU, kU, kU, kU},
                           {k2, k4, k9, kU, kU, kU, kU, k8, kU},
                           {kU, k5, kU, kU, kU, kU, k3, kU, kU},
                           {k3, kU, kU, kU, k5, kU, kU, kU, kU},
                           {kU, kU, kU, kU, k9, k6, kU, kU, kU},
                           {kU, kU, k6, kU, k8, k4, k7, kU, kU},
                           {kU, kU, kU, k6, k7, kU, k5, kU, kU},
                           {kU, kU, kU, kU, kU, kU, kU, k4, k9},
                           {kU, kU, kU, kU, k4, k9, kU, k2, kU}});

int main() {
  sdk::Solve(easy);
  std::cout << "easy" << std::endl << easy.ToString() << std::endl;
  sdk::Solve(hard);
  std::cout << "hard" << std::endl << hard.ToString() << std::endl;
  sdk::Solve(expert);
  std::cout << "expert" << std::endl << expert.ToString() << std::endl;
}