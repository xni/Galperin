#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "../../equation10.h"

#define sqr(a) ((a)*(a))

/*
  RBF-MQ
*/

const int NEURONS = 20;
const int POINTS_INNER = 200;
const int POINTS_BORDER = 50; // точек на каждой границе
const int ALL_POINTS = POINTS_INNER + 4 * POINTS_BORDER;

const double DELTA = 100;
const double ACCURACY = 1e-9;

const double W_MIN = -100;
const double W_MAX = 100;
const double A_MIN = 0.0;
const double A_MAX = right_x + top_y - left_x - bottom_y; 
const double C_X_MIN = left_x - 0.5;
const double C_X_MAX = right_x + 0.5;
const double C_Y_MIN = bottom_y - 0.5;
const double C_Y_MAX = top_y + 0.5;

double box_points[2 * NEURONS * 4][4 * NEURONS];
double test_points[ALL_POINTS][2];
double cached_values[2 * NEURONS * 4];

inline double calc_neuron(double *a, double x, double y) 
{
  double x_d = x - a[2];
  double y_d = y - a[3];
  double a_q = a[1];
  return a[0] * sqrt(sqr(x_d) + sqr(y_d) + sqr(a_q));
}

inline double MQ_sample(double *a, double x, double y)
{
  double x_d = x - a[2];
  double y_d = y - a[3];
  double a_q = a[1];
  return 1.0 / sqrt(sqr(x_d) + sqr(y_d) + sqr(a_q));
}

double derivative(double *a, double x, double y, int pos)
{
  double res = 0.0;
  for (int i = 0; i < NEURONS; ++i)
  {
    double mqs = MQ_sample(&a[4 * i], x, y);
    double dx = x - a[4 * i + 2];
    double dy = y - a[4 * i + 3];
    res += a[4 * i] * mqs * ((pos==1) ? (dx) : (dy));
  }
  return res;
}

double laplace(double *a, double x, double y) 
{
  double res = 0.0;
  for (int i = 0; i < NEURONS; i++) 
  {
    double mqs = MQ_sample(&a[4 * i], x, y);
    double dx = x - a[4 * i + 2];
    double dy = y - a[4 * i + 3];
    res += a[4 * i] * mqs * (2.0  -  sqr(dx) * sqr(mqs) - sqr(dy) * sqr(mqs));
  }
  return res;
}

double calc(double *a, double x, double y) 
{
  double res = 0.0;
  for (int i = 0; i < NEURONS; ++i) 
  {
    res += calc_neuron(&a[i * 4], x, y);
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
    test_points[i][0] = left_x;
    test_points[i][1] = double(rand()) / RAND_MAX;
  }
  for (int j = 0; j < POINTS_BORDER; i++,j++) 
  {
    test_points[i][0] = right_x;
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
}

double J(double *a) 
{
  double res = 0.0;
  for (int i = 0; i < POINTS_INNER; i++) 
  {
    double U = calc(a, test_points[i][0], test_points[i][1]);
    double dUx = derivative(a, test_points[i][0], test_points[i][1], 1);
    double dUy = derivative(a, test_points[i][0], test_points[i][1], 2);
    double tmp = laplace(a, test_points[i][0], test_points[i][1]) \
      - f(test_points[i][0], test_points[i][1], U, dUx, dUy);
    res += sqr(tmp);
  }
  for (int i = POINTS_INNER; i < POINTS_INNER + POINTS_BORDER; i++) 
  {
    double tmp;
    double x = test_points[i][0];
    double y = test_points[i][1];
    tmp = left_derivative_factor * derivative(a, x, y, 1) + left_value_factor * calc(a, x, y) - left_border(y);
    res += DELTA * sqr(tmp);
  }
  for (int i = POINTS_INNER + POINTS_BORDER; i < POINTS_INNER + 2 * POINTS_BORDER; i++) 
  {
    double tmp;
    double x = test_points[i][0];
    double y = test_points[i][1];
    tmp = right_derivative_factor * derivative(a, x, y, 1) + right_value_factor * calc(a, x, y) - right_border(y);
    res += DELTA * sqr(tmp);
  }
  for (int i = POINTS_INNER + 2 * POINTS_BORDER; i < POINTS_INNER + 3 * POINTS_BORDER; i++)
  {
    double tmp;
    double x = test_points[i][0];
    double y = test_points[i][1];
    tmp = bottom_derivative_factor * derivative(a, x, y, 2) + bottom_value_factor * calc(a, x, y) - bottom_border(x);
    res += DELTA * sqr(tmp);
  }
  for (int i = POINTS_INNER + 3 * POINTS_BORDER; i < POINTS_INNER + 4 * POINTS_BORDER; i++)
  {
    double tmp;
    double x = test_points[i][0];
    double y = test_points[i][1];
    tmp = top_derivative_factor * derivative(a, x, y, 2) + top_value_factor * calc(a, x, y) - top_border(x);
    res += DELTA * sqr(tmp);
  }
  return res;
}

void generate_box_points() 
{
  for (int c = 0; c < 2 * NEURONS * 4; c++) 
  { 
    for (int i = 0; i < NEURONS; i++) 
    {
      box_points[c][4 * i] = W_MIN + (W_MAX - W_MIN) * double(rand()) / RAND_MAX;
      box_points[c][4 * i + 1] = A_MIN + (A_MAX - A_MIN) * rand() / RAND_MAX;
      box_points[c][4 * i + 2] = C_X_MIN + (C_X_MAX - C_X_MIN) * double(rand()) / RAND_MAX;
      box_points[c][4 * i + 3] = C_Y_MIN + (C_Y_MAX - C_Y_MIN) * double(rand()) / RAND_MAX;
    }
  }
}

void fill_cache() {
  for (int i = 0; i < 2 * NEURONS * 4; i++) {
    cached_values[i] = J(&box_points[i][0]);
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
    for (int i = 0; i < 2 * NEURONS * 4; ++i) 
    {
      double tmp = cached_values[i];
      if (tmp > max_error) 
      {
        max_error = tmp;
        max_index = i;
      }
    }

    // Finding the centre of gravity
    double cog[4 * NEURONS] = {0};
    for (int i = 0; i < 4 * NEURONS; ++i) 
    {
      for (int j = 0; j < 2 * NEURONS * 4; ++j) 
      {
        if (j == max_index) continue;
        cog[i] += box_points[j][i];
      }
      cog[i] /= 2 * NEURONS * 4 - 1;
    }
    
    // End of calculations
    if (iteration % 100 == 0) 
    {
      double sum = 0.0;
      double tmp = J(&cog[0]);
      for (int i = 0; i < 2 * NEURONS * 4; ++i) 
      {
        sum += sqr(tmp - cached_values[i]);
      }
      if (sqrt(sum) < ACCURACY) 
      {
        // Finding the best point
        int min_index = 0;
        double min_error = 1e307;
        for (int i = 0; i < 2 * NEURONS * 4; ++i) 
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
      std::cerr << "Max error = " << max_error << std::endl;
    }
    
    // Box method
    double c = 1.3;
    bool good_point = false;
    for (int i = 0; i < 10; ++i) 
    {
      double new_point[4 * NEURONS];
      for (int j = 0; j < 4 * NEURONS; ++j) 
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
        for (int i = 0; i < 4 * NEURONS; i++) 
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
      for (int i = 0; i < 2 * NEURONS * 4; ++i) 
      {
        double tmp = cached_values[i];
        if (tmp < min_error) 
        {
          min_error = tmp;
          min_index = i;
        }
      }
      for (int i = 0; i < 2 * NEURONS * 4; ++i) 
      {
        for (int j = 0; j < 4 * NEURONS; ++j) 
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
  fill_cache();
  int p = box_method();
  /*  double E1 = 0.0;
  double E2 = 0.0;
  double EM = 0.0;
  for (double x = left_x; x <= right_x + 0.00001; x += 0.005)
  {
    for (double y = bottom_y; y <= top_y + 0.00001; y += 0.005)
    {
      double tmp = fabs(calc(&box_points[p][0], x, y) - solution(x, y));
      E1 += tmp;
      E2 += sqr(tmp);
      EM = (EM > tmp)?EM:tmp;
    }
    }*/
  //  std::cout << "Problem N\t" << NEURONS << "\t" << POINTS_INNER << "\t" << POINTS_BORDER << "\t" << DELTA << "\t" << cached_values[p] << "\t" << E1 << "\t" << E2 << "\t" << EM << std::endl;  
  std::cout << "RBF-MQ" << std::endl;
  for (int i=0; i < NEURONS; ++i) 
  {
    std::cout << box_points[p][i * 4] << " " << box_points[p][i * 4 + 1] << " " \
        << box_points[p][i * 4 + 2] << " " << box_points[p][i * 4 + 3];
    std::cout << std::endl;
  }
  return 0;
}
