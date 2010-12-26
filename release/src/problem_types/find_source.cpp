#include "find_source.h"
#include "../normal_distribution.h"

#include "../MQ/MQ_1.h"
#include <cmath>


FindSource::FindSource(double sigma) :
  Function(),
  _sigma(sigma) {
  for (double i = 0; i <= 1; i += 0.01) {
    points.push_back(i);
    values.push_back(distribute(1000 * i * i, _sigma));
  }
}


double FindSource::operator()(vector<double> p) {
  double result = 0;
  MQ_1 cmq(p);
  for (int i = 0; i < points.size(); i++) {
    double tmp = values[i] - cmq.value(points[i]);
    result += tmp * tmp;
  }
  return result;
}


double FindSource::max_error(vector<double> p) {
  double result = -1.0;
  MQ_1 cmq(p);
  for (int i = 0; i < points.size(); i++) {
    double tmp = fabs(values[i] - cmq.value(points[i]));
    if (tmp > result)
      result = tmp;
  }
  return result;
}


string FindSource::report(vector<double> p) {
  string result;
  std::stringstream ss;
  MQ_1 cmq(p);
  ss << "Результат аппроксимации при допустимой погрешности датчиков " << \
    _sigma << std::endl;
  ss << "Функция ошибки: " << (*this)(p) << std::endl;
  ss << "Максимальное непопадание: " << (*this).max_error(p) << std::endl;
  ss << "Ответ: " << std::endl;
  ss << cmq.report_value();
  ss << "Вторая производная: " << std::endl;
  ss << cmq.report_laplace();
  return ss.str();
}
