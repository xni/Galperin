#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector< vector< double > > Matrix;
typedef vector< double > Vector;
    
void init(Matrix &m, int s1, int s2) // Initialization
{
    Vector tmp;
    for (int i = 0; i < s2; ++i)
        tmp.push_back(0.0);
    for (int i = 0; i < s1; ++i)
        m.push_back(tmp);
}

void start_values(Matrix &m, double step_x, double step_y, int steps_x, int steps_y) // Start values of U(x,y)
{
    for (int i = 0; i <= steps_x; ++i)
    {
        m[i][0] = sin(M_PI * i * step_x);
        m[i][steps_y] = sin(M_PI * i * step_x) + 1.0;
    }
    
    for (int j = 0; j <= steps_y; ++j)
    {
        m[0][j] = j * step_y;
        m[steps_x][j] = j * step_y;
    }
}

void interpolation(Matrix &m, double step_x, double step_y, int steps_x, int steps_y) // Linear interpolation of ending values
{
    for (int j = 1; j < steps_y; ++j)
        for (int i = 1; i < steps_x; ++i)
            m[i][j] = sin(M_PI * i * step_x) + (j * step_y);
}

double norm_value(const Matrix &m, int steps_x, int steps_y) // Normal value of matrix m
{
    double tmp = 0.0;
    for (int i = 1; i < steps_x; ++i)
        for (int j = 1; j < steps_y; ++j)
            if (tmp < fabs(m[i][j])) tmp = fabs(m[i][j]);
    return tmp;
}

void solve(Matrix &m, double step_x, double step_y, int steps_x, int steps_y, double eps, int &iter, double param) // Solving by upper relaxation method
{
    start_values(m, step_x, step_y, steps_x, steps_y);
    
    interpolation(m, step_x, step_y, steps_x, steps_y);
    
    Matrix Tmp;
    init(Tmp, steps_x + 1, steps_y + 1);
    
    double temp;
    
    for (int i = 0; i < steps_x; ++i)
        for (int j = 0; j < steps_y; ++j)
            Tmp[i][j] = m[i][j];
            
    for (int i = 1; i < steps_x; ++i)
        for (int j = 1; j < steps_y; ++j)
            {
                temp = (Tmp[i+1][j] * (1.0 / (step_x * step_x) + 1.0 / step_x) + \
                        Tmp[i-1][j] * (1.0 / (step_x * step_x) - 1.0 / step_x) + \
                        Tmp[i][j+1] * (1.0 / (step_y * step_y)) + \
                        Tmp[i][j-1] * (1.0 / (step_y * step_y))) / \
                        (2.0 / (step_x * step_x) + 2.0 / (step_y * step_y) - 3.0);
                Tmp[i][j] = temp / param - ((1 - param) / param) * m[i][j];
            }
        
    ++iter;
    
    while (fabs(norm_value(m, steps_x, steps_y) - norm_value(Tmp, steps_x, steps_y)) >= eps)
    {
        for (int i = 1; i < steps_x; ++i)
            for (int j = 1; j < steps_y; ++j)
                m[i][j] = Tmp[i][j];
    
        for (int i = 1; i < steps_x; ++i)
            for (int j = 1; j < steps_y; ++j)
                {
                    temp = (Tmp[i+1][j] * (1.0 / (step_x * step_x) + 1.0 / step_x) + \
                            Tmp[i-1][j] * (1.0 / (step_x * step_x) - 1.0 / step_x) + \
                            Tmp[i][j+1] * (1.0 / (step_y * step_y)) + \
                            Tmp[i][j-1] * (1.0 / (step_y * step_y))) / \
                            (2.0 / (step_x * step_x) + 2.0 / (step_y * step_y) - 3.0);
                    Tmp[i][j] = temp / param - ((1 - param) / param) * m[i][j];
                }
                
        ++iter;
    }
    
    for (int i = 1; i < steps_x; ++i)
            for (int j = 1; j < steps_y; ++j)
                m[i][j] = Tmp[i][j];
                
}

int main()
{
    Matrix M;
    
    int steps_x, steps_y;
    double lim_x = 1.0;
    double lim_y = 1.0;
    double eps;
    double param;

//    cin >> steps_x >> steps_y >> eps >> param;
    steps_x = 20;
    steps_y = 20;
    eps = 1e-3;
    param = 0.56;
    
    double step_x = lim_x/steps_x;
    double step_y = lim_y/steps_y;
    
    init(M, steps_x + 1, steps_y + 1);
    
    int iter = 0;
    solve(M, step_x, step_y, steps_x, steps_y, eps, iter, param);

    for (int i = 0; i < M.size(); ++i)
    {
        for (int j = 0; j < M[i].size(); ++j)
            cout << std::setw(15) << M[i][j];
        cout << endl;
    }
        
    return 0;
}

