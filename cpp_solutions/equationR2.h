#include <math.h>

const double left_x = 0.0;
const double right_x = 1.0;
const double bottom_y = 0.0;
const double top_y = 1.0;

const double left_derivative_factor = 0;
const double left_value_factor = 1;

const double right_derivative_factor = 0;
const double right_value_factor = 1;

const double bottom_derivative_factor = 0;
const double bottom_value_factor = 1;

const double top_derivative_factor = 0;
const double top_value_factor = 1;

double left_border(double y) {
  return 0; }

double right_border(double y) {
  return 0; }

double top_border(double x) {
  return 0; }

double bottom_border(double x) {
  return 0; }


#define max(a, b) ((a) > (b)) ? (a) : (b)

double f(double x, double y, double U, double dUx, double dUy)
{
  return max(0, 1.0 - 2*fabs(x - 0.5) - 2*fabs(y - 0.5));
}
