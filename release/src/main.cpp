#include <vector>
#include <iostream>
#include "problem_types/reverse_with_curvilinear_borders.h"
#include "optimisation.h"

using std::vector;

int main() {
  for (double sigma = 0.07; sigma <= 0.151; sigma += 10.05) {
    ReverseWithCurvilinearBorders* a = new ReverseWithCurvilinearBorders(sigma);
    Optimizer o(a, 1e-14);
    vector<double> x = o.optimize();
    std::cout << a->report(x);
    delete a;
    break;
  }
  return 0;
}
