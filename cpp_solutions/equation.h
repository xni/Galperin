#include <math.h>

const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = 1.0;

double borders_func(double x, double y)
{
  return 0;
  if (x == left_x) return 0;
  if (x == right_x) return 1 - y * y;
  if (y == bottom_y) return 0;
  if (y == top_y) return x * x - 1;
}

double f(double x, double y)
{
  return sin(M_PI * x) * sin(M_PI * y);
  return 0;
}
