#include <math.h>

const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = 3.14159265358979 / 2.0;

const bool border_derivatives[] = {false, false, true, true};

double solution(double x, double y)
{
   return exp(x) * cos(y);
}

double borders_func(double x, double y)
{
  if (x == left_x) return cos(y);
  if (x == right_x) return exp(1.0) * cos(y);
  if (y == bottom_y) return 0;
  if (y == top_y) return -1.0 * exp(x);
}

double f(double x, double y)
{
  return 0;
}
