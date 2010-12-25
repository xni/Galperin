#include "approximator.h"

#include "mq.h"
#include <cmath>


Approximator::Approximator() : Function() {
  for (double i = 0; i < 0.005; i += 0.001) {
    points.push_back(i);
    values.push_back(10 * sin(M_PI_2 * i / 0.005));
  }
  for (double i = 0.005; i < 0.02; i += 0.001) {
    points.push_back(i);
    values.push_back(10 * cos(M_PI_2 * (i - 0.005) / 0.015));
  }
}


double Approximator::operator()(vector<double> p) {
  double result;
  MQ_1 cmq(p);
  for (int i = 0; i < points.size(); i++) {
    double tmp = values[i] - cmq.value(points[i]);
    result += tmp * tmp;
  }
  return result;
}
