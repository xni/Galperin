#include <cmath>
#include "MQ_1.h"


MQ_1::MQ_1(vector<double> data) :
  _data(data) {
}


double MQ_1::value(double x) {
  double result = 0;
  for (int i = 0; i < _data.size() / 3; i++) {
    double dx = _data[i * 3 + 2] - x;
    double a = _data[i * 3 + 1];
    result += _data[i * 3] * sqrt(dx*dx + a*a);
  }
  return result;
}


double MQ_1::d(double x) {
  return 0;
}


double MQ_1::laplace(double x) {
  double result = 0;
  for (int i = 0; i < _data.size() / 3; i++) {
    double dx = _data[i * 3 + 2] - x;
    double a = _data[i * 3 + 1];
    result += _data[i * 3] * (1.0 / sqrt(dx*dx + a*a) - dx*dx / pow(dx*dx + a*a, 1.5));
  }
  return result;
}
