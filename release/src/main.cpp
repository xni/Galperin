#include <vector>
#include <iostream>
#include "problem_types/find_source.h"
#include "optimisation.h"

using std::vector;

int main() {
  for (double sigma = 0; sigma <= 0.151; sigma += 10.05) {
    FindSource* a = new FindSource(sigma);
    Optimizer o(a, 1e-12);
    vector<double> x = o.optimize();
    std::cout << a->report(x);
    delete a;
    break;
  }
  return 0;
}
