#include <math.h>

const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = 1.0;

const double left_derivative_factor = 0;
const double left_value_factor = 1;

const double right_derivative_factor = 0;
const double right_value_factor = 1;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

const bool use_sf_left = true;
const bool use_sf_right = true;
const bool use_sf_bottom = true;
const bool use_sf_top = false;


double solution(double x, double y)
{
   return x + y;
}

double left_border(double y) {
  return y; }

double right_border(double y) {
  return 1.0 + y; }

double top_border(double x) {
  return 1.0 + x; }

double bottom_border(double x) {
  return x; }


double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
