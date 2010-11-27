#include <math.h>

const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = M_PI_2;

const double left_derivative_factor = 1;
const double left_value_factor = 0;

const double right_derivative_factor = 1;
const double right_value_factor = -1;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

double solution(double x, double y)
{
  return x * cos(y);
}

double left_border(double y) {
  return cos(y); }

double right_border(double y) {
  return 0; }

double bottom_border(double x) {
  return x; }

double top_border(double x) {
  return 0; }


double f(double x, double y, double U, double dUx, double dUy)
{
  return -U;
}
