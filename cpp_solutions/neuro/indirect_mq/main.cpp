#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "../../equation.h"

#define sqr(a) ((a)*(a))

/*
  RBF-INDIRECT-MQ
*/

const int NEURONS = 10;
const int P = 5;                // Для апроксимации функций Ci
const int POINTS_INNER = 200;
const int POINTS_BORDER = 50; // точек на каждой границе
const int ALL_POINTS = POINTS_INNER + 4 * POINTS_BORDER;

const double DELTA = 1000;

const double W_MIN = -100;
const double W_MAX = 100;
const double A_MIN = 0.0;
const double A_MAX = 3.0;
const double C_X_MIN = -0.5;
const double C_X_MAX = 1.5;
const double C_Y_MIN = -0.5;
const double C_Y_MAX = 1.5;

const int NEURAL_DIMENSION = 4 * (2 * NEURONS + 4 * P);
// Uxx Uyy C1 C2 C3 C4

double box_points[2 * NEURAL_DIMENSION][NEURAL_DIMENSION];
double test_points[ALL_POINTS][2];
double cached_values[2 * NEURAL_DIMENSION];

inline double calc_neuron(double *a, double x, double y) 
{
  double x_d = x - a[2];
  double y_d = y - a[3];
  double a_q = a[1];
  return a[0] * sqrt(sqr(x_d) + sqr(y_d) + sqr(a_q));
}

double calc_Uxx(double *a, double x, double y)   // Вторая производная по х
{
  double res = 0.0;
  for (int i = 0; i < NEURONS; ++i)
  {
      res += calc_neuron(&a[4 * i], x, y);
  }
  return res;
}

double calc_Uyy(double *a, double x, double y)   // Вторая производная по y
{
  double res = 0.0;
  for (int i = NEURONS; i < 2 * NEURONS; ++i)
  {
      res += calc_neuron(&a[4 * i], x, y);
  }
  return res;
}

double calc_U1(double *a, double x, double y)
{
  double res = 0;
  for (int i = 0; i < NEURONS; ++i)
  {
      double r2 = sqr(x - a[4 * i + 2]) + sqr(y - a[4 * i + 3]);
      double dx = x - a[4 * i + 2];
      double a2 = sqr(a[4 * i + 1]);
      res += a[4 * i] * (pow((r2 + a2), 1.5) / 6.0 +			\
			 0.5 * (r2 - sqr(dx) + a2) * (dx * log(dx + sqrt(r2 + a2)) - sqrt(r2 + a2)));
  }
  for (int i = 2 * NEURONS; i < 2 * NEURONS + P; ++i)
  {
      res += x * calc_neuron(&a[4 * i], x, y);
  }
  for (int i = 2 * NEURONS + P; i < 2 * NEURONS + 2 * P; ++i)
  {
      res += calc_neuron(&a[4 * i], x, y);
  }
  return res;
}

double calc_U2(double *a, double x, double y)
{
  double res = 0;
  for (int i = NEURONS; i < 2 * NEURONS; ++i)
  {
      double r2 = sqr(x - a[4 * i + 2]) + sqr(y - a[4 * i + 3]);
      double dy = y - a[4 * i + 3];
      double a2 = sqr(a[4 * i + 1]);
      res += a[4 * i] * (pow((r2 + a2), 1.5) / 6.0 +			\
			 0.5 * (r2 - sqr(dy) + a2) * (dy * log(dy + sqrt(r2 + a2)) - sqrt(r2 + a2)));
  }
  for (int i = 2 * NEURONS + 2 * P; i < 2 * NEURONS + 3 * P; ++i)
  {
      res += y * calc_neuron(&a[4 * i], x, y);
  }
  for (int i = 2 * NEURONS + 3 * P; i < 2 * NEURONS + 4 * P; ++i)
  {
      res += calc_neuron(&a[4 * i], x, y);
  }
  return res;
}

void generate_test_points() 
{
  int i = 0;
  for (int j = 0; j < POINTS_INNER; i++,j++) 
  {
    test_points[i][0] = double(rand()) / RAND_MAX;
    test_points[i][1] = double(rand()) / RAND_MAX;
  }
  for (int j = 0; j < POINTS_BORDER; i++,j++) 
  {
    test_points[i][0] = double(rand()) / RAND_MAX;
    test_points[i][1] = bottom_y;
  }
  for (int j = 0; j < POINTS_BORDER; i++,j++) 
  {
    test_points[i][0] = double(rand()) / RAND_MAX;
    test_points[i][1] = top_y;
  }
  for (int j = 0; j < POINTS_BORDER; i++,j++) 
  {
    test_points[i][0] = left_x;
    test_points[i][1] = double(rand()) / RAND_MAX;
  }
  for (int j = 0; j < POINTS_BORDER; i++,j++) 
  {
    test_points[i][0] = right_x;
    test_points[i][1] = double(rand()) / RAND_MAX;
  }
}

double J(double *a) 
{
  double res = 0.0;
  for (int i = 0; i < POINTS_INNER; i++) 
  {
    double x = test_points[i][0];
    double y = test_points[i][1];
    double tmp = calc_Uxx(a, x, y) + calc_Uyy(a, x, y) - f(x, y);
    res += sqr(tmp);
    tmp = calc_U1(a, x, y) - calc_U2(a, x, y);
    res += 10*sqr(tmp);
  }
  for (int i = POINTS_INNER; i < ALL_POINTS; i++) 
  {
    double x = test_points[i][0];
    double y = test_points[i][1];
    double tmp = calc_U1(a, x, y) - borders_func(x, y);
    //std::cerr << "On border diff " << tmp << std::endl;
    res += DELTA * sqr(tmp);
  }
  return res;
}

void generate_box_points() 
{
  for (int c = 0; c < 2 * NEURAL_DIMENSION; c++) 
  { 
    for (int i = 0; i < 2 * NEURONS + 4 * P ; i++) 
    {
      box_points[c][4 * i] = W_MIN + (W_MAX - W_MIN) * double(rand()) / RAND_MAX;
      box_points[c][4 * i + 1] = A_MIN + (A_MAX - A_MIN) * rand() / RAND_MAX;
      box_points[c][4 * i + 2] = C_X_MIN + (C_X_MAX - C_X_MIN) * double(rand()) / RAND_MAX;
      box_points[c][4 * i + 3] = C_Y_MIN + (C_Y_MAX - C_Y_MIN) * double(rand()) / RAND_MAX;
    }
  }
}

int iteration = 0;

int box_method() 
{
  while (true) 
  {
    ++iteration;
    // Finding the worst point
    int max_index = 0;
    double max_error = 0.0;
    for (int i = 0; i < 2 * NEURAL_DIMENSION; ++i) 
    {
      double tmp = cached_values[i];
      if (tmp > max_error) 
      {
        max_error = tmp;
        max_index = i;
      }
    }

    // Finding the centre of gravity
    double cog[NEURAL_DIMENSION] = {0};
    for (int i = 0; i < NEURAL_DIMENSION; ++i) 
    {
      for (int j = 0; j < 2 * NEURAL_DIMENSION; ++j) 
      {
        if (j == max_index) continue;
        cog[i] += box_points[j][i];
      }
      cog[i] /= 2 * NEURAL_DIMENSION - 1;
    }
    
    // End of calculations
    if (iteration % 100 == 0) 
    {
      double sum = 0.0;
      double tmp = J(&cog[0]);
      for (int i = 0; i < 2 * NEURAL_DIMENSION; ++i) 
      {
        sum += sqr(tmp - cached_values[i]);
      }
      if (sqrt(sum) < 1e-7) 
      {
        // Finding the best point
        int min_index = 0;
        double min_error = 1e307;
        for (int i = 0; i < 2 * NEURAL_DIMENSION; ++i) 
        {
          double tmp = cached_values[i];
          if (tmp < min_error) 
          {
            min_error = tmp;
            min_index = i;
          }
        }
      return min_index;
      }
      std::cerr << "Max error = " << std::setprecision(15) << max_error << std::endl;
    }
    
    // Box method
    double c = 1.3;
    bool good_point = false;
    for (int i = 0; i < 10; ++i) 
    {
      double new_point[NEURAL_DIMENSION];
      for (int j = 0; j < NEURAL_DIMENSION; ++j) 
      {
        new_point[j] = cog[j] + c * (cog[j] - box_points[max_index][j]);
        int type = j % 4;
        if (type == 0) 
        {
          if (new_point[j] < W_MIN) new_point[j] = W_MIN;
          else if (new_point[j] > W_MAX) new_point[j] = W_MAX;
        }
        else if (type == 1) 
        {
          if (new_point[j] < A_MIN) new_point[j] = A_MIN;
          else if (new_point[j] > A_MAX) new_point[j] = A_MAX;
        }
        else if (type == 2) 
        {
          if (new_point[j] < C_X_MIN) new_point[j] = C_X_MIN;
          else if (new_point[j] > C_X_MAX) new_point[j] = C_X_MAX;
        }
        else if (type == 3) 
        {
          if (new_point[j] < C_Y_MIN) new_point[j] = C_Y_MIN;
          else if (new_point[j] > C_Y_MAX) new_point[j] = C_Y_MAX;
        }
      }
      if (J(&new_point[0]) > max_error) 
      {
        c /= 2.0;
      }
      else 
      {
        good_point = true;
        for (int i = 0; i < NEURAL_DIMENSION; i++) 
        {
          box_points[max_index][i] = new_point[i];
        }
        cached_values[max_index] = J(&box_points[max_index][0]);
        break;
      }
    }
    
    // Редукция
    if (!good_point) 
    {
      // Finding the best point
      int min_index = 0;
      double min_error = 1e307;
      for (int i = 0; i < 2 * NEURAL_DIMENSION; ++i) 
      {
        double tmp = cached_values[i];
        if (tmp < min_error) 
        {
          min_error = tmp;
          min_index = i;
        }
      }
      for (int i = 0; i < 2 * NEURAL_DIMENSION; ++i) 
      {
        for (int j = 0; j < NEURAL_DIMENSION; ++j) 
        {
          box_points[i][j] = box_points[min_index][j] \
            + 0.5 * (box_points[i][j] - box_points[min_index][j]);
        }
        cached_values[i] = J(&box_points[i][0]);
      }
    }
  }
}

int main() 
{
  srand(time(0));
  generate_box_points();
  generate_test_points();
  int p = box_method();
  std::cout << "RBF-INDIRECT-MQ" << std::endl;
  for (int i = 0; i < 2 * NEURONS + 4 * P; ++i) 
  {
    std::cout << box_points[p][i * 4] << " " << box_points[p][i * 4 + 1] << " " \
        << box_points[p][i * 4 + 2] << " " << box_points[p][i * 4 + 3];
    std::cout << std::endl;
  }

  for (double i = 0.0; i <= 1.00001; i+=0.1) {
    for (double j = 0.0; j <= 1.00001; j+=0.1) {
      std::cerr << calc_U1(&box_points[p][0], i, j) << " ";
    }
    std::cerr << std::endl;
  }
  return 0;
}
