#include "s21_string.h"

#include <math.h>
#include <stdlib.h>

void *s21_to_upper(const char *str) {
  char *new_str = s21_NULL;
  if (str) {
    int str_len = s21_strlen(str);
    new_str = malloc((str_len + 1) * sizeof(char));
    int pos = 0;
    for (; pos < str_len; ++pos) {
      if (str[pos] >= 'a' && str[pos] <= 'z') {
        new_str[pos] = str[pos] - ('a' - 'A');
      } else {
        new_str[pos] = str[pos];
      }
    }
    new_str[pos] = '\0';
  }
  return (void *)new_str;
}
void *s21_to_lower(const char *str) {
  s21_size_t length_of_str = s21_strlen(str);
  int diff_between_cases = 32, ascii_of_start_uppercase = 65,
      ascii_of_end_uppercase = 90;
  char *new_str = (char *)malloc(sizeof(char) * (length_of_str + 1));
  if (new_str != s21_NULL) {
    s21_size_t i = 0;
    for (; i < length_of_str; ++i) {
      char letter = str[i];
      if (letter >= ascii_of_start_uppercase &&
          letter <= ascii_of_end_uppercase) {
        letter += diff_between_cases;
      }
      new_str[i] = letter;
    }
    new_str[i] = '\0';
  }
  return (void *)new_str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;
  if (str1 && str2) {
    for (; str1[i] && str1[i] == str2[i] && i < n - 1; ++i)
      ;
  }
  return (str1 && str2) ? str1[i] - str2[i] : 0;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char pattern[256] = {0};
  int match_found = 0, pos;

  if (str1 && str2) {
    for (int i = 0; str2[i]; ++i) {
      pattern[(unsigned char)str2[i]] = 1;
    }

    for (pos = 0; str1[pos]; ++pos) {
      if (pattern[(unsigned char)str1[pos]]) {
        match_found = 1;
        break;
      }
    }
  }

  return match_found ? (char *)&str1[pos] : s21_NULL;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_src = s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index <= src_len && src != s21_NULL && str != s21_NULL) {
    new_src = (char *)calloc((str_len + src_len + 1), sizeof(char));
    s21_memcpy(new_src, src, start_index);
    s21_strcat(new_src, str);
    s21_strncat(new_src, src + start_index, src_len - start_index);
  }

  return (void *)new_src;
}

char *s21_strcpy(char *str2, const char *str1) {
  int len = s21_strlen(str1) + 1;
  for (int i = 0; i < len; i++) {
    str2[i] = str1[i];
  }
  return str2;
}

char *s21_strcat(char *str2, const char *str1) {
  int i = s21_strlen(str2);
  s21_strcpy(str2 + i, str1);
  return str2;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  if (dest && src) {
    size_t dest_len = s21_strlen(dest);
    s21_strncpy(&dest[dest_len], src, n);
    dest[dest_len + n] = '\0';
  }

  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  char *tmp = str;

  if (str) {
    for (size_t i = 0; i < n; ++i) {
      tmp[i] = (unsigned char)c;
    }
  }

  return tmp;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  int tmp = -1;

  if (str1 && str2) {
    tmp = 0;

    const unsigned char *byte1 = (const unsigned char *)str1;
    const unsigned char *byte2 = (const unsigned char *)str2;

    for (size_t i = 0; i < n && !tmp; ++i) {
      unsigned char ch1 = byte1[i];
      unsigned char ch2 = byte2[i];

      if (ch1 != ch2) {
        tmp = ch1 - ch2;
      }
    }
  }

  return tmp;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str) {
    for (; *str; ++len, str++)
      ;
  }
  return len;
}

char *s21_strchr(const char *str, int c) {
  const char *tmp = str;
  int found = 0;
  int count = -1;

  if (str) {
    while (*str && !found) {
      if (*str == c) {
        found = 1;
      }

      ++count;
      ++str;
    }

    if (!found && (*str == c)) {
      ++count;
      found = 1;
    }
  }

  return found ? (char *)(tmp + count) : s21_NULL;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  unsigned int len = 0;

  if ((str1 == s21_NULL) || (str2 == s21_NULL)) return len;
  while (*str1) {
    if (s21_strchr(str2, *str1)) {
      break;
    } else {
      ++str1;
      ++len;
    }
  }

  return len;
}

// g and e

int s21_sprintf(char *str, const char *format, ...) {
  if (str == s21_NULL || format == s21_NULL) return -1;
  va_list valist;
  va_start(valist, format);
  int written_chars = assprintf(str, format, valist);
  str[written_chars] = '\0';
  va_end(valist);
  return written_chars;
}

int assprintf(char *str, const char *format, va_list valist) {
  sprintf_config config = {0};
  while (*format) {
    if (*format != '%') {
      str[config.written_chars++] = *format++;
      continue;
    }
    format++;
    int flags_found = 1;
    while (flags_found) {
      flags_found = 0;
      flags_config(&format, &config, &flags_found);
    }
    config_width(&format, &config, valist);
    config_precision(&format, &config, valist);
    config_length(&format, &config);
    if (*format == 'c') {
      c_specs(&config, valist, str);
    } else if (s21_strchr("iduxXo", *format)) {
      config_int(&format, &config);
      int_specs(&config, valist, str, *format);
    } else if (*format == 'f') {
      f_specs(&config, valist, str);
    } else if (*format == 'e' || *format == 'E') {
      if (*format == 'E') config.flag_upper_case = 1;
      e_specs(&config, valist, str);
    } else if (*format == 'g' || *format == 'G') {
      if (*format == 'E') config.flag_upper_case = 1;
      g_specs(&config, valist, str);
    } else if (*format == 's') {
      s_specs(&config, valist, str);
    } else if (*format == 'p') {
      config.base = 16;
      config.flag_plus = 0;
      config.flag_hash = 1;
      s21_itoa((unsigned long int)va_arg(valist, void *), &config, str, 0);
    } else if (*format == '%') {
      str[config.written_chars++] = '%';
    }
    format++;
    empty_config(&config);
  }
  return config.written_chars;
}

void s21_gtoa(long double value, sprintf_config *config, char *str) {
  char ftoa[1024] = {0}, etoa[1024] = {0}, temp[1024] = {0};
  s21_ftoa_without_format(value, config, ftoa);
  int ftoa_size = s21_strlen(ftoa);
  s21_etoa_without_format(value, config, etoa);
  int etoa_size = s21_strlen(etoa);
  remove_succeeding_zeros(ftoa, etoa, ftoa_size, etoa_size);
  int new_ftoa_size = 0, new_etoa_size = 0;
  int e_exponent = (etoa[etoa_size - 1] - '0') + (etoa[etoa_size - 2] - '0');
  if (e_exponent <= -4 || e_exponent >= config->precision) {
    new_etoa_size = -1;
  }
  int index = 0;
  if (new_etoa_size < new_ftoa_size) {
    for (int i = 0; i < etoa_size; ++i) {
      if (etoa[i] != 'a') temp[index++] = etoa[i];
    }
  } else {
    for (int i = 0; i < ftoa_size; ++i) {
      if (ftoa[i] != 'a') temp[index++] = ftoa[i];
    }
  }
  if (temp[s21_strlen(temp) - 1] == '.') temp[s21_strlen(temp) - 1] = '\0';
  format_gtoa(temp, config, str);
}

void format_gtoa(char *temp, sprintf_config *config, char *str) {
  int border = config->width - s21_strlen(temp);
  if (config->flag_space) {
    str[config->written_chars++] = ' ';
    border--;
  }
  if (config->flag_plus) border--;
  if (!config->flag_left) {
    for (int i = 0; i < border; ++i)
      str[config->written_chars++] = config->flag_zero ? '0' : ' ';
  }
  if (config->flag_plus && temp[0] != '-') str[config->written_chars++] = '+';
  for (char *ch = temp; *ch; ++ch) {
    str[config->written_chars++] = *ch;
  }
  if (config->flag_left) {
    for (int i = 0; i < border; ++i)
      str[config->written_chars++] = config->flag_zero ? '0' : ' ';
  }
}

void remove_succeeding_zeros(char *ftoa, char *etoa, int ftoa_size,
                             int etoa_size) {
  int ftoapos1 = 0, ftoapos2 = 0, etoapos1 = 0, etoapos2 = 0, pos_of_e = 0;
  ;
  for (ftoapos1 = ftoa_size - 1; ftoapos1 >= 0 && ftoa[ftoapos1] == '0';
       --ftoapos1)
    ;
  if (ftoapos1) ftoapos2 = ftoa_size - 1;
  ++ftoapos1;
  for (int i = ftoapos1; i <= ftoapos2; ++i) {
    ftoa[i] = 'a';
  }
  int e_found = 0;
  for (etoapos1 = etoa_size - 1; etoapos1 >= 0 && !e_found; --etoapos1) {
    if (etoa[etoapos1] == 'e' || etoa[etoapos1] == 'E') e_found = 1;
  }
  pos_of_e = etoapos1;
  for (; etoapos1 >= 0 && etoa[etoapos1] == '0'; --etoapos1)
    ;
  ++etoapos1;
  if (etoapos1) etoapos2 = pos_of_e;
  for (int i = etoapos1; i <= etoapos2; ++i) {
    etoa[i] = 'a';
  }
  if (etoa[1] == '.' && etoa[2] == 'a') etoa[1] = 'a';
}

void g_specs(sprintf_config *config, va_list valist, char *str) {
  if (config->length_L_lf) {
    long double value = va_arg(valist, long double);
    s21_gtoa(value, config, str);
  } else {
    double value = va_arg(valist, double);
    s21_gtoa(value, config, str);
  }
}

void isNegativeFunc(long double *a, int *neg) {
  if (*a < 0.0) {
    *neg = 1;
    *a = -*a;
  }
}

void counterCheck(size_t *counter_after_e, sprintf_config *config, char *str) {
  if (*counter_after_e >= 10) {
    double copy = *counter_after_e;
    while ((int)copy >= 10) {
      copy /= 10;
    }
    int d = copy - (int)copy;
    while (d != 0) {
      str[config->written_chars++] = (int)d + '0';
      d *= 10;
      d = d - (int)d;
    }
  } else {
    str[config->written_chars++] = '0';
    str[config->written_chars++] = *counter_after_e + '0';
  }
}

void s21_etoa(long double a, sprintf_config *config, char *str) {
  size_t counter_after_e = 0,
         chars_after_dot = config->flag_precision ? config->precision : 6;
  int isNegative = 0;
  isNegativeFunc(&a, &isNegative);
  while ((int)a >= 10) {
    ++counter_after_e;
    a /= 10;
  }
  int border = 0;
  if (config->flag_space) {
    str[config->written_chars++] = ' ';
    --border;
  }
  if (isNegative) --border;
  if (!config->flag_left) {
    border += config->width - 6 - chars_after_dot;
    for (int i = 0; i < border; ++i)
      str[config->written_chars++] = config->flag_zero ? '0' : ' ';
  }
  if (isNegative) str[config->written_chars++] = '-';
  if (config->flag_plus && !isNegative) str[config->written_chars++] = '+';
  a = round(a * pow(10, chars_after_dot)) / pow(10, chars_after_dot);
  str[config->written_chars++] = (int)a + '0';
  if (chars_after_dot != 0) str[config->written_chars++] = '.';
  double d = a - (int)a;
  for (size_t i = 0; i != chars_after_dot; ++i) {
    d *= 10;
    str[config->written_chars++] = (int)d + '0';
    d = d - (int)d;
  }
  str[config->written_chars++] = config->flag_upper_case ? 'E' : 'e';
  str[config->written_chars++] = '+';
  counterCheck(&counter_after_e, config, str);
  if (config->flag_left) {
    border += config->width - 6 - chars_after_dot;
    for (int i = 0; i < border; ++i)
      str[config->written_chars++] = config->flag_zero ? '0' : ' ';
  }
}

void e_specs(sprintf_config *config, va_list valist, char *str) {
  if (config->length_L_lf) {
    long double value = va_arg(valist, long double);
    s21_etoa(value, config, str);
  } else {
    double value = va_arg(valist, double);
    s21_etoa(value, config, str);
  }
}

void f_specs(sprintf_config *config, va_list valist, char *str) {
  if (config->length_L_lf) {
    long double value = va_arg(valist, long double);
    s21_ftoa(value, config, str);
  } else {
    double value = va_arg(valist, double);
    s21_ftoa(value, config, str);
  }
}

void s21_etoa_without_format(long double a, sprintf_config *config, char *str) {
  size_t counter_after_e = 0,
         chars_after_dot = config->flag_precision ? config->precision : 6;

  int isNegative = 0;
  if (a < 0.0) {
    isNegative = 1;
    a = -a;
  }
  while ((int)a >= 10) {
    ++counter_after_e;
    a /= 10;
  }
  int index = 0;
  if (isNegative) str[index++] = '-';
  a = round(a * pow(10, chars_after_dot)) / pow(10, chars_after_dot);
  str[index++] = (int)a + '0';
  if (chars_after_dot != 0) str[index++] = '.';
  double d = a - (int)a;
  for (size_t i = 0; i != chars_after_dot; ++i) {
    d *= 10;
    str[index++] = (int)d + '0';
    d = d - (int)d;
  }
  str[index++] = config->flag_upper_case ? 'E' : 'e';
  str[index++] = '+';
  if (counter_after_e >= 10) {
    double copy = counter_after_e;
    while ((int)copy >= 10) {
      copy /= 10;
    }
    d = copy - (int)copy;
    while (d != 0) {
      str[index++] = (int)d + '0';
      d *= 10;
      d = d - (int)d;
    }
  } else {
    str[index++] = '0';
    str[index++] = counter_after_e + '0';
  }
}

void s21_ftoa_without_format(long double value, sprintf_config *config,
                             char *str) {
  char temp[1024];
  s21_ftoi(value, temp, config);
  int numberLength = s21_strlen(temp);
  for (int i = 0; i < numberLength; ++i) {
    str[i] = temp[i];
  }
}

void s21_ftoa(long double value, sprintf_config *config, char *str) {
  char temp[1024];
  int padding = 0;
  if (config->flag_space && config->flag_plus) config->flag_space = 0;
  s21_ftoi(value, temp, config);
  int numberLength = s21_strlen(temp);
  padding = config->width - numberLength;
  if ((config->flag_plus && temp[0] != '-') || config->flag_space) padding--;
  if (config->flag_space) str[config->written_chars++] = ' ';
  if (!config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = config->flag_zero ? '0' : ' ';
    }
  }
  if (config->flag_plus && temp[0] != '-') str[config->written_chars++] = '+';
  for (int i = 0; i < numberLength; ++i) {
    str[config->written_chars++] = temp[i];
  }
  if (config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
}

void s21_ftoi(long double value, char *temp, sprintf_config *config) {
  int isNegative = 0;
  if (value < 0.0) {
    value = -value;
    isNegative = 1;
  }
  unsigned long int whole = (unsigned long int)value;
  long double fract = value - whole;
  if (config->flag_precision && config->precision == 0 &&
      (int)(fract * 10) >= 5)
    ++whole;
  if (!config->flag_precision) config->precision = 6;
  s21_atoi(whole, temp, 10, 0, isNegative);
  int index = s21_strlen(temp);
  if (config->precision != 0) temp[index++] = '.';
  for (int i = 0; i < config->precision; ++i) {
    fract *= 10;
    int digit = (int)fract;
    temp[index++] = digit + '0';
    fract -= digit;
  }
  temp[index] = '\0';
}

void int_specs(sprintf_config *config, va_list valist, char *str, char format) {
  int isNegative = 0;
  if (format == 'i' || format == 'd') {
    if (config->length_h_short) {
      int value_temp = va_arg(valist, int);
      if (value_temp < 0) {
        int value = -value_temp;
        isNegative = 1;
        s21_itoa((short int)value, config, str, isNegative);
      } else {
        unsigned int value = value_temp;
        s21_itoa((unsigned short int)value, config, str, isNegative);
      }
    } else {
      if (config->length_l_li) {
        long long int value_temp = va_arg(valist, long long int);
        if (value_temp < 0) {
          long int value = -value_temp;
          isNegative = 1;
          s21_itoa(value, config, str, isNegative);
        } else {
          unsigned long int value = value_temp;
          s21_itoa(value, config, str, isNegative);
        }
      } else {
        int value = va_arg(valist, int);
        if (value < 0) {
          value = -value;
          isNegative = 1;
        }
        s21_itoa(value, config, str, isNegative);
      }
    }
  } else {
    if (config->length_l_li) {
      s21_itoa(va_arg(valist, long int), config, str, isNegative);
    } else if (config->length_h_short) {
      s21_itoa((unsigned short int)va_arg(valist, int), config, str,
               isNegative);
    } else {
      s21_itoa(va_arg(valist, int), config, str, isNegative);
    }
  }
}

void s21_itoa(unsigned long int value, sprintf_config *config, char *str,
              int isNegative) {
  char temp[1024];
  if (config->flag_space && config->flag_plus) config->flag_space = 0;
  s21_atoi(value, temp, config->base, config->flag_upper_case, isNegative);
  int numberLength = s21_strlen(temp);
  int width = config->width;
  if (config->precision >= width) width = config->precision;
  int padding = width - numberLength;
  if ((config->flag_plus && !isNegative) || config->flag_space) padding--;
  if (config->flag_hash) padding -= 2;
  if (config->flag_space) str[config->written_chars++] = ' ';
  if (!config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = config->flag_zero ? '0' : ' ';
    }
  }
  if (config->flag_plus && !isNegative) str[config->written_chars++] = '+';
  if (config->flag_hash) {
    str[config->written_chars++] = '0';
    if (config->flag_upper_case && config->base != 8) {
      str[config->written_chars++] = 'X';
    } else if (config->base != 8) {
      str[config->written_chars++] = 'x';
    }
  }
  for (int i = 0; i < numberLength; ++i) {
    str[config->written_chars++] = temp[i];
  }
  if (config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
}

void s21_atoi(unsigned long int value, char *temp, int base, int is_upper_hex,
              int isNegative) {
  int index = 0;

  while (value) {
    temp[index++] = (value % base >= 10)
                        ? (is_upper_hex ? (value % base + 'A' - 10)
                                        : (value % base + 'a' - 10))
                        : (value % base) + '0';
    value /= base;
  }

  if (isNegative && base != 16 && base != 8) temp[index++] = '-';

  temp[index] = '\0';
  int length = s21_strlen(temp);
  for (int i = 0; i < length / 2; ++i) {
    char tmp = temp[i];
    temp[i] = temp[length - i - 1];
    temp[length - i - 1] = tmp;
  }
}

void config_int(const char **format, sprintf_config *config) {
  if (**format == 'x' || **format == 'X') {
    config->base = 16;
    if (**format == 'X') config->flag_upper_case = 1;
  } else if (**format == 'o') {
    config->base = 8;
  } else {
    config->base = 10;
    config->flag_hash = 0;
  }

  if (**format != 'i' && **format != 'd') {
    config->flag_plus = 0;
    config->flag_space = 0;
  }

  if (config->precision >= config->width) {
    config->flag_zero = 1;
  }
}

void s_specs(sprintf_config *config, va_list valist, char *str) {
  if (config->length_l_li) {
    s21_stoa_wide(va_arg(valist, wchar_t *), config, str);
  } else {
    s21_stoa(va_arg(valist, char *), config, str);
  }
}

void s21_stoa(char *value, sprintf_config *config, char *str) {
  int padding = 0;
  int prec_length = 0;
  int str_length = s21_strlen(value);
  if (config->flag_precision) prec_length = config->precision;
  if (prec_length < str_length && config->flag_precision)
    str_length = prec_length;
  if (config->width > str_length) padding = config->width - str_length;
  if (!config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
  for (int i = 0; i < str_length; ++i) {
    str[config->written_chars++] = *value++;
  }
  if (config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
}

void s21_stoa_wide(wchar_t *value, sprintf_config *config, char *str) {
  int padding = 0;
  int size = wcstombs(s21_NULL, value, MB_CUR_MAX * wcslen(value));
  char temp[size];
  int widechars =
      wcstombs(temp, value, config->flag_precision ? config->precision : size);
  if (config->width > widechars) padding = config->width - widechars;
  if (!config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
  for (int i = 0; i < widechars; ++i) {
    str[config->written_chars++] = temp[i];
  }
  if (config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
}

void c_specs(sprintf_config *config, va_list valist, char *str) {
  if (config->length_l_li) {
    s21_ctoa(va_arg(valist, wchar_t), config, str);
  } else {
    s21_ctoa(va_arg(valist, int), config, str);
  }
}

void s21_ctoa(wchar_t value, sprintf_config *config, char *str) {
  int padding = 0;
  char temp[MB_CUR_MAX];
  int widechars = wctomb(temp, value);
  if (config->width > 1) padding = config->width - widechars;
  if (!config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
  for (int i = 0; i < widechars; ++i) {
    str[config->written_chars++] = temp[i];
  }
  if (config->flag_left) {
    for (int i = 0; i < padding; ++i) {
      str[config->written_chars++] = ' ';
    }
  }
}

void config_length(const char **format, sprintf_config *config) {
  if (**format == 'h') {
    config->length_h_short = 1;
    (*format)++;
  } else if (**format == 'l') {
    config->length_l_li = 1;
    (*format)++;
  } else if (**format == 'L') {
    config->length_L_lf = 1;
    (*format)++;
  }
}

void config_precision(const char **format, sprintf_config *config,
                      va_list valist) {
  if (**format == '.') {
    config->precision = 0;
    config->flag_precision = 1;
    (*format)++;
    if (**format == '*') {
      config->precision = va_arg(valist, int);
      (*format)++;
    } else {
      while (**format >= '0' && **format <= '9') {
        config->precision = config->precision * 10 + (**format - '0');
        (*format)++;
      }
    }
  }
}

void config_width(const char **format, sprintf_config *config, va_list valist) {
  if (**format == '*') {
    config->width = va_arg(valist, int);
    (*format)++;
  } else {
    while (**format >= '0' && **format <= '9') {
      config->width = config->width * 10 + (**format - '0');
      (*format)++;
    }
  }
}

void flags_config(const char **format, sprintf_config *config,
                  int *flags_found) {
  if (**format == '-') {
    config->flag_left = 1;
    (*format)++;
    *flags_found = 1;
  } else if (**format == '+') {
    config->flag_plus = 1;
    (*format)++;
    *flags_found = 1;
  } else if (**format == '0') {
    config->flag_zero = 1;
    (*format)++;
    *flags_found = 1;
  } else if (**format == ' ') {
    config->flag_space = 1;
    (*format)++;
    *flags_found = 1;
  } else if (**format == '#') {
    config->flag_hash = 1;
    (*format)++;
    *flags_found = 1;
  }
}

void empty_config(sprintf_config *config) {
  config->width = config->precision = config->length_h_short =
      config->length_l_li = config->length_L_lf = config->flag_left =
          config->flag_zero = config->flag_plus = config->flag_space =
              config->flag_hash = config->flag_upper_case = config->base = 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *ptrDest = (char *)dest;
  const char *ptrSource = (const char *)src;

  if ((ptrDest) && (ptrSource)) {
    while (n) {
      *(ptrDest++) = *(ptrSource++);
      --n;
    }
  } else {
    return s21_NULL;
  }
  return (void *)ptrDest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (; i < n; ++i) {
    dest[i] = src[i];
    if (src[i] == '\0') {
      break;
    }
  }
  dest[i] = '\0';

  return dest;
}
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *ch = s21_NULL;
  if (str) {
    for (s21_size_t i = 0; i < n; ++i) {
      if (*(char *)str == c) {
        ch = (char *)str;
        break;
      }
      str = (char *)str + 1;
    }
  }
  return ch;
}

char isDelim(char c, const char *delim) {
  char result = 0;
  while (*delim != '\0') {
    if (c == *delim) {
      result = 1;
      break;
    }
    ++delim;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *prev_string;
  char *return_value = s21_NULL;
  if (!str) {
    str = prev_string;
  }
  if (str) {
    while (isDelim(*str, delim)) ++str;
    if (*str != '\0') {
      return_value = str;
      while (!(isDelim(*str, delim) || *str == '\0')) ++str;
      prev_string = *str == '\0' ? str : str + 1;
      *str = '\0';
    }
  }
  return return_value;
}

#ifdef __APPLE__
#define COUNT_OF_ERRORS 107
char *errors[107] = {
    "Unknown error: 0",  // for equality of errno and index of array
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#endif  // for mac os x

#ifdef __unix__
#define COUNT_OF_ERRORS 134
char *errors[134] = {"Success",  // for equality of errno and index of array
                     "Operation not permitted",
                     "No such file or directory",
                     "No such process",
                     "Interrupted system call",
                     "Input/output error",
                     "No such device or address",
                     "Argument list too long",
                     "Exec format error",
                     "Bad file descriptor",
                     "No child processes",
                     "Resource temporarily unavailable",
                     "Cannot allocate memory",
                     "Permission denied",
                     "Bad address",
                     "Block device required",
                     "Device or resource busy",
                     "File exists",
                     "Invalid cross-device link",
                     "No such device",
                     "Not a directory",
                     "Is a directory",
                     "Invalid argument",
                     "Too many open files in system",
                     "Too many open files",
                     "Inappropriate ioctl for device",
                     "Text file busy",
                     "File too large",
                     "No space left on device",
                     "Illegal seek",
                     "Read-only file system",
                     "Too many links",
                     "Broken pipe",
                     "Numerical argument out of domain",
                     "Numerical result out of range",
                     "Resource deadlock avoided",
                     "File name too long",
                     "No locks available",
                     "Function not implemented",
                     "Directory not empty",
                     "Too many levels of symbolic links",
                     "Unknown error 41",
                     "No message of desired type",
                     "Identifier removed",
                     "Channel number out of range",
                     "Level 2 not synchronized",
                     "Level 3 halted",
                     "Level 3 reset",
                     "Link number out of range",
                     "Protocol driver not attached",
                     "No CSI structure available",
                     "Level 2 halted",
                     "Invalid exchange",
                     "Invalid request descriptor",
                     "Exchange full",
                     "No anode",
                     "Invalid request code",
                     "Invalid slot",
                     "Unknown error 58",
                     "Bad font file format",
                     "Device not a stream",
                     "No data available",
                     "Timer expired",
                     "Out of streams resources",
                     "Machine is not on the network",
                     "Package not installed",
                     "Object is remote",
                     "Link has been severed",
                     "Advertise error",
                     "Srmount error",
                     "Communication error on send",
                     "Protocol error",
                     "Multihop attempted",
                     "RFS specific error",
                     "Bad message",
                     "Value too large for defined data type",
                     "Name not unique on network",
                     "File descriptor in bad state",
                     "Remote address changed",
                     "Can not access a needed shared library",
                     "Accessing a corrupted shared library",
                     ".lib section in a.out corrupted",
                     "Attempting to link in too many shared libraries",
                     "Cannot exec a shared library directly",
                     "Invalid or incomplete multibyte or wide character",
                     "Interrupted system call should be restarted",
                     "Streams pipe error",
                     "Too many users",
                     "Socket operation on non-socket",
                     "Destination address required",
                     "Message too long",
                     "Protocol wrong type for socket",
                     "Protocol not available",
                     "Protocol not supported",
                     "Socket type not supported",
                     "Operation not supported",
                     "Protocol family not supported",
                     "Address family not supported by protocol",
                     "Address already in use",
                     "Cannot assign requested address",
                     "Network is down",
                     "Network is unreachable",
                     "Network dropped connection on reset",
                     "Software caused connection abort",
                     "Connection reset by peer",
                     "No buffer space available",
                     "Transport endpoint is already connected",
                     "Transport endpoint is not connected",
                     "Cannot send after transport endpoint shutdown",
                     "Too many references: cannot splice",
                     "Connection timed out",
                     "Connection refused",
                     "Host is down",
                     "No route to host",
                     "Operation already in progress",
                     "Operation now in progress",
                     "Stale file handle",
                     "Structure needs cleaning",
                     "Not a XENIX named type file",
                     "No XENIX semaphores available",
                     "Is a named type file",
                     "Remote I/O error",
                     "Disk quota exceeded",
                     "No medium found",
                     "Wrong medium type",
                     "Operation canceled",
                     "Required key not available",
                     "Key has expired",
                     "Key has been revoked",
                     "Key was rejected by service",
                     "Owner died",
                     "State not recoverable",
                     "Operation not possible due to RF-kill",
                     "Memory page has hardware error"};
#endif  // for unix

char *s21_strerror(int errnum) {
  static char msg_for_unknown_error[1000];
  s21_sprintf(msg_for_unknown_error, "Unknown error: %d", errnum);
  return errnum >= 0 && errnum <= COUNT_OF_ERRORS ? errors[errnum]
                                                  : msg_for_unknown_error;
}

void handler_flags(va_list *args, const char **str, Input_type *input_type,
                   const char **format, int all_symbols_count,
                   long *cycle_symbols_count) {
  const char *nums = "0123456789";
  if (**format == '*')
    input_type->isPass = 1;
  else if (s21_strchr(nums, **format))  // isDigit
  {
    if (input_type->width == -1)
      input_type->width = (**format - '0');
    else
      input_type->width = input_type->width * 10 + (**format - '0');
  } else if (**format == 'h' || **format == 'l' || **format == 'L')
    input_type->specificator = **format;
  else if (**format == 'd') {
    *cycle_symbols_count += handle_d(args, str, input_type);
  } else if (**format == 'c') {
    *cycle_symbols_count += handle_c(args, str, input_type);
  } else if (**format == 's')
    *cycle_symbols_count += handle_s(args, str, input_type);
  else if (s21_strchr("fgGeE", **format)) {
    *cycle_symbols_count += handle_f(args, str, input_type);
  } else if (**format == 'u')
    *cycle_symbols_count += handle_u(args, str, input_type);
  else if (**format == 'o')
    *cycle_symbols_count += handle_o(args, str, input_type);
  else if (**format == 'X' || **format == 'x')
    *cycle_symbols_count += handle_x(args, str, input_type);
  else if (**format == 'i')
    cycle_symbols_count += handle_i(args, str, input_type);
  else if (**format == 'p')
    *cycle_symbols_count += handle_p(args, str, input_type);
  else if (**format == 'n')
    handle_n(args, all_symbols_count + *cycle_symbols_count + 1, input_type);
  else if (**format == '%') {
    while (**str == ' ' || **str == '%') {
      ++(*str);
    }
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  int result = 0;
  va_list args;
  long all_symbols_count = 0;
  const char *specificator = "cdieEfgGosuxXpnLlh%*";
  const char *nums = "0123456789";
  va_start(args, format);
  while (*format != '\0') {
    Input_type input_type = {0, -1, '\0', 0};
    if (*format == '%') {
      ++format;
      long cycle_symbols_count = 0;
      while (*format != '\0' &&
             (s21_strchr(specificator, *format) || s21_strchr(nums, *format))) {
        handler_flags(&args, &str, &input_type, &format, all_symbols_count,
                      &cycle_symbols_count);
        format++;
      }
      if (!input_type.success) break;
      result += input_type.success;
      str += cycle_symbols_count;
      all_symbols_count += cycle_symbols_count;
    }
    if (*format != '\0') ++format;
  }
  va_end(args);
  return result ? result : -1;
}

int handle_d(va_list *args, const char **str, Input_type *input_type) {
  int symbolCount = 0;
  long int res = s21_atoi_sscanf(str, input_type, &symbolCount);
  if (input_type->isPass == 0) {
    check_flag_H_and_L(args, input_type, &res);
    input_type->success += 1;
  }
  input_type->width = -1;
  input_type->isPass = 0;
  input_type->specificator = '\0';
  return symbolCount;
}
int handle_c(va_list *args, const char **str, Input_type *input_type) {
  int symbolCount = 0;
  if (input_type->width > 0)
    symbolCount += handle_s(args, str, input_type);
  else if (!input_type->isPass) {
    if (input_type->specificator == 'l') {
      wchar_t *destination = va_arg(*args, wchar_t *);
      *destination = (wchar_t)(**str);
      ++destination;
      ++(*str);
      input_type->specificator = '\0';
    } else {
      char *destination = va_arg(*args, char *);
      *destination = **str;
      ++destination;
      ++(*str);
    }
    input_type->success += 1;
    ++symbolCount;

  } else {
    ++(*str);
    input_type->isPass = 0;
  }
  input_type->width = -1;
  return symbolCount;
}
int handle_s(va_list *args, const char **str, Input_type *input_type) {
  int symbolCount = 0;
  while (**str == ' ' || **str == '\n') {
    (*str)++;
    ++symbolCount;
  }
  if (!input_type->isPass) {
    if (input_type->specificator == 'l') {
      wchar_t *destination = va_arg(*args, wchar_t *);
      while (**str && **str != ' ' && **str != '\n' && input_type->width != 0) {
        ++symbolCount;
        *destination = (wchar_t)(**str);
        destination++;
        (*str)++;
        input_type->width--;
      }
      *destination = '\0';
      input_type->specificator = '\0';
      input_type->success += 1;
    } else {
      char *destination = va_arg(*args, char *);
      while (**str && **str != ' ' && **str != '\n' && input_type->width != 0) {
        ++symbolCount;
        *destination = **str;
        (*str)++;
        destination++;
        input_type->width--;
      }
      *destination = '\0';
      input_type->success += 1;
    }
  } else {
    while (**str && **str != ' ' && **str != '\n' && input_type->width != 0) {
      ++symbolCount;
      ++(*str);
      input_type->width--;
    }
    input_type->isPass = 0;
  }
  input_type->width = -1;
  return symbolCount;
}
int handle_f(va_list *args, const char **str, Input_type *input_type) {
  int symbolCount = 0;
  int sign = 1;
  const char *tmp = *str;
  while (*tmp == ' ') ++tmp;
  if (*tmp == '-') sign = -1;
  long int to_dot = s21_atoi_sscanf(str, input_type, &symbolCount);
  long double result = to_dot;
  if (**str == '.') {
    (*str)++;
    int symbolCountRight = 0;
    long double after_dot = s21_atoi_sscanf(str, input_type, &symbolCountRight);
    for (int i = symbolCountRight; i > 0; --i) after_dot /= 10;
    if (!symbolCountRight && !symbolCount && sign == -1)
      result = -0.0;
    else if (sign == -1)
      result -= after_dot;
    else
      result += after_dot;
    symbolCount = symbolCountRight + 1;
  }
  if (**str == 'e' || **str == 'E') {
    handle_e(str, input_type, &result, &symbolCount);
  }
  if (input_type->isPass == 0) {
    check_flag_H_and_L_for_double(args, input_type, &result);
    input_type->success += 1;
  }
  input_type->isPass = 0;
  input_type->specificator = '\0';
  return symbolCount;
}

int handle_e(const char **str, Input_type *input_type, long double *result,
             int *symbolCount) {
  ++(*str);
  input_type->width--;
  int countSymbolsE = 1;  // 'e' is counted already

  // gets the number after "e+" or "e-", always positive
  int n = s21_atoi_sscanf(str, input_type, &countSymbolsE);

  if (n >= 0) {
    while (n--) *result *= 10.0;
  } else if (n < 0) {
    while (n++) *result /= 10.0;
  }
  *symbolCount += countSymbolsE;
  return countSymbolsE;
}

int handle_o(va_list *args, const char **str, Input_type *input_type) {
  int symbol_count = 0;
  long octal = s21_atoi_sscanf(str, input_type, &symbol_count);
  long decimal = 0;
  while (**str != '\0' &&
         (**str == ' ' || **str == '-' || **str == '+' || **str == '0'))
    (*str)++;
  int i = 0;
  while (octal != 0 && input_type->width != 0) {
    decimal = decimal + (octal % 10) * pow(8, i++);
    octal = octal / 10;
    input_type->width--;
  }

  if (!input_type->isPass) check_flag_H_and_L(args, input_type, &decimal);
  input_type->width = -1;
  input_type->success += 1;
  input_type->specificator = '\0';
  return symbol_count;
}
int handle_u(va_list *args, const char **str, Input_type *input_type) {
  int symbol_count = 0;
  if (!input_type->isPass) {
    if (input_type->specificator == '\0') {
      unsigned int *destination = va_arg(*args, unsigned int *);
      long temp = s21_atoi_sscanf(str, input_type, &symbol_count);
      *destination = (unsigned int)temp;
    } else if (input_type->specificator == 'h') {
      unsigned short *destination = va_arg(*args, unsigned short *);
      long temp = s21_atoi_sscanf(str, input_type, &symbol_count);
      *destination = (unsigned short)temp;
    } else if (input_type->specificator == 'l') {
      unsigned long *destination = va_arg(*args, unsigned long *);
      long temp = s21_atoi_sscanf(str, input_type, &symbol_count);
      *destination = (unsigned long)temp;
    }
    input_type->success += 1;
  } else {
    s21_atoi_sscanf(str, input_type, &symbol_count);
  }
  input_type->isPass = 0;
  input_type->width = -1;
  input_type->specificator = '\0';
  return symbol_count;
}
int handle_i(va_list *args, const char **str, Input_type *input_type) {
  int symbol_count = 0;
  while (**str == ' ') {
    str++;
    symbol_count++;
  }
  if (**str == '0') {
    ++(*str);
    ++symbol_count;
    if (**str == 'x') {  // in case of 0x111
      symbol_count += handle_x(args, str, input_type);
    } else {  // in case of 0111
      symbol_count += handle_o(args, str, input_type);
    }
  } else if ((**str >= '0' && **str <= '9') || **str == '-' || **str == '+') {
    symbol_count += handle_d(args, str, input_type);
  }
  return symbol_count;
}
int handle_x(va_list *args, const char **str, Input_type *input_type) {
  int symbol_count = 0;
  long decimal = read_hex(str, input_type, &symbol_count);
  if (!input_type->isPass) {
    check_flag_H_and_L(args, input_type, &decimal);
    input_type->success += 1;
  }
  input_type->isPass = 0;
  input_type->width = -1;
  input_type->specificator = '\0';
  return symbol_count;
}
int handle_p(va_list *args, const char **str, Input_type *input_type) {
  int symbol_count = 0;
  long decimal = read_hex(str, input_type, &symbol_count);
  if (!input_type->isPass) {
    void **destination = va_arg(*args, void **);
    *destination = (void *)(0x0 + decimal);
    input_type->success += 1;
  }
  input_type->isPass = 0;
  input_type->width = -1;
  return symbol_count;
}
void handle_n(va_list *args, long all_symbols_count, Input_type *input_type) {
  if (!input_type->isPass) {
    unsigned int *destination = va_arg(*args, unsigned int *);
    *destination = (unsigned int)(all_symbols_count);
  }
  input_type->isPass = 0;
  input_type->width = -1;
}
long read_hex(const char **str, Input_type *input_type, int *symbol_count) {
  long decimal = 0;
  int sign = 1;

  while (**str == ' ' || **str == '-' || **str == '+' || **str == '0' ||
         **str == 'x') {
    if (**str == '-') sign = -1;
    (*str)++;
    ++(*symbol_count);
  }
  char hex_num[50] = {'\0'};
  int i = 0;
  while ((**str && **str != ' ' && **str != '\n' && input_type->width--) ||
         ((hex_num[i] >= '0' && hex_num[i] <= '9') ||
          (hex_num[i] >= 'a' && hex_num[i] <= 'f') ||
          (hex_num[i] >= 'A' && hex_num[i] <= 'F'))) {
    ++(*symbol_count);
    hex_num[i] = **str;
    ++i;
    ++(*str);
  }
  int len = s21_strlen(hex_num);
  int temp = 0;
  for (i = 0; hex_num[i] != '\0'; i++) {
    if (hex_num[i] >= '0' && hex_num[i] <= '9') {
      temp = hex_num[i] - 48;
    } else if (hex_num[i] >= 'a' && hex_num[i] <= 'f') {
      temp = hex_num[i] - 87;
    } else if (hex_num[i] >= 'A' && hex_num[i] <= 'F') {
      temp = hex_num[i] - 55;
    }
    decimal += temp * pow(16, --len);
  }
  return decimal *= sign;
}
void check_flag_H_and_L_for_double(va_list *args, Input_type *input_type,
                                   long double *result) {
  if (input_type->specificator == 'l') {
    double *destination = va_arg(*args, double *);
    *destination = (double)*result;
  } else if (input_type->specificator == 'L') {
    long double *destination = va_arg(*args, long double *);
    *destination = (long double)*result;
  } else {
    float *destination = va_arg(*args, float *);
    *destination = (float)*result;
  }
}
void check_flag_H_and_L(va_list *args, Input_type *input_type,
                        long int *result) {
  if (input_type->specificator == '\0') {
    int *destination = va_arg(*args, int *);
    *destination = (int)(*result);
  } else if (input_type->specificator == 'h') {
    short *destination = va_arg(*args, short *);
    *destination = (short)*result;
  } else if (input_type->specificator == 'l') {
    long *destination = va_arg(*args, long *);
    *destination = (long)*result;
  }
}
long int s21_atoi_sscanf(const char **str, Input_type *input_type,
                         int *symbol_count) {
  long int res = 0;
  int sign = 1;
  *symbol_count = 0;

  while (**str && **str == ' ') {
    (*str)++;
    (*symbol_count)++;
  }

  if (**str == '-') {
    sign = -1;
    (*str)++;
    input_type->width--;
    (*symbol_count)++;
  } else if (**str == '+') {
    (*str)++;
    (*symbol_count)++;
  }

  while (**str && **str >= '0' && **str <= '9' && input_type->width != 0) {
    res = res * 10 + (**str - '0');
    (*str)++;
    (*symbol_count)++;
    input_type->width--;
  }
  return res * sign;
}
void *s21_trim(const char *src, const char *trim_chars) {
  int start = 0;
  int end = s21_strlen(src);
  while (start < end && s21_strchr(trim_chars, src[start])) start++;
  while (end > start && s21_strchr(trim_chars, src[end - 1])) end--;
  char *newStr = s21_NULL;
  int sizeNewStr = end - start;
  if (sizeNewStr > 0) {
    newStr = (char *)calloc(sizeNewStr + 1, sizeof(char));
    for (int i = 0; i < sizeNewStr; ++i, ++start) {
      newStr[i] = src[start];
    }
  }
  return (void *)newStr;
}
char *s21_strrchr(const char *str, int c) {
  char *symbol = (char *)str;
  char *save = s21_NULL;
  for (; *symbol != '\0'; ++symbol) {
    if (*symbol == c) save = symbol;
  }
  return save;
}
char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == 0) return (char *)&haystack[0];
  char *result = s21_NULL;
  size_t j = 0;
  for (size_t i = 0; haystack[i] != '\0'; ++i) {
    if (haystack[i] == needle[j] && needle[j] != '\0') {
      size_t prom = i;
      result = (char *)&haystack[prom];
      for (; needle[j] != '\0'; ++i, ++j) {
        if (haystack[i] != needle[j]) {
          i = prom;
          j = 0;
          result = s21_NULL;
          break;
        }
      }
    }
  }
  return result;
}
