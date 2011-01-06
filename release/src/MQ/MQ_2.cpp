#include <cmath>
#include "MQ_2.h"

MQ_2::MQ_2(vector<double> data) :
  _data(data) {
}


double MQ_2::value(double x, double y) {
  double result = 0;
  for (int i = 0; i < _data.size() / 4; i++) {
    result += w(i) * core(i, x, y);
  }
  return result;
}


double MQ_2::laplace(double x, double y) {
  double result = 0;
  for (int i = 0; i < _data.size() / 4; i++) {
    result += 2.0 * w(i) / core(i, x, y) \
      - w(i) * (dx(i) * dx(i) + dy(i) * dy(i)) / pow(core(i, x, y), 3);
  }
  return result;
}


string MQ_2::report_value() {
  std::stringstream ss;
  for (int i = 0; i < _data.size() / 4; i++) {
    ss << "+(" << w(i) << ")*sqrt(" << a(i) << "**2 + (" << cx(i) << "-x)**2 + (" << cy(i) << "-y)**2) ";
  }
  ss << std::endl;
  return ss.str();
}
