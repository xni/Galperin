/* Решение задачи нахождения функции источника */

#ifndef FIND_SOURCE_H
#define FIND_SOURCE_H

#include <sstream>
#include <vector>

#include "../function.h"

using std::string;
using std::vector;

class FindSource : public Function {
 public:
  FindSource(double sigma);
  double operator()(vector<double> p);
  string report(vector<double> p);

 private:
  double max_error(vector<double> p);
  double _sigma;
  vector<double> points;
  vector<double> values;
};

#endif
