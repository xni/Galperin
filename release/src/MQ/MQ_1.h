#ifndef MQ_1_H
#define MQ_1_H

#include <vector>
#include <sstream>

using std::vector;
using std::string;

class MQ_1 {
 public:
  MQ_1(vector<double> data);
  double value(double x);
  double d(double x);
  double laplace(double x);
  string report_value();
  string report_laplace();
 private:
  vector<double> _data;
};

#endif
