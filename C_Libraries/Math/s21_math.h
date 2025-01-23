#ifndef S21_MATH
#define S21_MATH
#define s21_NAN __builtin_nanf("0x7fc00000")
#define s21_EPS 4.94065645841247E-324
#define s21_M_PI 3.14159265358979323846264338327950288
#define s21_E 2.7182818284590452353602874713526624977572
#define s21_INFINITY 1.0 / 0.0
#define POS_INF 1.0 / 0.0
#define NEG_INF -1.0 / 0.0

long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_cos(double x);
long double s21_sin(double x);
long double s21_tan(double x);
long double s21_sqrt(double x);
int s21_abs(int x);
long double s21_fabs(double x);
long double s21_pow(double base, double exp);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_fact(long double n);
char s21_isNumNegative(const double number);
char s21_isNumNan(const double number);
char s21_isNumInfinity(const double exp);

#endif
