#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"

#define NUMBER_OF_FUNCS 15

START_TEST(test_sin_1) {
  ck_assert_ldouble_eq_tol(s21_sin(0.6), sin(0.6), 0.0000001);
}
END_TEST

START_TEST(test_sin_2) {
  ck_assert_ldouble_eq_tol(s21_sin(-1), sin(-1), 0.0000001);
}
END_TEST

START_TEST(test_sin_3) {
  ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 0.0000001);
}
END_TEST

START_TEST(test_sin_4) {
  ck_assert_ldouble_eq_tol(s21_sin(1), sin(1), 0.0000001);
}
END_TEST

START_TEST(test_sin_5) {
  ck_assert_ldouble_eq_tol(s21_sin(-1.5638216482164), sin(-1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_sin_6) {
  ck_assert_ldouble_eq_tol(s21_sin(1.5638216482164), sin(1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_sin_7) { ck_assert(isnan(s21_sin(NAN)) == isnan(sin(NAN))); }
END_TEST

START_TEST(test_sin_8) {
  ck_assert(isnan(s21_sin(INFINITY)) == isnan(sin(INFINITY)));
}
END_TEST

START_TEST(test_sin_9) {
  ck_assert_ldouble_eq_tol(s21_sin(12000000), sin(12000000), 0.0000001);
}
END_TEST

START_TEST(test_cos_1) {
  ck_assert_ldouble_eq_tol(s21_cos(0.6), cos(0.6), 0.0000001);
}
END_TEST

START_TEST(test_cos_2) {
  ck_assert_ldouble_eq_tol(s21_cos(-1), cos(-1), 0.0000001);
}
END_TEST

START_TEST(test_cos_3) {
  ck_assert_ldouble_eq_tol(s21_cos(0), cos(0), 0.0000001);
}
END_TEST

START_TEST(test_cos_4) {
  ck_assert_ldouble_eq_tol(s21_cos(1), cos(1), 0.0000001);
}
END_TEST

START_TEST(test_cos_5) {
  ck_assert_ldouble_eq_tol(s21_cos(-1.5638216482164), cos(-1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_cos_6) {
  ck_assert_ldouble_eq_tol(s21_cos(1.5638216482164), cos(1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_cos_7) { ck_assert(isnan(s21_cos(NAN)) == isnan(cos(NAN))); }
END_TEST

START_TEST(test_cos_8) {
  ck_assert(isnan(s21_cos(INFINITY)) == isnan(cos(INFINITY)));
}
END_TEST

START_TEST(test_cos_9) {
  ck_assert_ldouble_eq_tol(s21_cos(12000000), cos(12000000), 0.0000001);
}
END_TEST

START_TEST(test_tan_1) {
  ck_assert_ldouble_eq_tol(s21_tan(0.6), tan(0.6), 0.0000001);
}
END_TEST

START_TEST(test_tan_2) {
  ck_assert_ldouble_eq_tol(s21_tan(-1), tan(-1), 0.0000001);
}
END_TEST

START_TEST(test_tan_3) {
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), 0.0000001);
}
END_TEST

START_TEST(test_tan_4) {
  ck_assert_ldouble_eq_tol(s21_tan(1), tan(1), 0.0000001);
}
END_TEST

START_TEST(test_tan_5) {
  ck_assert_ldouble_eq_tol(s21_tan(-1.5638216482164), tan(-1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_tan_6) {
  ck_assert_ldouble_eq_tol(s21_tan(1.5638216482164), tan(1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_tan_7) { ck_assert(isnan(s21_tan(NAN)) == isnan(tan(NAN))); }
END_TEST

START_TEST(test_tan_8) {
  ck_assert(isnan(s21_tan(INFINITY)) == isnan(tan(INFINITY)));
}
END_TEST

START_TEST(test_tan_9) {
  ck_assert_ldouble_eq_tol(s21_tan(12000000), tan(12000000), 0.0000001);
}
END_TEST

START_TEST(test_asin_1) {
  ck_assert_ldouble_eq_tol(s21_asin(0.6), asin(0.6), 0.0000001);
}
END_TEST

START_TEST(test_asin_2) {
  ck_assert_ldouble_eq_tol(s21_asin(-1), asin(-1), 0.0000001);
}
END_TEST

START_TEST(test_asin_3) {
  ck_assert_ldouble_eq_tol(s21_asin(0), asin(0), 0.0000001);
}
END_TEST

START_TEST(test_asin_4) {
  ck_assert_ldouble_eq_tol(s21_asin(1), asin(1), 0.0000001);
}
END_TEST

START_TEST(test_asin_5) { ck_assert_ldouble_nan(s21_asin(-1.5638216482164)); }
END_TEST

START_TEST(test_asin_6) { ck_assert_ldouble_nan(s21_asin(1.5638216482164)); }
END_TEST

START_TEST(test_asin_7) { ck_assert(isnan(s21_asin(NAN)) == isnan(asin(NAN))); }
END_TEST

START_TEST(test_asin_8) {
  ck_assert(isnan(s21_asin(INFINITY)) == isnan(asin(INFINITY)));
}
END_TEST

START_TEST(test_asin_9) {
  ck_assert(isnan(s21_asin(12000000)) == isnan(asin(12000000)));
}
END_TEST

START_TEST(test_acos_1) {
  ck_assert_ldouble_eq_tol(s21_acos(0.6), acos(0.6), 0.0000001);
}
END_TEST

START_TEST(test_acos_2) {
  ck_assert_ldouble_eq_tol(s21_acos(-1), acos(-1), 0.0000001);
}
END_TEST

START_TEST(test_acos_3) {
  ck_assert_ldouble_eq_tol(s21_acos(0), acos(0), 0.0000001);
}
END_TEST

START_TEST(test_acos_4) {
  ck_assert_ldouble_eq_tol(s21_acos(1), acos(1), 0.0000001);
}
END_TEST

START_TEST(test_acos_5) { ck_assert_ldouble_nan(s21_acos(-1.5638216482164)); }
END_TEST

START_TEST(test_acos_6) { ck_assert_ldouble_nan(s21_acos(1.5638216482164)); }
END_TEST

START_TEST(test_acos_7) { ck_assert(isnan(s21_acos(NAN)) == isnan(acos(NAN))); }
END_TEST

START_TEST(test_acos_8) {
  ck_assert(isnan(s21_acos(INFINITY)) == isnan(acos(INFINITY)));
}
END_TEST

START_TEST(test_acos_9) {
  ck_assert(isnan(s21_acos(12000000)) == isnan(acos(12000000)));
}
END_TEST

START_TEST(test_atan_1) {
  ck_assert_ldouble_eq_tol(s21_atan(0.6), atan(0.6), 0.0000001);
}
END_TEST

START_TEST(test_atan_2) {
  ck_assert_ldouble_eq_tol(s21_atan(-1), atan(-1), 0.0000001);
}
END_TEST

START_TEST(test_atan_3) {
  ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), 0.0000001);
}
END_TEST

START_TEST(test_atan_4) {
  ck_assert_ldouble_eq_tol(s21_atan(1), atan(1), 0.0000001);
}
END_TEST

START_TEST(test_atan_5) {
  ck_assert_ldouble_eq_tol(s21_atan(-1.5638216482164), atan(-1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_atan_6) {
  ck_assert_ldouble_eq_tol(s21_atan(1.5638216482164), atan(1.5638216482164),
                           0.0000001);
}
END_TEST

START_TEST(test_atan_7) { ck_assert(isnan(s21_atan(NAN)) == isnan(atan(NAN))); }
END_TEST

START_TEST(test_atan_8) {
  ck_assert_ldouble_eq_tol(s21_atan(INFINITY), atan(INFINITY), 0.0000001);
}
END_TEST

START_TEST(test_atan_9) {
  ck_assert_ldouble_eq_tol(s21_atan(-INFINITY), atan(-INFINITY), 0.0000001);
}
END_TEST

START_TEST(test_atan_10) {
  ck_assert_ldouble_eq_tol(s21_atan(12000000), atan(12000000), 0.0000001);
}
END_TEST

START_TEST(test_fmod_1) {
  ck_assert_ldouble_eq_tol(fmod(7.5, 2.9), s21_fmod(7.5, 2.9), 0.0000001);
}
END_TEST

START_TEST(test_nan_1) { ck_assert_ldouble_nan(s21_fmod(7.5, 0.0)); }
END_TEST

START_TEST(test_s21_exp_positive) {
  double input = 2.0;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_exp_zero) {
  double input = 0.0;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_exp_negative) {
  double input = -2.0;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_exp_large) {
  double input = 20.0;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_exp_neg_inf) {
  double input = -INFINITY;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert(isinf(expected_output) == isinf(actual_output));
}
END_TEST

START_TEST(test_s21_exp_pos_inf) {
  double input = INFINITY;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert(isinf(expected_output) == isinf(actual_output));
}
END_TEST

START_TEST(test_s21_exp_nan) {
  double input = NAN;
  long double expected_output = exp(input);
  long double actual_output = s21_exp(input);

  ck_assert(isnan(expected_output) == isnan(actual_output));
}
END_TEST

START_TEST(test_s21_log_superlarge) {
  double input = 1234567890123456.123456;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_log_positive) {
  double input = 2.0;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_log_zero) {
  double input = 0.0;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert(isinf(expected_output) == isinf(actual_output));
}
END_TEST

START_TEST(test_s21_log_negative) {
  double input = -2.0;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert(isnan(expected_output) == isnan(actual_output));
}
END_TEST

START_TEST(test_s21_log_large) {
  double input = 100.0;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert_ldouble_eq_tol(expected_output, actual_output, 0.000001);
}
END_TEST

START_TEST(test_s21_log_neg_inf) {
  double input = -INFINITY;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert(isnan(expected_output) == isnan(actual_output));
}
END_TEST

START_TEST(test_s21_log_pos_inf) {
  double input = INFINITY;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert(isinf(expected_output) == isinf(actual_output));
}
END_TEST

START_TEST(test_s21_log_nan) {
  double input = NAN;
  long double expected_output = log(input);
  long double actual_output = s21_log(input);

  ck_assert(isnan(expected_output) == isnan(actual_output));
}
END_TEST

START_TEST(test_ceil_1) {
  ck_assert_double_eq_tol(ceil(0.0), s21_ceil(0.0), 1e-6);
}
END_TEST

START_TEST(test_ceil_2) {
  ck_assert_double_eq_tol(ceil(-0.0), s21_ceil(-0.0), 1e-6);
}
END_TEST

START_TEST(test_ceil_3) {
  ck_assert_double_eq(ceil(NEG_INF), s21_ceil(NEG_INF));
}
END_TEST

START_TEST(test_ceil_4) {
  ck_assert_double_eq_tol(ceil(-3141517.3412), s21_ceil(-3141517.3412), 1e-6);
}
END_TEST

START_TEST(test_ceil_5) {
  ck_assert_double_eq(ceil(POS_INF), s21_ceil(POS_INF));
}
END_TEST

START_TEST(test_ceil_6) {
  ck_assert_double_eq_tol(ceil(7478.0000001), s21_ceil(7478.0000001), 1e-6);
}
END_TEST

START_TEST(test_ceil_7) {
  ck_assert_double_eq_tol(ceil(76.0), s21_ceil(76.0), 1e-6);
}
END_TEST

START_TEST(test_ceil_8) {
  ck_assert_double_eq_tol(ceil(-10.0), s21_ceil(-10.0), 1e-6);
}
END_TEST

START_TEST(test_ceil_9) {
  ck_assert_double_eq_tol(ceil(-323958032040.2156),
                          s21_ceil(-323958032040.2156), 1e-6);
}
END_TEST

START_TEST(test_ceil_10) {
  ck_assert_double_eq_tol(ceil(54392.49357938), s21_ceil(54392.49357938), 1e-6);
}
END_TEST

START_TEST(test_floor_1) {
  ck_assert_double_eq_tol(floor(0.0), s21_floor(0.0), 1e-6);
}
END_TEST

START_TEST(test_floor_2) {
  ck_assert_double_eq_tol(floor(-0.0), s21_floor(-0.0), 1e-6);
}
END_TEST

START_TEST(test_floor_3) {
  ck_assert_double_eq(floor(NEG_INF), s21_floor(NEG_INF));
}
END_TEST

START_TEST(test_floor_4) {
  ck_assert_double_eq_tol(floor(-3141517.3412), s21_floor(-3141517.3412), 1e-6);
}
END_TEST

START_TEST(test_floor_5) {
  ck_assert_double_eq(floor(POS_INF), s21_floor(POS_INF));
}
END_TEST

START_TEST(test_floor_6) {
  ck_assert_double_eq_tol(floor(7478.0000001), s21_floor(7478.0000001), 1e-6);
}
END_TEST

START_TEST(test_floor_7) {
  ck_assert_double_eq_tol(floor(76.0), s21_floor(76.0), 1e-6);
}
END_TEST

START_TEST(test_floor_8) {
  ck_assert_double_eq_tol(floor(-10.0), s21_floor(-10.0), 1e-6);
}
END_TEST

START_TEST(test_floor_9) {
  ck_assert_double_eq_tol(floor(-323958032040.2156),
                          s21_floor(-323958032040.2156), 1e-6);
}
END_TEST

START_TEST(test_floor_10) {
  ck_assert_double_eq_tol(floor(54392.49357938), s21_floor(54392.49357938),
                          1e-6);
}
END_TEST

START_TEST(test_abs_1) { ck_assert_int_eq(s21_abs(5), abs(5)); }
END_TEST

START_TEST(test_abs_2) { ck_assert_int_eq(s21_abs(-24), abs(-24)); }
END_TEST

START_TEST(test_abs_3) { ck_assert_int_eq(s21_abs(0), abs(0)); }
END_TEST

START_TEST(test_abs_4) { ck_assert_int_eq(s21_abs(32), abs(32)); }
END_TEST

START_TEST(test_abs_5) { ck_assert_int_eq(s21_abs(1), abs(1)); }
END_TEST

START_TEST(test_abs_6) { ck_assert_int_eq(s21_abs(-4234), abs(-4234)); }
END_TEST

START_TEST(test_abs_7) { ck_assert_int_eq(s21_abs(-132), abs(-132)); }
END_TEST

START_TEST(test_abs_8) { ck_assert_int_eq(s21_abs(-53), abs(-53)); }
END_TEST

START_TEST(test_abs_9) { ck_assert_int_eq(s21_abs(234234), abs(234234)); }
END_TEST

START_TEST(test_abs_10) {
  ck_assert_int_eq(s21_abs(-421424223), abs(-421424223));
}
END_TEST

START_TEST(test_fabs_1) {
  ck_assert_ldouble_eq_tol(s21_fabs(5.3434), fabs(5.3434), 0.0000001);
}
END_TEST

START_TEST(test_fabs_2) {
  ck_assert_ldouble_eq_tol(s21_fabs(-53.422), fabs(-53.422), 0.0000001);
}
END_TEST

START_TEST(test_fabs_3) {
  ck_assert_ldouble_eq_tol(s21_fabs(23423.4), fabs(23423.4), 0.0000001);
}
END_TEST

START_TEST(test_fabs_4) {
  ck_assert_ldouble_eq_tol(s21_fabs(-132.323), fabs(-132.323), 0.0000001);
}
END_TEST

START_TEST(test_fabs_5) {
  ck_assert_ldouble_eq_tol(s21_fabs(-1.0063), fabs(-1.0063), 0.0000001);
}
END_TEST

START_TEST(test_fabs_6) {
  ck_assert_ldouble_eq_tol(s21_fabs(132.32542), fabs(132.32542), 0.0000001);
}
END_TEST

START_TEST(test_fabs_7) { ck_assert_int_eq(s21_fabs(0), fabs(0.0)); }
END_TEST

START_TEST(test_fabs_8) { ck_assert_int_eq(s21_fabs(5), fabs(5.0)); }
END_TEST

START_TEST(test_fabs_9) { ck_assert_int_eq(s21_fabs(53232), fabs(53232.0)); }
END_TEST

START_TEST(test_fabs_10) {
  ck_assert_ldouble_eq_tol(s21_fabs(563.242637), fabs(563.242637), 0.0000001);
}
END_TEST

START_TEST(test_fabs_11) {
  ck_assert(isnan(s21_fabs(NAN)) == isnan(fabs(NAN)));
}
END_TEST

START_TEST(test_fabs_12) { ck_assert(s21_fabs(INFINITY) == fabs(INFINITY)); }
END_TEST

START_TEST(test_fabs_13) { ck_assert(s21_fabs(-INFINITY) == fabs(-INFINITY)); }
END_TEST

START_TEST(test_pow_1) { ck_assert(s21_pow(0, -5) == pow(0, -5)); }
END_TEST

START_TEST(test_pow_2) {
  ck_assert_ldouble_eq_tol(s21_pow(0, INFINITY), pow(0, INFINITY), 0.0000001);
}
END_TEST

START_TEST(test_pow_3) {
  ck_assert_ldouble_eq_tol(s21_pow(0, INFINITY), pow(0, INFINITY), 0.0000001);
}
END_TEST

START_TEST(test_pow_4) {
  ck_assert_ldouble_eq_tol(s21_pow(0, 5), pow(0, 5), 0.0000001);
}
END_TEST

START_TEST(test_pow_5) {
  ck_assert_ldouble_eq_tol(s21_pow(0, 5.4), pow(0, 5.4), 0.0000001);
}
END_TEST

START_TEST(test_pow_6) {
  ck_assert_ldouble_eq_tol(s21_pow(0, 6), pow(0, 6), 0.0000001);
}
END_TEST

START_TEST(test_pow_7) {
  ck_assert_ldouble_eq_tol(s21_pow(-1, INFINITY), pow(-1, INFINITY), 0.0000001);
}
END_TEST

START_TEST(test_pow_8) {
  ck_assert_ldouble_eq_tol(s21_pow(1, 6436346), pow(1, 6436346), 0.0000001);
}
END_TEST

START_TEST(test_pow_9) {
  ck_assert_ldouble_eq_tol(s21_pow(1, NAN), pow(1, NAN), 0.0000001);
}
END_TEST

START_TEST(test_pow_10) {
  ck_assert_ldouble_eq_tol(s21_pow(NAN, 0), pow(NAN, 0), 0.0000001);
}
END_TEST

START_TEST(test_pow_11) {
  ck_assert(s21_pow(-INFINITY, INFINITY) == pow(-INFINITY, INFINITY));
}
END_TEST

START_TEST(test_pow_12) {
  ck_assert(s21_pow(-634, INFINITY) == pow(-634, INFINITY));
}
END_TEST

START_TEST(test_pow_13) {
  ck_assert(s21_pow(-INFINITY, 4.63) == pow(-INFINITY, 4.63));
}
END_TEST

START_TEST(test_pow_14) {
  ck_assert(s21_pow(0.4, -INFINITY) == pow(0.4, -INFINITY));
}
END_TEST

START_TEST(test_pow_15) {
  ck_assert(s21_pow(23, -INFINITY) == pow(23, -INFINITY));
}
END_TEST

START_TEST(test_pow_16) {
  ck_assert(s21_pow(23, INFINITY) == pow(23, INFINITY));
}
END_TEST

START_TEST(test_pow_17) {
  ck_assert(s21_pow(23, INFINITY) == pow(23, INFINITY));
}
END_TEST

START_TEST(test_pow_18) {
  ck_assert_ldouble_eq_tol(s21_pow(-INFINITY, -23), pow(-INFINITY, -23),
                           0.0000001);
}
END_TEST

START_TEST(test_pow_19) {
  ck_assert_ldouble_eq_tol(s21_pow(-INFINITY, -23.4), pow(-INFINITY, -23.4),
                           0.0000001);
}
END_TEST

START_TEST(test_pow_20) {
  ck_assert_ldouble_eq_tol(s21_pow(-INFINITY, -24), pow(-INFINITY, -24),
                           0.0000001);
}
END_TEST

START_TEST(test_pow_21) {
  ck_assert(s21_pow(-INFINITY, 5) == pow(-INFINITY, 5));
}
END_TEST

START_TEST(test_pow_22) {
  ck_assert(s21_pow(-INFINITY, 5.23) == pow(-INFINITY, 5.23));
}
END_TEST

START_TEST(test_pow_23) {
  ck_assert(s21_pow(-INFINITY, 6) == pow(-INFINITY, 6));
}
END_TEST

START_TEST(test_pow_24) {
  ck_assert_ldouble_eq_tol(s21_pow(INFINITY, -23), pow(INFINITY, -23),
                           0.0000001);
}
END_TEST

START_TEST(test_pow_25) {
  ck_assert(s21_pow(INFINITY, 23) == pow(INFINITY, 23));
}
END_TEST

START_TEST(test_pow_26) {
  ck_assert(s21_pow(INFINITY, 5.23) == pow(INFINITY, 5.23));
}
END_TEST

START_TEST(test_pow_27) {
  ck_assert_ldouble_eq_tol(s21_pow(-23, 5), pow(-23, 5), 0.0000001);
}
END_TEST

START_TEST(test_pow_28) {
  ck_assert_ldouble_eq_tol(s21_pow(23, 0.5), pow(23, 0.5), 0.0000001);
}
END_TEST

START_TEST(test_pow_29) {
  ck_assert_ldouble_eq_tol(s21_pow(-23, 6), pow(-23, 6), 0.0000001);
}
END_TEST

START_TEST(test_pow_30) {
  ck_assert(isnan(s21_pow(5, NAN)) == isnan(pow(5, NAN)));
}
END_TEST

START_TEST(test_pow_31) {
  ck_assert_ldouble_eq_tol(s21_pow(INFINITY, -4), pow(INFINITY, -4), 0.0000001);
}
END_TEST

START_TEST(test_pow_32) {
  ck_assert_ldouble_eq_tol(s21_pow(INFINITY, -4.2), pow(INFINITY, -4.2),
                           0.0000001);
}
END_TEST

START_TEST(test_sqrt_1) {
  ck_assert_ldouble_eq_tol(s21_sqrt(5.3434), sqrt(5.3434), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_2) { ck_assert(isnan(s21_sqrt(-5)) == isnan(sqrt(-5))); }
END_TEST

START_TEST(test_sqrt_3) {
  ck_assert_ldouble_eq_tol(s21_sqrt(4234), sqrt(4234), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_4) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_5) {
  ck_assert_ldouble_eq_tol(s21_sqrt(434.2344), sqrt(434.2344), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_6) {
  ck_assert_ldouble_eq_tol(s21_sqrt(132), sqrt(132), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_7) {
  ck_assert_ldouble_eq_tol(s21_sqrt(144), sqrt(144), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_8) {
  ck_assert_ldouble_eq_tol(s21_sqrt(1024), sqrt(1024), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_9) {
  ck_assert_ldouble_eq_tol(s21_sqrt(53232), sqrt(53232), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_10) {
  ck_assert_ldouble_eq_tol(s21_sqrt(563.242637), sqrt(563.242637), 0.0000001);
}
END_TEST

START_TEST(test_sqrt_11) {
  ck_assert(isnan(s21_sqrt(NAN)) == isnan(sqrt(NAN)));
}
END_TEST

START_TEST(test_sqrt_12) { ck_assert(s21_sqrt(INFINITY) == sqrt(INFINITY)); }
END_TEST

START_TEST(test_sqrt_13) {
  ck_assert(isinf(s21_sqrt(-INFINITY)) == isinf(sqrt(-INFINITY)));
}
END_TEST

Suite *s21_exp_suite(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_exp_tests");

  tcase = tcase_create("s21_exp");
  tcase_add_test(tcase, test_s21_exp_positive);
  tcase_add_test(tcase, test_s21_exp_zero);
  tcase_add_test(tcase, test_s21_exp_negative);
  tcase_add_test(tcase, test_s21_exp_large);
  tcase_add_test(tcase, test_s21_exp_neg_inf);
  tcase_add_test(tcase, test_s21_exp_pos_inf);
  tcase_add_test(tcase, test_s21_exp_nan);
  suite_add_tcase(suite, tcase);

  return suite;
}

Suite *s21_ceil_test(void) {
  Suite *s = suite_create("ceil");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_ceil_1);
  tcase_add_test(tc_core, test_ceil_2);
  tcase_add_test(tc_core, test_ceil_3);
  tcase_add_test(tc_core, test_ceil_4);
  tcase_add_test(tc_core, test_ceil_5);
  tcase_add_test(tc_core, test_ceil_6);
  tcase_add_test(tc_core, test_ceil_7);
  tcase_add_test(tc_core, test_ceil_8);
  tcase_add_test(tc_core, test_ceil_9);
  tcase_add_test(tc_core, test_ceil_10);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *s21_floor_test(void) {
  Suite *s = suite_create("floor");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_floor_1);
  tcase_add_test(tc_core, test_floor_2);
  tcase_add_test(tc_core, test_floor_3);
  tcase_add_test(tc_core, test_floor_4);
  tcase_add_test(tc_core, test_floor_5);
  tcase_add_test(tc_core, test_floor_6);
  tcase_add_test(tc_core, test_floor_7);
  tcase_add_test(tc_core, test_floor_8);
  tcase_add_test(tc_core, test_floor_9);
  tcase_add_test(tc_core, test_floor_10);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *s21_log_suite(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_log_tests");

  tcase = tcase_create("s21_log");
  tcase_add_test(tcase, test_s21_log_positive);
  tcase_add_test(tcase, test_s21_log_zero);
  tcase_add_test(tcase, test_s21_log_negative);
  tcase_add_test(tcase, test_s21_log_large);
  tcase_add_test(tcase, test_s21_log_neg_inf);
  tcase_add_test(tcase, test_s21_log_pos_inf);
  tcase_add_test(tcase, test_s21_log_nan);
  tcase_add_test(tcase, test_s21_log_superlarge);
  suite_add_tcase(suite, tcase);

  return suite;
}

Suite *TestFmod(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("fmod");
  tc = tcase_create("Core");
  tcase_add_test(tc, test_fmod_1);
  tcase_add_test(tc, test_nan_1);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_abs_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("abs");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_abs_1);
  tcase_add_test(tc_core, test_abs_2);
  tcase_add_test(tc_core, test_abs_3);
  tcase_add_test(tc_core, test_abs_4);
  tcase_add_test(tc_core, test_abs_5);
  tcase_add_test(tc_core, test_abs_6);
  tcase_add_test(tc_core, test_abs_7);
  tcase_add_test(tc_core, test_abs_8);
  tcase_add_test(tc_core, test_abs_9);
  tcase_add_test(tc_core, test_abs_10);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_sine(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sin");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sin_1);
  tcase_add_test(tc_core, test_sin_2);
  tcase_add_test(tc_core, test_sin_3);
  tcase_add_test(tc_core, test_sin_4);
  tcase_add_test(tc_core, test_sin_5);
  tcase_add_test(tc_core, test_sin_6);
  tcase_add_test(tc_core, test_sin_7);
  tcase_add_test(tc_core, test_sin_8);
  tcase_add_test(tc_core, test_sin_9);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_cosine(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("cos");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cos_1);
  tcase_add_test(tc_core, test_cos_2);
  tcase_add_test(tc_core, test_cos_3);
  tcase_add_test(tc_core, test_cos_4);
  tcase_add_test(tc_core, test_cos_5);
  tcase_add_test(tc_core, test_cos_6);
  tcase_add_test(tc_core, test_cos_7);
  tcase_add_test(tc_core, test_cos_8);
  tcase_add_test(tc_core, test_cos_9);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_fabs_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("fabs");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fabs_1);
  tcase_add_test(tc_core, test_fabs_2);
  tcase_add_test(tc_core, test_fabs_3);
  tcase_add_test(tc_core, test_fabs_4);
  tcase_add_test(tc_core, test_fabs_5);
  tcase_add_test(tc_core, test_fabs_6);
  tcase_add_test(tc_core, test_fabs_7);
  tcase_add_test(tc_core, test_fabs_8);
  tcase_add_test(tc_core, test_fabs_9);
  tcase_add_test(tc_core, test_fabs_10);
  tcase_add_test(tc_core, test_fabs_11);
  tcase_add_test(tc_core, test_fabs_12);
  tcase_add_test(tc_core, test_fabs_13);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_tangent(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("tan");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_tan_1);
  tcase_add_test(tc_core, test_tan_2);
  tcase_add_test(tc_core, test_tan_3);
  tcase_add_test(tc_core, test_tan_4);
  tcase_add_test(tc_core, test_tan_5);
  tcase_add_test(tc_core, test_tan_6);
  tcase_add_test(tc_core, test_tan_7);
  tcase_add_test(tc_core, test_tan_8);
  tcase_add_test(tc_core, test_tan_9);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_pow_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("pow");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_pow_1);
  tcase_add_test(tc_core, test_pow_2);
  tcase_add_test(tc_core, test_pow_3);
  tcase_add_test(tc_core, test_pow_4);
  tcase_add_test(tc_core, test_pow_5);
  tcase_add_test(tc_core, test_pow_6);
  tcase_add_test(tc_core, test_pow_7);
  tcase_add_test(tc_core, test_pow_8);
  tcase_add_test(tc_core, test_pow_9);
  tcase_add_test(tc_core, test_pow_10);
  tcase_add_test(tc_core, test_pow_11);
  tcase_add_test(tc_core, test_pow_12);
  tcase_add_test(tc_core, test_pow_13);
  tcase_add_test(tc_core, test_pow_14);
  tcase_add_test(tc_core, test_pow_15);
  tcase_add_test(tc_core, test_pow_16);
  tcase_add_test(tc_core, test_pow_17);
  tcase_add_test(tc_core, test_pow_18);
  tcase_add_test(tc_core, test_pow_19);
  tcase_add_test(tc_core, test_pow_20);
  tcase_add_test(tc_core, test_pow_21);
  tcase_add_test(tc_core, test_pow_22);
  tcase_add_test(tc_core, test_pow_23);
  tcase_add_test(tc_core, test_pow_24);
  tcase_add_test(tc_core, test_pow_25);
  tcase_add_test(tc_core, test_pow_26);
  tcase_add_test(tc_core, test_pow_27);
  tcase_add_test(tc_core, test_pow_28);
  tcase_add_test(tc_core, test_pow_29);
  tcase_add_test(tc_core, test_pow_30);
  tcase_add_test(tc_core, test_pow_31);
  tcase_add_test(tc_core, test_pow_32);
  suite_add_tcase(s, tc_core);

  return s;
}
Suite *s21_arcsine(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("asin");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_asin_1);
  tcase_add_test(tc_core, test_asin_2);
  tcase_add_test(tc_core, test_asin_3);
  tcase_add_test(tc_core, test_asin_4);
  tcase_add_test(tc_core, test_asin_5);
  tcase_add_test(tc_core, test_asin_6);
  tcase_add_test(tc_core, test_asin_7);
  tcase_add_test(tc_core, test_asin_8);
  tcase_add_test(tc_core, test_asin_9);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_sqrt_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sqrt");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sqrt_1);
  tcase_add_test(tc_core, test_sqrt_2);
  tcase_add_test(tc_core, test_sqrt_3);
  tcase_add_test(tc_core, test_sqrt_4);
  tcase_add_test(tc_core, test_sqrt_5);
  tcase_add_test(tc_core, test_sqrt_6);
  tcase_add_test(tc_core, test_sqrt_7);
  tcase_add_test(tc_core, test_sqrt_8);
  tcase_add_test(tc_core, test_sqrt_9);
  tcase_add_test(tc_core, test_sqrt_10);
  tcase_add_test(tc_core, test_sqrt_11);
  tcase_add_test(tc_core, test_sqrt_12);
  tcase_add_test(tc_core, test_sqrt_13);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_arccosine(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("acos");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_acos_1);
  tcase_add_test(tc_core, test_acos_2);
  tcase_add_test(tc_core, test_acos_3);
  tcase_add_test(tc_core, test_acos_4);
  tcase_add_test(tc_core, test_acos_5);
  tcase_add_test(tc_core, test_acos_6);
  tcase_add_test(tc_core, test_acos_7);
  tcase_add_test(tc_core, test_acos_8);
  tcase_add_test(tc_core, test_acos_9);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_arctangent(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("atan");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_atan_1);
  tcase_add_test(tc_core, test_atan_2);
  tcase_add_test(tc_core, test_atan_3);
  tcase_add_test(tc_core, test_atan_4);
  tcase_add_test(tc_core, test_atan_5);
  tcase_add_test(tc_core, test_atan_6);
  tcase_add_test(tc_core, test_atan_7);
  tcase_add_test(tc_core, test_atan_8);
  tcase_add_test(tc_core, test_atan_9);
  tcase_add_test(tc_core, test_atan_10);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  typedef Suite *(*func)(void);
  func funcs[NUMBER_OF_FUNCS] = {
      &s21_sine,      &s21_cosine,     &s21_tangent,    &s21_arcsine,
      &s21_arccosine, &s21_arctangent, &TestFmod,       &s21_log_suite,
      &s21_exp_suite, &s21_ceil_test,  &s21_floor_test, &s21_abs_test,
      &s21_fabs_test, &s21_pow_test,   &s21_sqrt_test};

  for (int i = 0; i < NUMBER_OF_FUNCS; i++) {
    s = funcs[i]();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
