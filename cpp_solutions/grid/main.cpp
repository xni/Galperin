#include <iostream>
#include <cmath>
#include "../equation.h"

const int grid_size = 50; // число точек

const double step_x = (right_x - left_x) / (grid_size - 1);
const double step_y = (top_y - bottom_y) / (grid_size - 1);

const double EPS = 1e-9;

double norm(double A[][grid_size], double B[][grid_size]) {

}


int main(int arcg, char* argv[]) {
  double A[grid_size][grid_size], B[grid_size][grid_size];

  // записываем начальные значения в матрицы A и B
  for (int i = 0; i < grid_size; i++) {
      A[0][i] = borders_func(left_x, bottom_y + i * step_y);
      A[grid_size - 1][i] = borders_func(right_x, bottom_y + i * step_y);
      A[i][0] = borders_func(left_x + i * step_x, bottom_y);
      A[i][grid_size - 1] = borders_func(left_x + i * step_x, top_y);

      B[0][i] = A[0][i];
      B[grid_size - 1][i] = A[grid_size - 1][i];
      B[i][0] = A[i][0];
      B[i][grid_size - 1] = A[i][grid_size - 1];
    }

  // интерполяция :-)
  for (int i = 1; i < grid_size - 1; i++) {
      for (int j = 1; j < grid_size - 1; j++) {
	  A[i][j] = 0;
	}
    }

  B[1][1] += 2 * EPS;
  
  while(true) {
    double res = 0.0;
    for (int i = 1; i < grid_size - 1; i++) {
      for (int j = 1; j < grid_size - 1; j++) {
	res = std::max(res, fabs(A[i][j] - B[i][j]));
      }
    }
    if (res < EPS) {
      break;
    }

    for (int i = 1; i < grid_size - 1; i++) {
      for (int j = 1; j < grid_size - 1; j++) {
	B[i][j] = A[i][j];
      }
    }
      
    for (int i = 1; i < grid_size - 1; i++) {
      for (int j = 1; j < grid_size - 1; j++) {
	A[i][j] = (A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1]) / 4.0 - \
		   step_x * step_y * f(left_x + step_x * i,
				       bottom_y + step_y * j) / 4.0;
      }
    }
  }

  std::cout << "Grid" << std::endl;
  std::cout << left_x << " " << right_x << " " << bottom_y << " " \
	    << top_y << std::endl;
  for (int j = grid_size - 1; j >= 0; j--) {
      for (int i = 0; i < grid_size; i++) {
	std::cout << A[i][j] << " ";
	}
      std::cout << std::endl;
    }
  return 0;
}
