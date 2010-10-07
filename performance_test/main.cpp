#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define sqr(a) ((a)*(a))

const int NEURONS = 3;
const int POINTS = 2400;

double box_points[2 * NEURONS * 4][4 * NEURONS];
double test_points[POINTS][2];

double calc(double *a, double x, double y)
{
    double res = 0.0;
    for (int i=0; i<NEURONS; ++i)
    {
        res += a[i * 4]* exp(-(sqr(x - a[i * 4 + 2]) + sqr(y - a[i * 4 + 3])) / sqr(a[i * 4 + 1]));
//         std::cout << x << " " << y << std::endl;
//         std::cout << a[i*4] << " "<< a[i*4+1] << " " << a[i*4+2] << " " << a[i*4+3] << std::endl; 
    }
    return res;
}

void generate_test_points()
{
    for (int i=0; i<POINTS; ++i)
    {
        test_points[i][0] = double(rand()) / RAND_MAX;
        test_points[i][1] = double(rand()) / RAND_MAX;
    }
}

void generate_box_points()
{
    for (int i=0; i<2 * NEURONS * 4; ++i)
    {
        for (int j=0; j<NEURONS; ++j)
        {
            box_points[i][4 * j] = 100.0 * double(rand()) / RAND_MAX;
            box_points[i][4 * j + 1] = 0.3 + 1.7 * double(rand()) / RAND_MAX;
            box_points[i][4 * j + 2] = double(rand()) / RAND_MAX;
            box_points[i][4 * j + 3] = double(rand()) / RAND_MAX;
        }
    }
}

double J(double *a)
{
    double secret_value[] = {21.0, 0.5, 0.23, 0.88, 67.0, 0.8, 0.5, 0.5, 74.0, 1.3, 0.79, 0.12};
    double res = 0.0;
    for (int i=0; i<POINTS; ++i)
    {
        res += fabs(calc(a, test_points[i][0], test_points[i][1]) - calc(&secret_value[0], test_points[i][0], test_points[i][1]));
    }
//     std::cout << "res is " << res << std::endl;
    return res;
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
            double tmp = J(&box_points[i][0]);
            if (tmp > max_error)
            {
                max_error = tmp;
                max_index = i;
            }
        }
        std::cout << "Max error = " << max_error << std::endl;
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
        if (iteration % 1000 == 0)
        {
            double sum = 0.0;
            for (int i=0; i<2*NEURONS*4; ++i)
            {
                sum += sqr(J(&cog[0]) - J(&box_points[i][0]));
            }
            if (sqrt(sum) < 1e-9)
            {
                // Finding the best point
                int min_index = 0;
                double min_error = 1e307;
                for (int i=0; i<2*NEURONS*4; ++i)
                {
                    double tmp = J(&box_points[i][0]);
                    if (tmp < min_error)
                    {
                        min_error = tmp;
                        min_index = i;
                    }
                }
                return min_index;
            }
        }

        // Box method
        double c = 1.3;
        bool good_point = false;
        for (int i=0; i<100; ++i)
        {
            double new_point[4*NEURONS];
            for (int j=0; j<4*NEURONS; ++j)
            {
                new_point[j] = cog[j] + c * (cog[j] - box_points[max_index][j]);
                int type = j % 4;
                if (type == 0)
                {
                    if (new_point[j] < 0.0) new_point[j] = 0.0;
                    if (new_point[j] > 100.0) new_point[j] = 100.0;
                }
                else if (type == 1)
                {
                    if (new_point[j] < 0.1) new_point[j] = 0.1;
                    if (new_point[j] > 2.0) new_point[j] = 2.0;
                }
                else
                {
                    if (new_point[j] < 0.0) new_point[j] = 0.0;
                    if (new_point[j] > 1.0) new_point[j] = 1.0;
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
                break;
            }
        }
        // Редукция
        if (!good_point)
        {
            // Finding the best point
            int min_index = 0;
            double min_error = 1e307;
            for (int i=0; i<2*NEURONS*4; ++i)
            {
                double tmp = J(&box_points[i][0]);
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
            }
        }
    }
}

int main()
{
    srand(time(0));
    generate_box_points();
    generate_test_points();
    std::cout << std::setprecision(10);
    int p = box_method();
    for (int i=0; i<4*NEURONS; ++i)
        std::cout << box_points[p][i] << " ";
    std::cout << std::endl;
    return 0;
}
