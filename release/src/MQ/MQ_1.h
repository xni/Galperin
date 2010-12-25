#include <vector>

using std::vector;

class MQ_1 {
 public:
  MQ_1(vector<double> data);
  double value(double x);
  double d(double x);
  double laplace(double x);
 private:
  vector<double> _data;
};
