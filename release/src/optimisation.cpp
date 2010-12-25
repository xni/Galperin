#include "optimisation.h"

#include <cstdlib>
#include <ctime>


const double Optimizer::FIRST_SCALE = 1.3;
const int Optimizer::REPEAT_DIVIDING = 10;

#include <iostream>

Optimizer::Optimizer(Function* J, int neurons, double accuracy, Restrictions restrictions) :
  _J(J),
  _accuracy(accuracy),
  _restrictions(restrictions),
  _neurons(neurons) {
  srand(time(0));
  for (int i = 0; i < 2 * neurons * (2 + restrictions.dimensions()); i++) {
    vector<double> c;
    for (int j = 0; j < neurons; j++) {
      c.push_back(restrictions.w_min() + (restrictions.w_max() - restrictions.w_min()) * \
                  double(rand()) / RAND_MAX);
      c.push_back(restrictions.a_min() + (restrictions.a_max() - restrictions.a_min()) * \
                  double(rand()) / RAND_MAX);
      for (int c_i = 0; c_i < restrictions.dimensions(); c_i++) {
	c.push_back(restrictions.c_min(c_i) + \
		    (restrictions.c_max(c_i) - restrictions.c_min(c_i)) * \
		    double(rand()) / RAND_MAX);
      }
    }
    _points.push_back(c);
  }
  fill_cache();
}


void Optimizer::fill_cache() {
  _cached_values.clear();
  for (int i = 0; i < _points.size(); i++) {
    _cached_values.push_back((*_J)(_points[i]));
  }
}


int Optimizer::worst_point_index() {
  int max_index = 0;
  for (int i = 0; i < _points.size(); ++i) {
    if (_cached_values[i] > _cached_values[max_index]) {
      max_index = i;
    }
  }
  return max_index;
}


int Optimizer::best_point_index() {
  int min_index = 0;
  for (int i = 0; i < _points.size(); ++i) {
    if (_cached_values[i] < _cached_values[min_index]) {
      min_index = i;
    }
  }
  return min_index;
}


vector<double> Optimizer::gravity_center() {
  int worst_point = worst_point_index();
  vector<double> result(_points[0].size());
  
  for (int i = 0; i < _points.size(); i++) {
    if (i == worst_point) 
      continue;

    for (int j = 0; j < _points[0].size(); j++) {
      result[j] += _points[i][j];
    }
  }
  for (int i = 0; i < _points[0].size(); i++) {
    result[i] /= (_points.size() - 1);
  }
  return result;
}

double Optimizer::max_difference() {
  double min_val = 0;
  double max_val = 0;
  for (int i = 0; i < _points.size(); i++) {
    if (_cached_values[i] > _cached_values[max_val]) {
      max_val = i;
    }
    if (_cached_values[i] < _cached_values[min_val]) {
      min_val = i;
    }
  }
  return _cached_values[max_val] - _cached_values[min_val];
}


bool Optimizer::update_point() {
  vector<double> new_point(_points[0].size());    
  double current_scale = FIRST_SCALE;
    
  vector<double> cache_gravity_center = gravity_center();
  int worst_point = worst_point_index();
  
  for (int i = 0; i < REPEAT_DIVIDING; ++i) {
    for (int j = 0; j < _points[0].size(); ++j) {
      new_point[j] = cache_gravity_center[j] + current_scale * (cache_gravity_center[j] - _points[worst_point][j]);
      int type = j % (2 + _restrictions.dimensions());
      if (type == 0) {
	new_point[j] = _restrictions.acceptable_w(new_point[j]);
      }
      else if (type == 1) {
	new_point[j] = _restrictions.acceptable_a(new_point[j]);
      }
      else {
	new_point[j] = _restrictions.acceptable_c(new_point[j], type - 2);
      }
    }
    
    if ((*_J)(new_point) > _cached_values[worst_point]) {
      current_scale /= 2.0;
    }
    else {
      std::cout << "REPLACE\n";
      for (int i = 0; i < _points[0].size(); i++) {
	_points[worst_point][i] = new_point[i];
      }
      _cached_values[worst_point] = (*_J)(_points[worst_point]);
      return true;
    }
  }
  return false;
}


void Optimizer::reduction() {
  int min_index = best_point_index();
  double max_error = _cached_values[min_index];
  for (int i = 0; i < _points.size(); ++i) {
    for (int j = 0; j < _points[0].size(); ++j) {
      _points[i][j] = _points[min_index][j] + 0.5 * (_points[i][j] - _points[min_index][j]);
    }
    _cached_values[i] = (*_J)(_points[i]);
    if (max_error < _cached_values[i]) {
      max_error = _cached_values[i];
    }
  }
}


vector<double> Optimizer::optimize() {
  int iteration = 0;
  while (true) {
    ++iteration;

    std::cout << max_difference() << std::endl;

    if (iteration % 100 == 0 && max_difference() < _accuracy) {
      return _points[best_point_index()];
    }

    if (!update_point()) {
      reduction();
    }
  }
}
