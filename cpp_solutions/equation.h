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


ouble left_border(double y) {
  return cos(y); }

double right_border(double y) {
  return exp(1.0) * cos(y); }

double top_border(double x) {
  return -1.0 * exp(x); }

double bottom_border(double x) {
  return 0.0; }


double f(double x, double y)
{
  return 0;
}
