#ifndef FUNCTION_H
#define FUNCTION_H

#include<functional>
#include<vector>

using std::vector;

class Function : unary_function<vector<double>,double> {
 public:
  double operator()(vector<double> p);
};

#endif
