#ifndef RESTRICTIONS_H
#define RESTRICTIONS_H

#include <vector>

using std::vector;
using std::min;
using std::max;

class Restrictions {
 public:
 Restrictions(double w_min, double w_max, double a_min, double a_max,
	      vector<double> c_min, vector<double> c_max):
    _w_min(w_min),
    _w_max(w_max),
    _a_min(a_min),
    _a_max(a_max),
    _c_min(c_min),
    _c_max(c_max) {
    }

  double w_min() { return _w_min; }
  double w_max() { return _w_max; }
  double a_min() { return _a_min; }
  double a_max() { return _a_max; }
  double c_min(int p) { return _c_min[p]; }
  double c_max(int p) { return _c_max[p]; }

  double acceptable_w(double c) {
    return max(w_min(), min(w_max(), c));
  }

  double acceptable_a(double c) {
    return max(a_min(), min(a_max(), c));
  }

  double acceptable_c(double c, int p) {
    return max(c_min(p), min(c_max(p), c));
  }

  int dimensions() {
    return _c_min.size();
  }
      

 private:
  double _w_min;
  double _w_max;
  double _a_min;
  double _a_max;
  vector<double> _c_min;
  vector<double> _c_max;
};

#endif
