#include <math.h>

const double left_x = 0.0;
const double right_x = 0.5;
const double bottom_y = 0.5;
const double top_y = sqrt(2.0) / 2.0;

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
   return x*x - y*y;
}

double left_border(double y)
{
    return 0.5 - y*y;
}

double bottom_border(double x)
{
    return x*x + 0.25;
}

double top_border(double x)
{
    return 2.0*x*x;
}

double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
