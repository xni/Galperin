#include <math.h>

const double left_x = 0.0;
const double right_x = M_PI_2;
const double bottom_y = 0.0;
const double top_y = 1.0;

const double left_derivative_factor = 1;
const double left_value_factor = 0;

const double right_derivative_factor = 1;
const double right_value_factor = 0;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

double solution(double x, double y)
{
  return exp(y) * sin(x);
}


double left_border(double y) {
  return exp(y); }

double right_border(double y) {
  return 0; }

double bottom_border(double x) {
  return sin(x); }

double top_border(double x) {
  return exp(1.0) * sin(x); }


double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
