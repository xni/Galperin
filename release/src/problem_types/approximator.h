/* Решение задачи апроксимации функции по заданным значениям */

#ifndef APPROXIMATOR_H
#define APPROXIMATOR_H

#include <sstream>
#include <vector>

#include "../function.h"

using std::string;
using std::vector;

class Approximator : public Function {
 public:
  Approximator();
  double operator()(vector<double> p);
  string report(vector<double> p);

 private:
  double max_error(vector<double> p);
  
  vector<double> points;
  vector<double> values;
};

#endif
