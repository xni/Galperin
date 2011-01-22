#include <cstdlib>
#include <ctime>

#include "reverse_with_derivatives_borders.h"
#include "../normal_distribution.h"

#include "../MQ/MQ_2.h"

//const int ReverseWithCurvilinearBorders::neurons = 25;
const double ReverseWithCurvilinearBorders::w_min = -1000;
const double ReverseWithCurvilinearBorders::w_max = 1000;
const double ReverseWithCurvilinearBorders::a_min = 0;
const double ReverseWithCurvilinearBorders::a_max = 3;
const double ReverseWithCurvilinearBorders::cx_min = -0.5;
const double ReverseWithCurvilinearBorders::cx_max = 1.5;
const double ReverseWithCurvilinearBorders::cy_min = -0.5;
const double ReverseWithCurvilinearBorders::cy_max = 2.0;
const double ReverseWithCurvilinearBorders::alpha = 2.0;

ReverseWithCurvilinearBorders::ReverseWithCurvilinearBorders(double sigma, int neurons) :
  Function(),
  _sigma(sigma),
  _neurons(neurons) {
  srand(time(0));
  // нижняя граница - значения
  int p_b = 100;
  for (int i = 0; i < p_b; i++) {
    double x = double(rand()) / RAND_MAX;
    double y = 0.0;
    double u = s(x, y);
    points.push_back(x);
    points.push_back(y);
    values.push_back(u);
  }

  // верхняя граница - значения
  int p_t = 100;
  for (int i = 0; i < p_t; i++) {
    double x = double(rand()) / RAND_MAX;
    double y = M_PI_2;
    double u = s(x, y);
    points.push_back(x);
    points.push_back(y);
    values.push_back(u);
  }

  // датчики
  int p_d = 10;
  for (int i = 0; i < p_d; i++) {
    double x = double(rand()) / RAND_MAX;
    double y = double(rand()) / RAND_MAX * M_PI_2;
    double u = s(x, y);
    points.push_back(x);
    points.push_back(y);
    values.push_back(u);
  }

  // точки проверки второй производной
  int p_l = 100;
  for (int i = 0; i < p_l; i++) {
    double x = double(rand()) / RAND_MAX;
    double y = double(rand()) / RAND_MAX * M_PI_2;
    double u = f(x, y);
    points_3.push_back(x);
    points_3.push_back(y);
    values_3.push_back(u);
  }
}

#include <iostream>
double ReverseWithCurvilinearBorders::operator()(vector<double> p) {
  double result = 0;
  MQ_2 nn(p);
  //  std::cout << "---------------------------------" << std::endl;
  for (int i = 0; i < values.size(); i++) {
    //std::cout << points[2 * i] << " " << points[2 * i + 1] << " " << values[i] << " " << nn.value(points[2 * i], points[2 * i + 1]) << std::endl;
    double tmp = values[i] - nn.value(points[2 * i], points[2 * i + 1]);
    result += 10.0 * tmp * tmp;
  }
  for (int i = 0; i < values_3.size(); i++) {
    double tmp = f(points_3[2 * i], points_3[2 * i + 1]) - nn.laplace(points_3[2 * i], points_3[2 * i + 1]);
    result += tmp * tmp;
  }
  return result;
}


vector<double> ReverseWithCurvilinearBorders::random_vector() {
  vector<double> result;
  for (int i = 0; i < _neurons; i++) {
    result.push_back(w_min + (w_max - w_min) * rand() / RAND_MAX);
    result.push_back(a_min + (a_max - a_min) * rand() / RAND_MAX);
    result.push_back(cx_min + (cx_max - cx_min) * rand() / RAND_MAX);
    result.push_back(cy_min + (cy_max - cy_min) * rand() / RAND_MAX);    
  }
  return result;
}


vector<double> ReverseWithCurvilinearBorders::crop(vector<double> p) {
  vector<double> result;
  for (int i = 0; i < 4 * _neurons; i++) {
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
  double y = 0.0;
  double x = 1.0;
  while (y < M_PI_2) {
    ss << y << " " << s(x, y) << " " << nn.value(x, y) << std::endl;
    y += 0.1;
  }
  ss << nn.report_value();
  return ss.str();
}
