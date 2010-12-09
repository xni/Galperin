#include <math.h>

/* U(x, y) = cos(x) cos(y)

   U_x(x, y) = -sin(x) cos(y)
   U_y(x, y) = -cos(x) sin(y)

   U_xx(x, y) = -cos(x) cos(y)
   U_yy(x, y) = -cos(x) cos(y)

   U_xx + U_yy = -2 cos(x) cos(y)
   
   U_x(0, y) + U(0, y) = cos(y)
   U_x(Pi/2, y) + U(Pi/2, y) = -cos(y)
   U_y(x, 0) + U(x, 0) = cos(x)
   U_y(x, Pi/2) - U(x, Pi/2) = -cos(x)
*/

const double left_x = 0.0;
const double right_x = M_PI_2;
const double bottom_y = 0.0;
const double top_y = M_PI_2;

const double left_derivative_factor = 1;
const double left_value_factor = 1;

const double right_derivative_factor = 1;
const double right_value_factor = 1;

const double bottom_derivative_factor = 1;
const double bottom_value_factor = 1;

const double top_derivative_factor = 1;
const double top_value_factor = 0;

const bool use_sf_left = true;
const bool use_sf_right = true;
const bool use_sf_bottom = true;
const bool use_sf_top = false;


double solution(double x, double y)
{
  return cos(x) * cos(y);
}

double left_border(double y) {
  return cos(y); }

double right_border(double y) {
  return -cos(y); }

double top_border(double x) {
  return -cos(x); }

double bottom_border(double x) {
  return cos(x); }


double f(double x, double y, double U, double dUx, double dUy)
{
  return -2.0 * cos(x) * cos(y);
}
