#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

#define sqr(a) ((a)*(a))

const int NEURONS = 7;
const int SIDE = 30;
const int POINTS = 4 + sqr(SIDE);

double box_points[2 * NEURONS * 4][4 * NEURONS];
double test_points[POINTS][2];
double cached_values[2 * NEURONS * 4];


double borders_func(double x, double y) {
  return sin(M_PI * x) + y;
}


inline double calc_neuron(double *a, double x, double y) {
  double x_d = x - a[2];
  double y_d = y - a[3];
  double a_q = a[1];
  return a[0]* exp(-(sqr(x_d) + sqr(y_d)) / sqr(a_q));
}


double calc_derivative(double *a, int n, double x, double y) {
  double res = 0.0;
  for (int i = 0; i < n; i++) {
    res += -2.0 * calc_neuron(&a[4 * i], x, y) / sqr(a[i * 4 + 1]) +
      4.0 * calc_neuron(&a[4 * i], x, y) * sqr(x - y) / sqr(sqr(a[i * 4 + 1]));
  }
}

double calc(double *a, int n, double x, double y)
{
    double res = 0.0;
    for (int i=0; i<n; ++i)
    {
      double x_d = x - a[i * 4 + 2];
      double y_d = y - a[i * 4 + 3];
      double a_q = a[i * 4 + 1];
      res += a[i * 4]* exp(-(sqr(x_d) + sqr(y_d)) / sqr(a_q));
    }
    return res;
}

void generate_test_points()
{
  const double step = 1.0 / (SIDE - 1);
    for (int i=0; i<SIDE; ++i)
    {
        for (int j=0; j<SIDE; ++j)
        {
	  test_points[i * SIDE + j][0] = step * i;
	  test_points[i * SIDE + j][1] = step * j;
        }
    }
}

double J(double *a)
{
    double res = 0.0;
    for (int i=0; i<POINTS; ++i)
    {
      if (test_points[i][0] == 0.0 || test_points[i][1] == 0.0 || test_points[i][0] == 1.0 || test_points[i][1] == 1.0) {
	double tmp =  calc(a, NEURONS, test_points[i][0], test_points[i][1]) - borders_func(test_points[i][0], test_points[i][1]);
	res += sqr(tmp);
      } else {
	double tmp = calc_derivative(a, NEURONS, test_points[i][0], test_points[i][1]);
	res += 800 * sqr(tmp);
      }
    }
    return res;
}

void generate_box_points()
{
    for (int c = 0; c < 2 * NEURONS * 4; c++)
    { 
        for (int i = 0; i < NEURONS; i++)
        {
            box_points[c][4 * i] = -100.0 + 200.0 * double(rand()) / RAND_MAX;
            box_points[c][4 * i + 1] = 0.3 + 1.7 * rand() / RAND_MAX;
            box_points[c][4 * i + 2] = -0.5 + 2.0 * double(rand()) / RAND_MAX;
            box_points[c][4 * i + 3] = -0.5 + 2.0 * double(rand()) / RAND_MAX;
        }
    }
}

int iteration = 0;

int box_method()
{
    while (true)
    {
        ++iteration;
        // Finding the worst point
        int max_index = 0;
        double max_error = 0.0;
        for (int i=0; i<2*NEURONS*4; ++i)
        {
            //double tmp = J(&box_points[i][0]);
            double tmp = cached_values[i];
            if (tmp > max_error)
            {
                max_error = tmp;
                max_index = i;
            }
        }
	//        std::cout << "Max error = " << max_error << std::endl;
        // Finding the centre of gravity
        double cog[4 * NEURONS] = {0};
        for (int i=0; i<4*NEURONS; ++i)
        {
            for (int j=0; j<2*NEURONS*4; ++j)
            {
                if (j == max_index) continue;
                cog[i] += box_points[j][i];
            }
            cog[i] /= 2*NEURONS*4 - 1;
        }

        // End of calculations
        if (iteration % 100 == 0)
        {
            double sum = 0.0;
            double tmp = J(&cog[0]);
            for (int i=0; i<2*NEURONS*4; ++i)
            {
                //sum += sqr(J(&cog[0]) - J(&box_points[i][0]));
                sum += sqr(tmp - cached_values[i]);
            }
            if (sqrt(sum) < 1e-7)
            {
                // Finding the best point
                int min_index = 0;
                double min_error = 1e307;
                for (int i=0; i<2*NEURONS*4; ++i)
                {
//                     double tmp = J(&box_points[i][0]);
                    double tmp = cached_values[i];
                    if (tmp < min_error)
                    {
                        min_error = tmp;
                        min_index = i;
                    }
                }
                std::cout << min_error << std::endl;
                return min_index;
            }
            std::cout << "Max error = " << max_error << std::endl;
        }

        // Box method
        double c = 1.3;
        bool good_point = false;
        for (int i=0; i<10; ++i)
        {
            double new_point[4*NEURONS];
            for (int j=0; j<4*NEURONS; ++j)
            {
                new_point[j] = cog[j] + c * (cog[j] - box_points[max_index][j]);
                int type = j % 4;
                if (type == 0)
                {
                    if (new_point[j] < -100.0) new_point[j] = -100.0;
                    if (new_point[j] > 100.0) new_point[j] = 100.0;
                }
                else if (type == 1)
                {
                    if (new_point[j] < 0.3) new_point[j] = 0.3;
                    if (new_point[j] > 2.0) new_point[j] = 2.0;
                }
                else
                {
                    if (new_point[j] < -0.5) new_point[j] = -0.5;
                    if (new_point[j] > 1.5) new_point[j] = 1.5;
                }
            }
            if (J(&new_point[0]) > max_error)
            {
                c /= 2.0;
            }
            else
            {
                good_point = true;
                for (int i=0; i<4*NEURONS; i++)
                {
                    box_points[max_index][i] = new_point[i];
                }
                cached_values[max_index] = J(&box_points[max_index][0]);
                break;
            }
        }
        // Редукция
        if (!good_point)
        {
            // Finding the best point
            //std::cout << "Reduction" << std::endl;
            int min_index = 0;
            double min_error = 1e307;
            for (int i=0; i<2*NEURONS*4; ++i)
            {
//                 double tmp = J(&box_points[i][0]);
                double tmp = cached_values[i];
                if (tmp < min_error)
                {
                    min_error = tmp;
                    min_index = i;
                }
            }
            for (int i=0; i<2*NEURONS*4; ++i)
            {
                for (int j=0; j<4*NEURONS; ++j)
                {
                    box_points[i][j] = box_points[min_index][j] + 0.5 * (box_points[i][j] - box_points[min_index][j]);
                }
                cached_values[i] = J(&box_points[i][0]);
            }
        }
    }
}

int main()
{
    srand(time(0));
    generate_box_points();
    generate_test_points();
//    std::cout << std::ios::fixed << std::setprecision(10);
    int p = box_method();
    for (int i=0; i<4*NEURONS; ++i)
        std::cout << box_points[p][i] << " ";
    std::cout << std::endl;
    return 0;
}
