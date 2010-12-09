#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "../../equationSL.h"

#define sqr(a) ((a)*(a))

/*
  RBF-MQ
*/

const int NEURONS = 20;
const int POINTS_INNER = 150;
const int ALL_POINTS = POINTS_INNER + 2;

const double DELTA = 10000;
const double ACCURACY = 1e-6;

const double W_MIN = -100;
const double W_MAX = 100;
const double C_X_MIN = left_x - 0.5;
const double C_X_MAX = right_x + 0.5;

double box_points[2 * NEURONS * 2][2 * NEURONS];
double test_points[ALL_POINTS][1];
double cached_values[2 * NEURONS * 2];

inline double calc_neuron(double *a, double x) 
{
  double x_d = fabs(x - a[1]);
 // return a[0] * sqr(x_d) * log(x_d);
 return a[0] * x_d*x_d*x_d;
}

double laplace(double *a, double x) 
{
  double res = 0.0;
  for (int i = 0; i < NEURONS; i++) 
  {
    double dx = fabs(x - a[2 * i + 1]);
    //res += a[2 * i] * (2.0 * log(dx) + 3.0);
    res += a[2*i] * 6.0 * dx;
  }
  return res;
}

double calc(double *a, double x) 
{
  double res = 0.0;
  for (int i = 0; i < NEURONS; ++i) 
  {
    res += calc_neuron(&a[i * 2], x);
  }
  return res;
}

void generate_test_points() 
{
  int i = 0;
  for (int j = 0; j < POINTS_INNER; i++,j++) 
  {
    test_points[i][0] = double(rand()) / RAND_MAX;
  }
  test_points[i++][0] = left_x;
  test_points[i][0] = right_x;
}

double J(double *a) 
{
  double res = 0.0;
  for (int i = 0; i < POINTS_INNER; i++) 
  {
    double U = calc(a, test_points[i][0]);
    double tmp = laplace(a, test_points[i][0]) - f(test_points[i][0], U);
    res += sqr(tmp);
  }
  res += DELTA * sqr(calc(a, left_x)) + DELTA*sqr(calc(a, right_x));
  return res;
}

void generate_box_points() 
{
  for (int c = 0; c < 2 * NEURONS * 2; c++) 
  { 
    for (int i = 0; i < NEURONS; i++) 
    {
      box_points[c][2 * i] = W_MIN + (W_MAX - W_MIN) * double(rand()) / RAND_MAX;
      box_points[c][2 * i + 1] = C_X_MIN + (C_X_MAX - C_X_MIN) * double(rand()) / RAND_MAX;
    }
  }
}

void fill_cache() {
  for (int i = 0; i < 2 * NEURONS * 2; i++) {
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
    for (int i = 0; i < 2 * NEURONS * 2; ++i) 
    {
      double tmp = cached_values[i];
      if (tmp > max_error) 
      {
        max_error = tmp;
        max_index = i;
      }
    }

    // Finding the centre of gravity
    double cog[2 * NEURONS] = {0};
    for (int i = 0; i < 2 * NEURONS; ++i) 
    {
      for (int j = 0; j < 2 * NEURONS * 2; ++j) 
      {
        if (j == max_index) continue;
        cog[i] += box_points[j][i];
      }
      cog[i] /= 2 * NEURONS * 2 - 1;
    }
    
    // End of calculations
    if (iteration % 100 == 0)
    {
      double sum = 0.0;
      double tmp = J(&cog[0]);
      for (int i = 0; i < 2 * NEURONS * 2; ++i) 
      {
        sum += sqr(tmp - cached_values[i]);
      }
      if (sqrt(sum) < ACCURACY) 
      {
        // Finding the best point
        int min_index = 0;
        double min_error = 1e307;
        for (int i = 0; i < 2 * NEURONS * 2; ++i) 
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
      double new_point[2 * NEURONS];
      for (int j = 0; j < 2 * NEURONS; ++j) 
      {
        new_point[j] = cog[j] + c * (cog[j] - box_points[max_index][j]);
        int type = j % 2;
        if (type == 0) 
        {
          if (new_point[j] < W_MIN) new_point[j] = W_MIN;
          else if (new_point[j] > W_MAX) new_point[j] = W_MAX;
        }
        else if (type == 1) 
        {
          if (new_point[j] < C_X_MIN) new_point[j] = C_X_MIN;
          else if (new_point[j] > C_X_MAX) new_point[j] = C_X_MAX;
        }
      }
      if (J(&new_point[0]) > max_error) 
      {
        c /= 2.0;
//         std::cerr << "Prereduction\n"; 
      }
      else 
      {
        good_point = true;
        for (int i = 0; i < 2 * NEURONS; i++) 
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
      std::cerr << "La redutcion comme\n";
      // Finding the best point
      int min_index = 0;
      double min_error = 1e307;
      for (int i = 0; i < 2 * NEURONS * 2; ++i) 
      {
        double tmp = cached_values[i];
        if (tmp < min_error) 
        {
          min_error = tmp;
          min_index = i;
        }
      }
      for (int i = 0; i < 2 * NEURONS * 2; ++i) 
      {
        for (int j = 0; j < 2 * NEURONS; ++j) 
        {
          box_points[i][j] = box_points[min_index][j] \
            + 0.5 * (box_points[i][j] - box_points[min_index][j]);
        }
        cached_values[i] = J(&box_points[i][0]);
      }
      double min_J = J(&box_points[0][0]);
      double max_J = J(&box_points[0][0]);
      for (int p=0; p < 2 * NEURONS * 2; p++) {
        double cJ = J(&box_points[p][0]);
        if (cJ < min_J) min_J = cJ;
        if (cJ > max_J) max_J = cJ;
      }
      if (max_J - min_J < 1e-6) {
        return 0;
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
  std::cout << "RBF-PLATE" << std::endl;
  for (int i=0; i < NEURONS; ++i) 
  {
    std::cout << box_points[p][i * 2] << " " << box_points[p][i * 2 + 1];
    std::cout << std::endl;
  }
  return 0;
}
