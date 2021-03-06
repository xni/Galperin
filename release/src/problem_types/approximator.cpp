#include "approximator.h"

#include "../MQ/MQ_1.h"
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
  double result = 0;
  MQ_1 cmq(p);
  for (int i = 0; i < points.size(); i++) {
    double tmp = values[i] - cmq.value(points[i]);
    result += tmp * tmp;
  }
  return result;
}


double Approximator::max_error(vector<double> p) {
  double result = -1.0;
  MQ_1 cmq(p);
  for (int i = 0; i < points.size(); i++) {
    double tmp = fabs(values[i] - cmq.value(points[i]));
    if (tmp > result)
      result = tmp;
  }
  return result;
}


string Approximator::report(vector<double> p) {
  string result;
  std::stringstream ss;
  MQ_1 cmq(p);
  ss << "Результат аппроксимации" << std::endl;
  ss << "Функция ошибки: " << (*this)(p) << std::endl;
  ss << "Максимальное непопадание: " << (*this).max_error(p) << std::endl;
  ss << "Ответ: " << std::endl;
  ss << cmq.report_value();
  return ss.str();
}
