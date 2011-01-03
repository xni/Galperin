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
  vector<double> random_vector();
  vector<double> crop(vector<double>);
  string report(vector<double> p);

 private:
  double max_error(vector<double> p);
  double _sigma;
  vector<double> points;
  vector<double> values;

  const static int left_neurons;
  const static int right_neurons;
  const static double w_min, w_max, a_min, a_max;
  const static double c_min;
  const static double c_max;
};

#endif
