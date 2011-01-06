/* Решение обратных задач в криволинейных областях */

#ifndef REVERSE_WITH_CURVILINEAR
#define REVERSE_WITH_CURVILINEAR

#include "../function.h"

using std::string;
using std::vector;

class ReverseWithCurvilinearBorders : public Function {
 public:
  ReverseWithCurvilinearBorders(double sigma);
  double operator()(vector<double> p);
  vector<double> random_vector();
  vector<double> crop(vector<double>);
  string report(vector<double> p);
 private:
  double max_error(vector<double> p);
  double _sigma;
  vector<double> points;
  vector<double> values;

  const static int neurons, points;
  const static double w_min, w_max, a_min, a_max, cx_min, cx_max, cy_min, cy_max;
};

#endif
