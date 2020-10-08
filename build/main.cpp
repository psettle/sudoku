#include <iostream>

#include "sdk.hpp"

using namespace sdk;

static Grid easy = Grid({{kU, kU, k3, k2, kU, kU, kU, kU, kU},
                         {k2, k8, k1, k6, kU, kU, k3, kU, kU},
                         {kU, k6, kU, kU, k1, k3, kU, kU, k8},
                         {kU, kU, k9, k5, kU, k6, kU, k2, kU},
                         {kU, kU, kU, kU, k3, kU, kU, kU, k1},
                         {k5, kU, kU, kU, k2, kU, k4, k6, k3},
                         {k4, k5, kU, k8, kU, k1, k9, kU, kU},
                         {kU, k9, kU, kU, kU, kU, kU, k1, kU},
                         {k3, kU, kU, kU, k9, k7, k6, k8, kU}});

int main() {
  std::cout << Solve(easy) << std::endl;
  std::cin.get();
}