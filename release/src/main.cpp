#include <vector>
#include <iostream>
#include "problem_types/find_source.h"
#include "optimisation.h"

using std::vector;

int main() {
  vector<double> c_min, c_max;
  int neurons = 12;
  c_min.push_back(-1);
  c_max.push_back(2);
  Restrictions r(-1000.0, 1000.0, 0, 5, c_min, c_max);
  for (double sigma = 0; sigma <= 0.151; sigma += 0.05) {
    FindSource* a = new FindSource(sigma);
    Optimizer o(a, neurons, 1e-8, r);
    vector<double> x = o.optimize();
    std::cout << a->report(x);
    delete a;
  }
  return 0;
}
