#include "s21_math.h"

long double s21_fmod(double x, double y) {
  double fmod21 = 0.0;
  long double result = 0.0;
  if (y == 0.0) {
    result = s21_NAN;
  } else {
    double z = x / y;
    fmod21 = x - (int)z * y;
    result = fmod21;
  }
  return result;
}

long double s21_acos(double x) {
  x = s21_fmod(x, 2 * s21_M_PI);
  long double result = 0;
  int err = 0;
  if (s21_isNumNan(x) || s21_isNumInfinity(x)) {
    err = 1;
  } else if (s21_fabs(x) <= 1.0) {
    result = s21_M_PI / 2.0 - s21_asin(x);
  } else {
    err = 1;
  }
  return err ? s21_NAN : result;
}

long double s21_asin(double x) {
  x = s21_fmod(x, 2 * s21_M_PI);
  long double result = 0;
  int err = 0;
  if (s21_isNumNan(x) || s21_isNumInfinity(x)) {
    err = 1;
  } else if (s21_fabs(x) <= 1.0) {
    if (x == 1.0) {
      result = s21_M_PI / 2;
    } else if (x == -1.0) {
      result = -s21_M_PI / 2;
    } else {
      for (int i = 0; i < 20; ++i) {
        result += (s21_fact(2 * i) /
                   (s21_pow(2, 2 * i) * s21_fact(i) * s21_fact(i))) *
                  (s21_pow(x, 2 * i + 1) / (2 * i + 1));
      }
    }
  } else {
    err = 1;
  }
  return err ? s21_NAN : result;
}

long double s21_atan(double x) {
  long double result = 0;
  int err = 0;
  int too_big = 0;
  int sign = x < 0 ? -1 : 1;
  x = s21_fabs(x);
  if (s21_isNumNan(x)) {
    err = 1;
  } else if (x == s21_INFINITY) {
    result = s21_M_PI / 2;
  } else {
    if (x > 1.0) {
      x = 1 / x;
      too_big = 1;
    }
    if (x == 1.0) {
      result = s21_M_PI / 4;
    } else {
      for (int i = 1; i < 20; ++i) {
        result += (s21_pow(-1, i - 1) / (2 * i - 1)) * s21_pow(x, 2 * i - 1);
      }
    }
  }
  return err ? s21_NAN
             : (!too_big ? result * sign : ((s21_M_PI / 2 - result) * sign));
}

long double s21_cos(double x) {
  x = s21_fmod(x, 2 * s21_M_PI);
  long double result = 0;
  int err = 0;
  if (s21_isNumNan(x) || s21_isNumInfinity(x)) {
    err = 1;
  } else {
    for (int i = 0; i < 20; ++i) {
      result += s21_pow(-1, i) * s21_pow(x, 2 * i) / s21_fact(2 * i);
    }
  }
  return err ? s21_NAN : result;
}

long double s21_sin(double x) {
  x = s21_fmod(x, 2 * s21_M_PI);
  long double result = 0;
  int err = 0;
  if (s21_isNumNan(x) || s21_isNumInfinity(x)) {
    err = 1;
  } else {
    for (int i = 0; i < 20; ++i) {
      result += s21_pow(-1, i) * s21_pow(x, 2 * i + 1) / s21_fact(2 * i + 1);
    }
  }
  return err ? s21_NAN : result;
}

long double s21_tan(double x) {
  int err = 0;
  if (s21_isNumNan(x) || s21_isNumInfinity(x)) {
    err = 1;
  }
  return err ? s21_NAN : s21_sin(x) / s21_cos(x);
}

long double s21_fact(long double n) {
  return (n <= 0) ? 1 : n * s21_fact(n - 1);
}

long double s21_exp(double x) {
  long double result = 1.0;

  if (x == 1.0 / 0.0 || x >= 710.0) {
    result = 1.0 / 0.0;
  } else if (x == -1.0 / 0.0) {
    result = 0.0;
  } else if (x != x) {
    result = x;
  } else if (x < 0.0) {
    result = 1.0 / s21_exp(-x);
  } else {
    const int max_iterations = 2000;
    long double term = 1.0;

    for (int i = 1; i <= max_iterations; ++i) {
      term *= x / i;
      result += term;
    }
  }

  return result;
}

long double s21_log(double x) {
  long double result = 0.0;
  long double approximation = 1.0;
  int exponent = 0;

  if (x < 0.0) {
    result = 0.0 / 0.0;
  } else if (x == 0.0) {
    result = (-1.0 / 0.0);
  } else if (x == (1.0 / 0.0)) {
    result = x;
  } else {
    while (x >= s21_E) {
      x /= s21_E;
      ++exponent;
    }

    for (int i = 0; i < 100; ++i) {
      approximation = result;
      result = approximation + 2 * ((x - s21_exp(approximation)) /
                                    (x + s21_exp(approximation)));
    }
  }

  return result + exponent;
}

long double s21_ceil(double x) {
  if (x == s21_INFINITY) {
    x = s21_INFINITY;
  } else if (x == -s21_INFINITY) {
    x = -s21_INFINITY;
  } else if (s21_fabs(s21_fmod(x, 1.0)) >= s21_EPS) {
    if (x < 0) {
      x = (long int)x;
    } else {
      x = (long int)x + 1;
    }
  }
  return x;
}

long double s21_floor(double x) {
  if (x == s21_INFINITY) {
    x = s21_INFINITY;
  } else if (x == -s21_INFINITY) {
    x = -s21_INFINITY;
  } else if (s21_fabs(s21_fmod(x, 1.0)) >= s21_EPS) {
    if (x < 0) {
      x = (long int)x - 1;
    } else {
      x = (long int)x;
    }
  }
  return x;
}

int s21_abs(int x) { return x > 0 ? x : -x; }

long double s21_fabs(double x) { return (long double)x > 0 ? x : -x; }

char s21_isNumNegative(const double number) { return number < 0 ? 1 : 0; }
char s21_isNumNan(const double number) { return number != number ? 1 : 0; }

long double s21_sqrt(double x) {
  long double result = x;
  if (!(s21_isNumNan(x) || s21_isNumNegative(x))) {
    result = s21_pow(x, 0.5);
  } else
    result = s21_NAN;
  return result;
}

char s21_isNumInfinity(const double exp) {
  return exp == s21_INFINITY || exp == -s21_INFINITY ? 1 : 0;
}

long double s21_ifExponentaInfinity(const double base, const double exp) {
  long double result = 1.0;
  if (!(base == 1 || base == -1)) {
    if (s21_fabs(base) > 1) {
      if (exp == s21_INFINITY)
        result = exp;
      else
        result = 0;
    } else {
      if (exp == s21_INFINITY)
        result = 0;
      else
        result = s21_INFINITY;
    }
  }
  return result;
}

long double s21_ifBaseInfinityAndExpFloat(const double base, const double exp) {
  long double result = 1.0;
  if (-s21_INFINITY == base) {
    if (exp < 0)
      result = 0;
    else
      result = s21_INFINITY;
  } else {
    if (exp < 0)
      result = 0;
    else
      result = s21_INFINITY;
  }
  return result;
}

long double s21_ifExponentaNotInfinity(double base, double exp) {
  long double result = 1.0;
  if (s21_isNumInfinity(base) && (exp != (int)exp))
    result = s21_ifBaseInfinityAndExpFloat(base, exp);
  else {
    char isExpNeg = 0;
    if (exp < 0) {
      isExpNeg = 1;
      exp *= -1;
    }
    if (exp == (int)exp) {
      for (int i = 1; i <= exp; i++) {
        result *= base;
      }
    } else {
      int sign = base < 0 ? -1 : 1;
      result = s21_exp(exp * s21_log(base * sign));
      if (s21_fmod(exp, 2)) result *= sign;
    }
    if (isExpNeg) result = 1 / result;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 1.0;
  if (base != 1 && exp != 0) {
    if (s21_isNumNan(exp) && base != 0)
      result = s21_NAN;
    else {
      if (s21_isNumInfinity(exp))
        result = s21_ifExponentaInfinity(base, exp);
      else
        result = s21_ifExponentaNotInfinity(base, exp);
    }
  }
  return result;
}
