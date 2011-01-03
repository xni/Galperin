#include <cstdlib>
#include <cmath>
#include <ctime>

#include "find_source.h"
#include "../normal_distribution.h"

#include "../MQ/MQ_1.h"


const int FindSource::left_neurons = 30;
const int FindSource::right_neurons = 10;
const double FindSource::w_min = -1000;
const double FindSource::w_max = 1000;
const double FindSource::a_min = 0;
const double FindSource::a_max = 20;
const double FindSource::c_min = -1;
const double FindSource::c_max = 4;



FindSource::FindSource(double sigma) :
  Function(),
  _sigma(sigma) {
  srand(time(0));
  //  double data[100] = {-6.4288564535e-05, -0.00012831828347, -0.000191831356659, -0.000254572064156, -0.00031628779584, -0.000376730068518, -0.000435655526407, -0.00049282692098, -0.000548014066211, -0.000600994765392, -0.000651555705776, -0.000699493317457, -0.000744614593009, -0.000786737864614, -0.000825693535513, -0.000861324762868, -0.000893488089266, -0.000922054020329, -0.000946907546104, -0.00096794860413, -0.000985092482324, -0.000998270160059, -0.00100742858606, -0.00101253089201, -0.00101355654097, -0.0010105014101, -0.0010033778072, -0.000992214421207, -0.000977056206615, -0.000957964202513, -0.000935015286785, -0.000908301866571, -0.00087793150619, -0.000844026494036, -0.000806723350197, -0.000766172276756, -0.000722536553017, -0.000675991878071, -0.000626725663356, -0.000574936278057, -0.000520832250389, -0.000464631427975, -0.000406560100697, -0.000346852089561, -0.000285747805234, -0.000223493280054, -0.000160339177398, -9.65397824086e-05, -3.23519781395e-05, 3.19657887633e-05, 9.61541707235e-05, 0.000159954719371, 0.000223110548213, 0.000285367366962, 0.000346474505413, 0.00040618592274, 0.000464261198159, 0.000520466498956, 0.000574575521991, 0.000626370404886, 0.000675642603223, 0.000722193730226, 0.000765836355548, 0.000806394759931, 0.000843705642728, 0.000877618779407, 0.000907997626415, 0.000934719870955, 0.000957677923456, 0.000976779350775, 0.000991947248361, 0.0010031205499, 0.00101025427318, 0.00101331970121, 0.00101230449784, 0.00100721275743, 0.000998064988318, 0.000984898030303, 0.000967764906254, 0.000946734608633, 0.000921891821687, 0.000893336580473, 0.000861183868065, 0.000825563152573, 0.000786617865852, 0.000744504825969, 0.000699393605786, 0.00065146585018, 0.000600914544658, 0.000547943238308, 0.000492765224219, 0.000435602680668, 0.000376685776526, 0.000316251744501, 0.000254543925927, 0.000191810790963, 0.000128304938147, 6.42820773144e-05};
  double h = M_PI / 99;
  for (int i = 0; i < 100; i++) {
    points.push_back(h * i);
    //values.push_back(distribute(data[i], _sigma));
    values.push_back(sin(h * i));
  }
}


double FindSource::operator()(vector<double> p) {
  double result = 0;
  vector<double> approximator_vector, sd_vector;
  for (int i = 0; i < 3 * left_neurons; i++) approximator_vector.push_back(p[i]);
  for (int i = 3 * left_neurons; i < 3 * (left_neurons + right_neurons); i++) sd_vector.push_back(p[i]);
  MQ_1 appr(approximator_vector);
  MQ_1 sd(sd_vector);
  for (int i = 0; i < points.size(); i++) {
    double val_tmp = values[i] - appr.value(points[i]);
    result += val_tmp * val_tmp;
    double sd_tmp = appr.laplace(points[i]) - sd.value(points[i]);
    result += 1.0 * sd_tmp * sd_tmp;
   }
  return result;
}


vector<double> FindSource::random_vector() {
  vector<double> result;
  for (int i = 0; i < left_neurons + right_neurons; i++) {
    result.push_back(w_min + (w_max - w_min) * rand() / RAND_MAX);
    result.push_back(a_min + (a_max - a_min) * rand() / RAND_MAX);
    result.push_back(c_min + (c_max - c_min) * rand() / RAND_MAX);
  }
  return result;
}


vector<double> FindSource::crop(vector<double> p) {
  vector<double> result;
  for (int i = 0; i < 3 * (left_neurons + right_neurons); i++) {
    result.push_back(p[i]);
    int type = i % 3;
    if (type == 0) {
      if (result[i] < w_min) result[i] = w_min;
      else if (result[i] > w_max) result[i] = w_max;
    }
    else if (type == 1) {
      if (result[i] < a_min) result[i] = a_min;
      else if (result[i] > a_max) result[i] = a_max;
    }
    else if (type == 2) {
      if (result[i] < c_min) result[i] = c_min;
      else if (result[i] > c_max) result[i] = c_max;
    }
  }
  return result;
}


double FindSource::max_error(vector<double> p) {
  double result = -1.0;
  vector<double> tv;
  for (int i = 0; i < 3 * left_neurons; i++) {
    tv.push_back(p[i]);
  }
  MQ_1 cmq(tv);
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
  vector<double> tv;
  for (int i = 0; i < 3 * left_neurons; i++) {
    tv.push_back(p[i]);
  }
  MQ_1 cmq(tv);
  ss << "Результат аппроксимации при допустимой погрешности датчиков " << \
    _sigma << std::endl;
  ss << "Функция ошибки: " << (*this)(p) << std::endl;
  ss << "Максимальное непопадание: " << (*this).max_error(p) << std::endl;
  ss << "Ответ: " << std::endl;
  ss << cmq.report_value();
  ss << "Вторая производная: " << std::endl;
  ss << cmq.report_laplace();
  ss << "Табулирование значений: x, точное, найденное" << std::endl;
  double h = M_PI / 99;
  for (int i = 0; i < 100; i++) {
    ss << i * h << '\t' << values[i] << '\t' << cmq.value(i * h) << '\t' << std::endl;
  }
  ss << "Табулирование второй производной: x, точное, найденное" << std::endl;
  for (int i = 0; i < 100; i++) {
    double r = 0;
    if (i * h < 0.1)
      r = sin(i * h / 0.1 * 3.1415);
    else
      r = -sin((i * h - 0.1) / 0.1 * 3.1415);
    r = -sin(h * i);
    ss << i * h << '\t' << r << '\t' << cmq.laplace(i * h) << std::endl;
  }
  return ss.str();
}
