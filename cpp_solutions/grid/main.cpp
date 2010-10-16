#include <iostream>
#include <cmath>
#include <iomanip>

const double left_x = 0.0;
const double bottom_y = 0.0;
const double right_x = 1.0;
const double top_y = 1.0;

const int grid_size = 150; // число точек

const double step_x = (right_x - left_x) / (grid_size - 1);
const double step_y = (top_y - bottom_y) / (grid_size - 1);

const double EPS = 1e-7;
const double TAU = 0.56;

double border(double x, double y)
{
  if (x == left_x) return y * y;
  if (x == right_x) return exp(y) + 1.0 - y;
  if (y == bottom_y) return 2.0 * x;
  if (y == top_y) return exp(x);
}


double f(double x, double y)
{
  return 3.0;
}


double norm(double A[][grid_size], double B[][grid_size])
{
  double res = 0;
  for (int i = 1; i < grid_size - 1; i++)
    {
      for (int j = 1; j < grid_size - 1; j++)
	{
	  res = std::max(res, fabs(A[i][j] - B[i][j]));
	}
    }
  return res;
}


int main(int arcg, char* argv[])
{
  double A[grid_size][grid_size], B[grid_size][grid_size];

  // записываем начальные значения в матрицы A и B
  for (int i = 0; i < grid_size; i++)
    {
      A[0][i] = border(left_x, bottom_y + i * step_y);
      A[grid_size - 1][i] = border(right_x, bottom_y + i * step_y);
      A[i][0] = border(left_x + i * step_x, bottom_y);
      A[i][grid_size - 1] = border(left_x + i * step_x, top_y);

      B[0][i] = A[0][i];
      B[grid_size - 1][i] = A[grid_size - 1][i];
      B[i][0] = A[i][0];
      B[i][grid_size - 1] = A[i][grid_size - 1];
    }

  // интерполяция :-)
  for (int i = 1; i < grid_size - 1; i++)
    {
      for (int j = 1; j < grid_size - 1; j++)
	{
	  A[i][j] = 0;
	}
    }
  
  B[1][1] += 2 * EPS;

  while(norm(A, B) > EPS)
    {
      for (int i = 1; i < grid_size - 1; i++)
	{
	  for (int j = 1; j < grid_size - 1; j++)
	    {
	      A[i][j] = B[i][j];
	    }
	}
      
      for (int i = 1; i < grid_size - 1; i++)
	{
	  for (int j = 1; j < grid_size - 1; j++)
	    {
	      B[i][j] = TAU * (B[i - 1][j] + B[i][j - 1] + A[i + 1][j] + A[i][j + 1] - 4.0 * (1.0 - 1.0 / TAU) * A[i][j] \
			       + step_x * step_y * f(left_x + step_x * i, bottom_y + step_y * j)) / 4.0;
	    }
	}
    }

  std::cout << grid_size << std::endl;
  for (int j = 0; j < grid_size; j++)
    {
      for (int i = 0; i < grid_size; i++)
	{
	  std::cout << std::setw(14) << left_x + i * step_x << std::setw(14) << bottom_y + j * step_y << std::setw(14) << B[i][j] << std::endl;
	}
    }
  return 0;
}
