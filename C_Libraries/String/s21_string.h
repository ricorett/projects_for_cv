#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <wchar.h>
#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;

void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_to_upper(const char *str);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);

char *s21_strcpy(char *str2, const char *str1);
char *s21_strcat(char *str2, const char *str1);

char *s21_strchr(const char *str, int c);
char *s21_strncat(char *dest, const char *src, size_t n);
void *s21_memset(void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);

s21_size_t s21_strcspn(const char *str1, const char *str2);
int s21_sprintf(char *str, const char *format, ...);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

typedef struct sprintf_struct {
  int width;           // число до точки без процента
  int precision;       // количество цифр после точки
  int flag_precision;  // есть ли пресисион
  int length_h_short;
  int length_l_li;  //
  int length_L_lf;
  int flag_left;   // если есть минус
  int flag_zero;   // если стоит 0 в начале |%06d| 5 |000005|
  int flag_plus;   // %+d 5 |+5|
  int flag_space;  // % d 5 | 5|
  int flag_hash;
  int flag_upper_case;  // e E
  int base;
  int written_chars;
} sprintf_config;

typedef struct input_type {
  int isPass;
  int width;
  char specificator;
  int success;
} Input_type;

int assprintf(char *str, const char *format, va_list valist);
void config_length(const char **format, sprintf_config *config);
void config_precision(const char **format, sprintf_config *config,
                      va_list valist);
void config_width(const char **format, sprintf_config *config, va_list valist);
void flags_config(const char **format, sprintf_config *config,
                  int *flags_found);
void c_specs(sprintf_config *config, va_list valist, char *str);
void s21_ctoa(wchar_t value, sprintf_config *config, char *str);
void empty_config(sprintf_config *config);
void s_specs(sprintf_config *config, va_list valist, char *str);
void s21_stoa(char *value, sprintf_config *config, char *str);
void s21_stoa_wide(wchar_t *value, sprintf_config *config, char *str);
void config_int(const char **format, sprintf_config *config);
void int_specs(sprintf_config *config, va_list valist, char *str, char format);
void s21_atoi(unsigned long int value, char *temp, int base, int is_upper_hex,
              int isNegative);
void s21_itoa(unsigned long int value, sprintf_config *config, char *str,
              int isNegative);
void f_specs(sprintf_config *config, va_list valist, char *str);
void s21_ftoa(long double value, sprintf_config *config, char *str);
void s21_ftoi(long double value, char *temp, sprintf_config *config);
void s21_etoa(long double value, sprintf_config *config, char *str);
void e_specs(sprintf_config *config, va_list valist, char *str);
void g_specs(sprintf_config *config, va_list valist, char *str);
void s21_gtoa(long double value, sprintf_config *config, char *str);
void remove_succeeding_zeros(char *ftoa, char *etoa, int ftoa_size,
                             int etoa_size);
void s21_ftoa_without_format(long double value, sprintf_config *config,
                             char *str);
void s21_etoa_without_format(long double value, sprintf_config *config,
                             char *str);
void handler_flags(va_list *args, const char **str, Input_type *input_type,
                   const char **format, int all_symbols_count,
                   long *cycle_symbols_count);
void format_gtoa(char *temp, sprintf_config *config, char *str);
char *s21_strerror(int errnum);
char *s21_strtok(char *str, const char *delim);
void *s21_to_lower(const char *str);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_sscanf(const char *str, const char *format, ...);
int handle_d(va_list *args, const char **str, Input_type *input_type);
int handle_c(va_list *args, const char **str, Input_type *input_type);
int handle_s(va_list *args, const char **str, Input_type *input_type);
int handle_f(va_list *args, const char **str, Input_type *input_type);
int handle_e(const char **str, Input_type *input_type, long double *result,
             int *symbolCount);
int handle_o(va_list *args, const char **str, Input_type *input_type);
int handle_u(va_list *args, const char **str, Input_type *input_type);
int handle_i(va_list *args, const char **str, Input_type *input_type);
int handle_x(va_list *args, const char **str, Input_type *input_type);
int handle_p(va_list *args, const char **str, Input_type *input_type);
void handle_n(va_list *args, long all_symbols_count, Input_type *input_type);
long read_hex(const char **str, Input_type *input_type, int *symbol_count);
void check_flag_H_and_L(va_list *args, Input_type *input_type,
                        long int *result);
void check_flag_H_and_L_for_double(va_list *args, Input_type *input_type,
                                   long double *result);
long int s21_atoi_sscanf(const char **str, Input_type *input_type,
                         int *symbol_count);
int findStartIndex(const char *src, const char *trim_chars);
int findEndIndex(const char *src, const char *trim_chars);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);

#endif
