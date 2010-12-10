#include <math.h>

const double left_x = 0.0;
const double right_x = 0.5;
const double bottom_y = 0.0;
const double top_y = (sqrt(2.0) - 1.0) / 2.0;

const double left_derivative_factor = 0;
const double left_value_factor = 1;

const double right_derivative_factor = 0;
const double right_value_factor = 1;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

const double P_const = top_y;

double solution(double x, double y)
{
   return x*x - y*y + P_const*P_const;
}

double left_border(double y)
{
    return P_const*P_const - y*y;
}

double bottom_border(double x)	
{
    return x*x + P_const*P_const;
}

double top_border(double x)
{
    return x*x*(x + 2.0*P_const*P_const);
}

double f(double x, double y, double U, double dUx, double dUy)
{
  return 0;
}
