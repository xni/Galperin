#include <vector>
#include <iostream>
#include "approximator.h"

using std::vector;

int main() {
  vector<double> c_min, c_max;
  c_min.push_back(0);
  c_max.push_back(0.01);
  Restrictions r(-5000.0, 5000.0, 0, 0.05, c_min, c_max);
  Approximator* a = new Approximator();
  Optimizer o(a, 8, 1e-07, r);
  vector<double> x = o.optimize();
  for (int i = 0; i < x.size(); i++) {
    std::cout << x[i] << " ";
  }
  return 0;
}
