/* Решение задачи апроксимации второй производной функции.
 * То есть решение прямой задачи.
 */

#ifndef SD_APPROXIMATOR_H
#define SD_APPROXIMATOR_H

#include <sstream>
#include <vector>

#include "../function.h"

using std::string;
using std::vector;

class SD_Approximator : public Function {
 public:
  SD_Approximator();
  double operator()(vector<double> p);
  string report(vector<double> p);

 private:
  double max_error(vector<double> p);
  
  vector<double> points;
  vector<double> values;
};

#endif
