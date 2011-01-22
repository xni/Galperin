#include <vector>
#include <iostream>
#include "problem_types/reverse_with_derivatives_borders.h"
#include "optimisation.h"

using std::vector;

int main() {
  ReverseWithCurvilinearBorders* a;
  double sigma;

  while (true) {
    sigma = 0.0;
    int neurons = 4;
    a = new ReverseWithCurvilinearBorders(sigma, neurons);
    Optimizer o(a, 1e-8);
    vector<double> x = o.optimize();
    std::cout << a->report(x);
    delete a;
    std::cout.flush();
    break;
  }
  return 0;
}
