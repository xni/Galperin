#include <math.h>

const double left_x = 0.0;
const double right_x = 5.0;
const double bottom_y = 0.0;
const double top_y = 2.0;

const double left_derivative_factor = 0;
const double left_value_factor = 1;

const double right_derivative_factor = 0;
const double right_value_factor = 1;

const double bottom_derivative_factor = 1;
const double bottom_value_factor = 0;

const double top_derivative_factor = 1;
const double top_value_factor = 0;

const bool use_sf_left = true;
const bool use_sf_right = true;
const bool use_sf_bottom = true;
const bool use_sf_top = false;


double left_border(double y) {
  return 0.0; }

double right_border(double y) {
  return 0.0; }

double top_border(double x) {
  return (x <= 1) ? sin(x * M_PI_2) * 3 : 3 * cos((x - 1.0) / 4.0 * M_PI_2); }

double bottom_border(double x) {
  return 0.0; }


double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
