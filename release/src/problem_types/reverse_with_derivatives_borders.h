/* Решение обратных задач в криволинейных областях */

#ifndef REVERSE_WITH_DERIVATIVES
#define REVERSE_WITH_DERIVATIVES

#include <vector>
#include <string>
#include <cmath>

#include "../function.h"

using std::string;
using std::vector;

class ReverseWithCurvilinearBorders : public Function {
 public:
  ReverseWithCurvilinearBorders(double sigma, int neurons);
  double operator()(vector<double> p);
  vector<double> random_vector();
  vector<double> crop(vector<double>);
  string report(vector<double> p);
 private:
  double max_error(vector<double> p);
  double _sigma;
  int _neurons;
  vector<double> points;
  vector<double> values;
  vector<double> points_3;
  vector<double> values_3;
  double s(double x, double y) { return x * cos(y); }
  double f(double x, double y) { return -1.0 * s(x, y); };

  const static int neurons;
  const static double w_min, w_max, a_min, a_max, cx_min, cx_max, cy_min, cy_max;
  const static double alpha;
};

#endif
