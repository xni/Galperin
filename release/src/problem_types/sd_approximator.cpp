#include "sd_approximator.h"

#include "../MQ/MQ_1.h"
#include <cmath>


SD_Approximator::SD_Approximator() : Function() {
  for (double i = 0; i < 0.01; i += 0.0001) {
    points.push_back(i);
    values.push_back(sin(i / 0.01 * M_PI));
  }
  for (double i = 0.01; i <= 0.02; i+= 0.0001) {
    points.push_back(i);
    values.push_back(sin((i - 0.01) / 0.01 * M_PI));
  }
}

double SD_Approximator::operator()(vector<double> p) {
  double result = 0;
  MQ_1 cmq(p);
  result += cmq.value(0) * cmq.value(0);
  result += cmq.value(0.02) * cmq.value(0.02);
  for (int i = 0; i < points.size(); i++) {
    double tmp = values[i] - cmq.laplace(points[i]);
    result += tmp * tmp;
  }
  return result;
}


double SD_Approximator::max_error(vector<double> p) {
  double result = -1.0;
  MQ_1 cmq(p);
  for (int i = 0; i < points.size(); i++) {
    double tmp = fabs(values[i] - cmq.laplace(points[i]));
    if (tmp > result)
      result = tmp;
  }
  return result;
}


string SD_Approximator::report(vector<double> p) {
  string result;
  std::stringstream ss;
  MQ_1 cmq(p);
  ss << "Результат аппроксимации" << std::endl;
  ss << "Функция ошибки: " << (*this)(p) << std::endl;
  ss << "Максимальное непопадание: " << (*this).max_error(p) << std::endl;
  ss << "Ответ: " << std::endl;
  ss << cmq.report_value();
  ss << "Вторая производная: " << std::endl;
  ss << cmq.report_laplace();
  return ss.str();
}
