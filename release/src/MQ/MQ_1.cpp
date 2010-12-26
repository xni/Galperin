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


string MQ_1::report_value() {
  std::stringstream ss;
  for (int i = 0; i < _data.size() / 3; i++) {
    ss << "+(" << _data[i * 3] << ")*sqrt(" << _data[i * 3 + 1] << "**2 + (x-" << \
      _data[i * 3 + 2] << ")**2) ";
  }
  ss << std::endl;
  return ss.str();
}


string MQ_1::report_laplace() {
  std::stringstream ss;
  for (int i = 0; i < _data.size() / 3; i++) {
    double w = _data[i * 3];
    double a = _data[i * 3 + 1];
    double c = _data[i * 3 + 2];
    ss << "+(" << w << ") * (1.0 / sqrt((x-" << c << ")**2 + " << a << "**2) - (x-" << c << ")**2 / ((x-" << c << ")**2 + " << a << "**2)**1.5)";
  }
  ss << std::endl;
  return ss.str();
}
