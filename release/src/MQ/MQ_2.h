#ifndef MQ_2_H
#define MQ_2_H

#include <cmath>
#include <vector>
#include <sstream>

using std::vector;
using std::string;

class MQ_2 {
 public:
  MQ_2(vector<double> data);
  double value(double x, double y);
  double laplace(double x, double y);
  string report_value();
 private:
  vector<double> _data;
  double w(int i) {
    return _data[i * 4]; }
  double a(int i) {
    return _data[i * 4 + 1]; }
  double cx(int i) {
    return _data[i * 4 + 2]; }
  double cy(int i) {
    return _data[i * 4 + 3]; }
  double dx(int i, double x) {
    return cx(i) - x; }
  double dy(int i, double y) {
    return cy(i) - y; }
  double core(int i, double x, double y) {
    return sqrt(a(i) * a(i) + dx(i, x) * dx(i, x) + dy(i, y) * dy(i, y)); }
};

#endif
