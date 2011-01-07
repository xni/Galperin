#include <cstdlib>
#include <cmath>
#include <ctime>

#include "find_source.h"
#include "../normal_distribution.h"

#include "../MQ/MQ_1.h"


const int FindSource::left_neurons = 45;
const int FindSource::right_neurons = 3;
const double FindSource::w_min = -1000;
const double FindSource::w_max = 1000;
const double FindSource::a_min = 0;
const double FindSource::a_max = 2;
const double FindSource::c_min = 0;
const double FindSource::c_max = 0.4;



FindSource::FindSource(double sigma) :
  Function(),
  _sigma(sigma) {
  srand(time(0));
  double data[100] = {0.0, 0.00308440683833, 0.00608718935909, 0.00900834756554, 0.0118478814609, 0.0146057910483, 0.0172820763311, 0.0198767373123, 0.022389773995, 0.0248211863825, 0.0271709744777, 0.0294391382837, 0.0316256778036, 0.0337305930402, 0.0357538839965, 0.0376955506753, 0.0395555930796, 0.0413340112119, 0.0430308050751, 0.0446459746719, 0.0461795200047, 0.0476314410762, 0.0490017378887, 0.0502904104448, 0.0514974587467, 0.0526228827966, 0.0536993323264, 0.0547268073382, 0.055705307834, 0.0566348338157, 0.0575153852852, 0.0583469622443, 0.0591295646946, 0.0598631926378, 0.0605478460753, 0.0611835250087, 0.0617702294391, 0.0623079593679, 0.0627967147962, 0.063236495725, 0.0636273021553, 0.0639691340879, 0.0642619915236, 0.064505874463, 0.0647007829066, 0.0648467168551, 0.0649436763086, 0.0649916612674, 0.0649906717317, 0.0649407077016, 0.0648417691769, 0.0646938561576, 0.0644969686433, 0.0642511066338, 0.0639562701286, 0.0636124591271, 0.0632196736287, 0.0627779136327, 0.0622871791381, 0.0617474701441, 0.0611587866496, 0.0605211286535, 0.0598344961546, 0.0590988891516, 0.0583143076431, 0.0574807516276, 0.0565982211034, 0.0556667160691, 0.0546862365227, 0.0536567824625, 0.0525783538867, 0.0514509507931, 0.0502745731798, 0.0490492210447, 0.0477748943854, 0.0464515931999, 0.0450793174857, 0.0436580672404, 0.0421878424616, 0.0406686431467, 0.0391004692932, 0.0374833208985, 0.0358171979599, 0.0341021004746, 0.0323380284399, 0.030524981853, 0.028662960711, 0.026751965011, 0.0247919947502, 0.0227830499254, 0.0207251305338, 0.0186182365724, 0.0164623680381, 0.0142575249279, 0.0120037072387, 0.00970091496746, 0.00734914811105, 0.0049484066664, 0.00249869063041, 0.0};
  double h = 0.4 / 99;
  for (int i = 0; i < 100; i++) {
    points.push_back(h * i);
    values.push_back(distribute(data[i], _sigma));
    //values.push_back(distribute(sin(h * i), _sigma));
  }
}


double FindSource::operator()(vector<double> p) {
  double result = 0;
  vector<double> approximator_vector, sd_vector;
  for (int i = 0; i < 3 * left_neurons; i++) approximator_vector.push_back(p[i]);
  for (int i = 3 * left_neurons; i < 3 * (left_neurons + right_neurons); i++) sd_vector.push_back(p[i]);
  MQ_1 appr(approximator_vector);
  MQ_1 sd(sd_vector);
  for (int i = 0; i < points.size(); i++) {
    double val_tmp = values[i] - appr.value(points[i]);
    result += val_tmp * val_tmp;
    double sd_tmp = appr.laplace(points[i]) - sd.value(points[i]);
    if (fabs(sd_tmp) > 10) {
      result += 0.0 * sd_tmp * sd_tmp;
    }
   }
  return result;
}


vector<double> FindSource::random_vector() {
  vector<double> result;
  for (int i = 0; i < left_neurons + right_neurons; i++) {
    result.push_back(w_min + (w_max - w_min) * rand() / RAND_MAX);
    result.push_back(a_min + (a_max - a_min) * rand() / RAND_MAX);
    result.push_back(c_min + (c_max - c_min) * rand() / RAND_MAX);
  }
  return result;
}


vector<double> FindSource::crop(vector<double> p) {
  vector<double> result;
  for (int i = 0; i < 3 * (left_neurons + right_neurons); i++) {
    result.push_back(p[i]);
    int type = i % 3;
    if (type == 0) {
      if (result[i] < w_min) result[i] = w_min;
      else if (result[i] > w_max) result[i] = w_max;
    }
    else if (type == 1) {
      if (result[i] < a_min) result[i] = a_min;
      else if (result[i] > a_max) result[i] = a_max;
    }
    else if (type == 2) {
      if (result[i] < c_min) result[i] = c_min;
      else if (result[i] > c_max) result[i] = c_max;
    }
  }
  return result;
}


double FindSource::max_error(vector<double> p) {
  double result = -1.0;
  vector<double> tv;
  for (int i = 0; i < 3 * left_neurons; i++) {
    tv.push_back(p[i]);
  }
  MQ_1 cmq(tv);
  for (int i = 0; i < points.size(); i++) {
    double tmp = fabs(values[i] - cmq.value(points[i]));
    if (tmp > result)
      result = tmp;
  }
  return result;
}


string FindSource::report(vector<double> p) {
  string result;
  std::stringstream ss;
  vector<double> tv;
  for (int i = 0; i < 3 * left_neurons; i++) {
    tv.push_back(p[i]);
  }
  MQ_1 cmq(tv);
  ss << "Результат аппроксимации при допустимой погрешности датчиков " << \
    _sigma << std::endl;
  ss << "Функция ошибки: " << (*this)(p) << std::endl;
  ss << "Максимальное непопадание: " << (*this).max_error(p) << std::endl;
  ss << "Ответ: " << std::endl;
  ss << cmq.report_value();
  ss << "Вторая производная: " << std::endl;
  ss << cmq.report_laplace();
  /*  ss << "Табулирование значений: x, точное, найденное" << std::endl;
  double h = M_PI / 99;
  for (int i = 0; i < 100; i++) {
    ss << i * h << '\t' << values[i] << '\t' << cmq.value(i * h) << '\t' << std::endl;
  }
  ss << "Табулирование второй производной: x, точное, найденное" << std::endl;
  for (int i = 0; i < 100; i++) {
    double r = 0;
    if (i * h < 0.1)
      r = sin(i * h / 0.1 * 3.1415);
    else
      r = -sin((i * h - 0.1) / 0.1 * 3.1415);
    r = -sin(h * i);
    ss << i * h << '\t' << r << '\t' << cmq.laplace(i * h) << std::endl;
    }*/
  return ss.str();
}
