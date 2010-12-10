#include <math.h>

const double left_x = -1.0;
const double right_x = 1.0;
const double bottom_y = -1.0;
const double top_y = 1.0;

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
   return x*x + y*y;
}

double border(double x, double y)
{
    return x*x + y*y;
}

double f(double x, double y, double U, double dUx, double dUy)
{
  return 4;
}
