#include "optimisation.h"

#include <cstdlib>
#include <ctime>
#include <cmath>


const double Optimizer::FIRST_SCALE = 1.3;
const int Optimizer::REPEAT_DIVIDING = 10;

Optimizer::Optimizer(Function* J, double accuracy) :
  _J(J),
  _accuracy(accuracy) {
  do {
    _points.push_back((*_J).random_vector());
  } while (_points.size() < _points[0].size());
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


vector<double> Optimizer::reflect(vector<double> gravity_center_cache, int worst_point, double current_scale) {
  vector<double> new_point;
  for (int j = 0; j < _points[0].size(); ++j) {
    new_point.push_back(\
       gravity_center_cache[j] + \
       current_scale * (gravity_center_cache[j] - _points[worst_point][j]));
  }
  return (*_J).crop(new_point);
}

#include <iostream>
bool Optimizer::update_point() {
  double current_scale = FIRST_SCALE;

  vector<double> cache_gravity_center = gravity_center();
  int worst_point = worst_point_index();
  std::cout.precision(30);
  std::cout << _cached_values[worst_point] << std::endl;
  for (int i = 0; i < REPEAT_DIVIDING; ++i) {
    vector<double> new_point = reflect(cache_gravity_center, worst_point, current_scale);
    if ((*_J)(new_point) > _cached_values[worst_point]) {
      current_scale /= 2.0;
    } else {
      _points[worst_point] = new_point;
      _cached_values[worst_point] = (*_J)(_points[worst_point]);
      return true;
    }
  }
  return false;
}


void Optimizer::reduction() {
  int min_index = best_point_index();
  for (int i = 0; i < _points.size(); ++i) {
    for (int j = 0; j < _points[0].size(); ++j) {
      _points[i][j] = _points[min_index][j] + 0.5 * (_points[i][j] - _points[min_index][j]);
    }
    _cached_values[i] = (*_J)(_points[i]);
  }
}


bool Optimizer::is_enough() {
  double sum = 0.0;
  double tmp = (*_J)(gravity_center());
  for (int i = 0; i < _points.size(); ++i) {
    double d = tmp - _cached_values[i];
    sum += d * d;
  }
  return sqrt(sum) < _accuracy;
}


vector<double> Optimizer::optimize() {
  while (true) {
    if (is_enough()) {
      return _points[best_point_index()];
    }
    if (!update_point()) {
      reduction();
    }
  }
}
