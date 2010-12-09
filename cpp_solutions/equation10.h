#include <math.h>

const double left_x = 0.0;
const double right_x = M_PI_2;
const double bottom_y = 0.0;
const double top_y = M_PI_2;

const double left_derivative_factor = 0;
const double left_value_factor = 1;

const double right_derivative_factor = 0;
const double right_value_factor = 1;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

const bool use_sf_left = false;
const bool use_sf_right = true;
const bool use_sf_bottom = true;
const bool use_sf_top = true;


double solution(double x, double y)
{
  return exp(-x - y) * cos(x) * cos(y);
}


double left_border(double y) {
  return exp(-y) * cos(y); }

double right_border(double y) {
  return 0; }

double bottom_border(double x) {
  return exp(-x) * cos(x); }

double top_border(double x) {
  return 0; }


double f(double x, double y, double U, double dUx, double dUy)
{
  return -2.0 * dUx - 2.0 * dUy - 4.0 * U;
}
