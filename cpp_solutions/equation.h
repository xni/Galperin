const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = 1.0;

double borders_func(double x, double y)
{
  if (x == left_x) return y * y;
  if (x == right_x) return exp(y) + 1.0 - y;
  if (y == bottom_y) return 2.0 * x;
  if (y == top_y) return exp(x);
}

double f(double x, double y)
{
  return 0.0;
}
