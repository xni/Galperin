#include <math.h>

const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = 1.0;

const bool border_derivatives[] = {false, false, false, false};

double borders_func(double x, double y)
{
  return x + y;
}

double f(double x, double y)
{
  return 0;
}
