#ifndef OPTIMISATION
#define OPTIMISATION

#include <vector>

#include "function.h"
#include "restrictions.h"

using std::vector;

class Optimizer {
 public:
  Optimizer(Function* J, int neurons, double accuracy, Restrictions restrictions);
  vector<double> optimize();

 private:
  double max_difference();
  vector<double> gravity_center();
  bool update_point();
  int best_point_index();
  int worst_point_index();
  void fill_cache();
  void reduction();
  vector<double> reflect(vector<double> gravity_center_cache, int worst_point, double current_scale);
  bool is_enough();

  vector<double> _cached_values;
  Function* _J;
  vector< vector<double> > _points;
  double _accuracy;
  Restrictions _restrictions;
  int _neurons;
  
  static const double FIRST_SCALE;
  static const int REPEAT_DIVIDING;
};

#endif
