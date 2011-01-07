#include <cstdlib>
#include <cmath>
#include <ctime>

#include "reverse_with_curvilinear_borders.h"
#include "../normal_distribution.h"

#include "../MQ/MQ_2.h"

const int ReverseWithCurvilinearBorders::neurons = 20;
const double ReverseWithCurvilinearBorders::w_min = -1000;
const double ReverseWithCurvilinearBorders::w_max = 1000;
const double ReverseWithCurvilinearBorders::a_min = 0;
const double ReverseWithCurvilinearBorders::a_max = 3;
const double ReverseWithCurvilinearBorders::cx_min = 0.4;
const double ReverseWithCurvilinearBorders::cx_max = 0.8;
const double ReverseWithCurvilinearBorders::cy_min = -0.1;
const double ReverseWithCurvilinearBorders::cy_max = 0.6;
const double ReverseWithCurvilinearBorders::alpha = 2.0;

ReverseWithCurvilinearBorders::ReverseWithCurvilinearBorders(double sigma) :
  Function(),
  _sigma(sigma) {
  srand(time(0));
  // Г2
  int p_g2 = 20;
  double h_g2 = (1.0 / sqrt(2) - 0.5) / (p_g2 - 1);
  for (int i = 0; i < p_g2; i++) {
    double x = 0.5 + h_g2 * i;
    double y = 0.0;
    double u = alpha * x * x;
    points.push_back(x);
    points.push_back(y);
    values.push_back(u);
  }

  // Г3
  int p_g3 = 20;
  double h_g3 = 0.5 / (p_g3 - 1);
  for (int i = 0; i < p_g3; i++) {
    double x = 0.5;
    double y = h_g3 * i;
    double u = alpha * (0.25 - y * y);
    points.push_back(x);
    points.push_back(y);
    values.push_back(u);
  }

  // датчики
  int p_d = 25;
  for (int i = 0; i < p_d; i++) {
    double x = 0.5 + (1.0 / sqrt(2.0) - 0.5) * rand() / RAND_MAX;
    double y = sqrt(0.5 - x * x) * rand() / RAND_MAX;
    double u = distribute(f(x, y), _sigma);
    points.push_back(x);
    points.push_back(y);
    values.push_back(u);
  }
}


double ReverseWithCurvilinearBorders::operator()(vector<double> p) {
  double result = 0;
  MQ_2 nn(p);
  for (int i = 0; i < values.size(); i++) {
    double tmp = values[i] - nn.value(points[2 * i], points[2 * i + 1]);
    result += tmp * tmp;
  }
  return result;
}


vector<double> ReverseWithCurvilinearBorders::random_vector() {
  vector<double> result;
  for (int i = 0; i < neurons; i++) {
    result.push_back(w_min + (w_max - w_min) * rand() / RAND_MAX);
    result.push_back(a_min + (a_max - a_min) * rand() / RAND_MAX);
    result.push_back(cx_min + (cx_max - cx_min) * rand() / RAND_MAX);
    result.push_back(cy_min + (cy_max - cy_min) * rand() / RAND_MAX);    
  }
  return result;
}


vector<double> ReverseWithCurvilinearBorders::crop(vector<double> p) {
  vector<double> result;
  for (int i = 0; i < 4 * neurons; i++) {
    result.push_back(p[i]);
    int type = i % 4;
    if (type == 0) {
      if (result[i] < w_min) result[i] = w_min;
      else if (result[i] > w_max) result[i] = w_max;
    }
    else if (type == 1) {
      if (result[i] < a_min) result[i] = a_min;
      else if (result[i] > a_max) result[i] = a_max;
    }
    else if (type == 2) {
      if (result[i] < cx_min) result[i] = cx_min;
      else if (result[i] > cx_max) result[i] = cx_max;
    }
    else if (type == 3) {
      if (result[i] < cy_min) result[i] = cy_min;
      else if (result[i] > cy_max) result[i] = cy_max;
    }    
  }
  return result;
}


double ReverseWithCurvilinearBorders::max_error(vector<double> p) {
  MQ_2 nn(p);
  double result = -1.0;
  int p_x = 100;
  double h_x = (1.0 / sqrt(2) - 0.5) / (p_x - 1);
  for (int i = 0; i < p_x; i++) {
    double x = 0.5 + h_x * i;
    double y = sqrt(0.5 - x * x);
    double t = fabs(f(x, y) - nn.value(x, y));
    if (t > result) {
      result = t;
    }
  }
  return result;
}


string ReverseWithCurvilinearBorders::report(vector<double> p) {
  std::stringstream ss;
  MQ_2 nn(p);
  int p_x = 100;
  double h_x = (1.0 / sqrt(2) - 0.5) / (p_x - 1);
  for (int i = 0; i < p_x; i++) {
    double x = 0.5 + h_x * i;
    double y = sqrt(0.5 - x * x);
    ss << x << "\t" << f(x, y) << "\t" << nn.value(x, y) << std::endl;
  }
  return ss.str();
}
