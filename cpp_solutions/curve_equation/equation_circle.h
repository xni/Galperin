#include <math.h>

const double left_x = -2.0;
const double right_x = 2.0;
const double bottom_y = -2.0;
const double top_y = 2.0;

const double left_derivative_factor = 0;
const double left_value_factor = 1;

const double right_derivative_factor = 0;
const double right_value_factor = 1;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

double solution(double x, double y)
{
   return x*x - y*y + 2*x*y - 3;
}

double inside_border(double x, double y)
{
    return x*x - y*y + 2*x*y - 3;
}

double outside_border(double x, double y)
{
    return x*x - y*y + 2*x*y - 3;
}

double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
