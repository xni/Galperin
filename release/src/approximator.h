#ifndef APPROXIMATOR
#define APPROXIMATOR

#include <vector>

#include "restrictions.h"
#include "optimisation.h"

using std::vector;

class Approximator : public Function {
 public:
  Approximator();
  double operator()(vector<double> p);

 private:
  vector<double> points;
  vector<double> values;
};

#endif
