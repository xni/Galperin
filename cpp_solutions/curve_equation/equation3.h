#include <math.h>

const double left_x = 1.0;
const double right_x = (sqrt(2.0) + 1.0) / 2.0;
const double bottom_y = 0.0;
const double top_y = 0.5;

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
   return x*x - y*y - 1;
}

double bottom_border(double y)
{
    return 2.0 * (sqrt(2.0) - 1.0) * y * y;
}

double right_border(double x)
{
    return x*x - 1.0;
}

double top_border(double y)
{
    return (2.0 * sqrt(2.0) - 1.0) / 4.0 - y*y;
}

double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
