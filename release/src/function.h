#ifndef FUNCTION_H
#define FUNCTION_H

#include<functional>
#include<vector>

using std::vector;
using std::unary_function;

class Function : unary_function<vector<double>,double> {
 public:
  virtual double operator()(vector<double> p) = 0;
};

#endif
