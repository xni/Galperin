// Нормальное распределение
// можно было бы использовать ЦПТ, но быстрее и точнее http://ru.wikipedia.org/w/index.php?title=%D0%9F%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%91%D0%BE%D0%BA%D1%81%D0%B0_%E2%80%94_%D0%9C%D1%8E%D0%BB%D0%BB%D0%B5%D1%80%D0%B0

#include <cmath>
#include <cstdlib>
#include <time.h>

double distribute(double M, double sigma) {
  double x, y, s;
  do {
    x = 2.0 * double(rand()) / RAND_MAX - 1.0;
    y = 2.0 * double(rand()) / RAND_MAX - 1.0;
    s = x*x + y*y;
  } while (s == 0.0 || s > 1.0);
  return M + sigma * x * sqrt(-2.0 * log(s) / s);
}
