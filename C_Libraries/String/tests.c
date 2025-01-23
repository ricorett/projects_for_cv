#include <check.h>
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define NUMBER_OF_FUNCS 21

void to_upper_test_func(char *str) {
  int pos = 0;
  while (str[pos]) {
    str[pos] = toupper(str[pos]);
    ++pos;
  }
}

START_TEST(test_to_upper_1) {
  char *func_result =
      (char *)s21_to_upper("Hello this 56 is ABOBA aboba privet &* speaking");
  char expected_result[] = "Hello this 56 is ABOBA aboba privet &* speaking";
  to_upper_test_func(expected_result);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_to_upper_2) {
  char *func_result = (char *)s21_to_upper("");
  char expected_result[] = "";
  to_upper_test_func(expected_result);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_to_upper_3) {
  char *func_result = (char *)s21_to_upper("aboba");
  char expected_result[] = "aboba";
  to_upper_test_func(expected_result);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_to_upper_4) {
  char *func_result = (char *)s21_to_upper("Hello @#$%^&*()_+ World");
  char expected_result[] = "Hello @#$%^&*()_+ World";
  to_upper_test_func(expected_result);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_to_upper_5) {
  char *func_result = (char *)s21_to_upper("Hello\0 World");
  char expected_result[] = "Hello\0 World";
  to_upper_test_func(expected_result);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_strlen_1) {
  ck_assert(s21_strlen("Hello aboba privet") == strlen("Hello aboba privet"));
}
END_TEST

START_TEST(test_strlen_2) { ck_assert_int_eq(s21_strlen(""), strlen("")); }
END_TEST

START_TEST(test_strlen_3) {
  ck_assert_int_eq(s21_strlen("Hello"), strlen("Hello"));
}
END_TEST

START_TEST(test_strlen_4) {
  ck_assert_int_eq(
      s21_strlen("Lorem ipsum dolor sit amet, consectetur adipiscing elit."),
      strlen("Lorem ipsum dolor sit amet, consectetur adipiscing elit."));
}
END_TEST

START_TEST(test_strlen_5) {
  ck_assert_int_eq(s21_strlen("   Hello World   "),
                   strlen("   Hello World   "));
}
END_TEST

START_TEST(test_strlen_6) {
  ck_assert_int_eq(s21_strlen("@#$%^&*()_+"), strlen("@#$%^&*()_+"));
}
END_TEST

START_TEST(test_strlen_7) {
  ck_assert_int_eq(s21_strlen("Hello\0 World"), strlen("Hello\0 World"));
}
END_TEST

START_TEST(test_strncmp_1) {
  ck_assert_int_eq(s21_strncmp("", "", 5), strncmp("", "", 5));
}
END_TEST

START_TEST(test_strncmp_2) {
  ck_assert_int_eq(s21_strncmp("Hello", "Hello", 5),
                   strncmp("Hello", "Hello", 5));
}
END_TEST

START_TEST(test_strncmp_3) {
  ck_assert_int_eq(s21_strncmp("Hello", "World", 5),
                   strncmp("Hello", "World", 5));
}
END_TEST

START_TEST(test_strncmp_4) {
  ck_assert_int_eq(s21_strncmp("Hello World", "Hello There", 6),
                   strncmp("Hello World", "Hello There", 6));
}
END_TEST

START_TEST(test_strncmp_5) {
  ck_assert_int_eq(s21_strncmp("Hello\0World", "Hello", 10),
                   strncmp("Hello\0World", "Hello", 10));
}
END_TEST

START_TEST(test_strncmp_6) {
  ck_assert_int_eq(s21_strncmp("Hello World", "Hello There", 11),
                   strncmp("Hello World", "Hello There", 11));
}
END_TEST

START_TEST(test_strncmp_7) {
  ck_assert_int_eq(s21_strncmp("Hello World", "Hello", 5),
                   strncmp("Hello World", "Hello", 5));
}
END_TEST

START_TEST(test_strncmp_8) {
  ck_assert_int_eq(s21_strncmp("Hello World", "", 5),
                   strncmp("Hello World", "", 5));
}
END_TEST

START_TEST(test_strncmp_9) {
  ck_assert_int_eq(s21_strncmp("", "Hello", 5), strncmp("", "Hello", 5));
}
END_TEST

START_TEST(test_strpbrk_1) {
  ck_assert_ptr_eq(s21_strpbrk("Hello World", "H"),
                   strpbrk("Hello World", "H"));
}
END_TEST

START_TEST(test_strpbrk_2) {
  ck_assert_ptr_eq(s21_strpbrk("Hello World", "d"),
                   strpbrk("Hello World", "d"));
}
END_TEST

START_TEST(test_strpbrk_3) {
  ck_assert_ptr_eq(s21_strpbrk("Hello World", " "),
                   strpbrk("Hello World", " "));
}
END_TEST

START_TEST(test_strpbrk_4) {
  ck_assert_ptr_eq(s21_strpbrk("Hello World", "xyz"),
                   strpbrk("Hello World", "xyz"));
}
END_TEST

START_TEST(test_strpbrk_5) {
  ck_assert_ptr_eq(s21_strpbrk("", ""), strpbrk("", ""));
}
END_TEST

START_TEST(test_insert_1) {
  char *expected_result = "";
  char *func_result = (char *)s21_insert("", "", 0);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_insert_2) {
  char *expected_result = "Hello";
  char *func_result = (char *)s21_insert("", "Hello", 0);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_insert_3) {
  char *expected_result = "World";
  char *func_result = (char *)s21_insert("World", "", 0);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_insert_4) {
  char *expected_result = " WorldHello";
  char *func_result = (char *)s21_insert("Hello", " World", 0);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_insert_5) {
  char *expected_result = "Hel Worldlo";
  char *func_result = (char *)s21_insert("Hello", " World", 3);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_insert_6) {
  char *expected_result = "Hello World";
  char *func_result = (char *)s21_insert("Hello", " World", 5);
  ck_assert_str_eq(func_result, expected_result);
  free(func_result);
}
END_TEST

START_TEST(test_insert_7) {
  char *func_result = (char *)s21_insert("Hello", " World", 10);
  ck_assert_ptr_eq(func_result, NULL);
  free(func_result);
}
END_TEST

START_TEST(test_insert_8) {
  char *func_result = (char *)s21_insert("Hello", " World", -5);
  ck_assert_ptr_eq(func_result, NULL);
  free(func_result);
}
END_TEST

Suite *s21_strncmp_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strncmp");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncmp_1);
  tcase_add_test(tc_core, test_strncmp_2);
  tcase_add_test(tc_core, test_strncmp_3);
  tcase_add_test(tc_core, test_strncmp_4);
  tcase_add_test(tc_core, test_strncmp_5);
  tcase_add_test(tc_core, test_strncmp_6);
  tcase_add_test(tc_core, test_strncmp_7);
  tcase_add_test(tc_core, test_strncmp_8);
  tcase_add_test(tc_core, test_strncmp_9);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_to_upper_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("to_upper");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper_1);
  tcase_add_test(tc_core, test_to_upper_2);
  tcase_add_test(tc_core, test_to_upper_3);
  tcase_add_test(tc_core, test_to_upper_4);
  tcase_add_test(tc_core, test_to_upper_5);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_strlen_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strlen");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen_1);
  tcase_add_test(tc_core, test_strlen_2);
  tcase_add_test(tc_core, test_strlen_3);
  tcase_add_test(tc_core, test_strlen_4);
  tcase_add_test(tc_core, test_strlen_5);
  tcase_add_test(tc_core, test_strlen_6);
  tcase_add_test(tc_core, test_strlen_7);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_strpbrk_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strpbrk");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strpbrk_1);
  tcase_add_test(tc_core, test_strpbrk_2);
  tcase_add_test(tc_core, test_strpbrk_3);
  tcase_add_test(tc_core, test_strpbrk_4);
  tcase_add_test(tc_core, test_strpbrk_5);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_insert_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("insert");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_insert_1);
  tcase_add_test(tc_core, test_insert_2);
  tcase_add_test(tc_core, test_insert_3);
  tcase_add_test(tc_core, test_insert_4);
  tcase_add_test(tc_core, test_insert_5);
  tcase_add_test(tc_core, test_insert_6);
  tcase_add_test(tc_core, test_insert_7);
  tcase_add_test(tc_core, test_insert_8);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(s21_strchr_test_found) {
  char *input =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n"
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char *expected_output = strchr(input, 'f');
  char *actual_output = s21_strchr(input, 'f');

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_strchr_test_not_found) {
  char *input =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n"
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char *expected_output = strchr(input, '5');
  char *actual_output = s21_strchr(input, '5');

  ck_assert(expected_output == NULL);
  ck_assert(actual_output == NULL);
  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_strchr_test_zero) {
  char *input =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n"
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char *expected_output = strchr(input, '\0');
  char *actual_output = s21_strchr(input, '\0');

  ck_assert(expected_output == actual_output);
}
END_TEST

Suite *s21_strchr_test(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_strchr_tests");
  tcase = tcase_create("s21_strchr");

  tcase_add_test(tcase, s21_strchr_test_found);
  tcase_add_test(tcase, s21_strchr_test_not_found);
  tcase_add_test(tcase, s21_strchr_test_zero);
  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(s21_to_lower_some_to_lower) {
  char *input = "Never over when it's done";

  char *expected_output = "never over when it's done";

  char *actual_output = s21_to_lower(input);
  ck_assert_str_eq(expected_output, actual_output);
  free(actual_output);
}
END_TEST

START_TEST(s21_to_lower_all_to_lower) {
  char *input = "WHATA DO YOU WANNA HUH MAN";

  char *expected_output = "whata do you wanna huh man";

  char *actual_output = s21_to_lower(input);

  ck_assert_str_eq(expected_output, actual_output);
  free(actual_output);
}
END_TEST

START_TEST(s21_to_lower_nothing_to_lower) {
  char *input = "whata do you wanna huh man";

  char *expected_output = "whata do you wanna huh man";

  char *actual_output = s21_to_lower(input);

  ck_assert_str_eq(expected_output, actual_output);
  free(actual_output);
}
END_TEST

Suite *s21_to_lower_tests(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_to_lower_tests");
  tcase = tcase_create("s21_to_lower");

  tcase_add_test(tcase, s21_to_lower_some_to_lower);
  tcase_add_test(tcase, s21_to_lower_all_to_lower);
  tcase_add_test(tcase, s21_to_lower_nothing_to_lower);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(s21_strncat_test_normal) {
  char input_part_1[512] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  char input_part_2[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char *expected_output = strncat(input_part_1, input_part_2, 217);
  char *actual_output = s21_strncat(input_part_1, input_part_2, 217);

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_strncat_test_empty) {
  char input_part_1[512] = "";
  char input_part_2[512] = "";

  char *expected_output = strncat(input_part_1, input_part_2, 217);
  char *actual_output = s21_strncat(input_part_1, input_part_2, 217);

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_strncat_test_half) {
  char input_part_1[512] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  char input_part_2[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char *expected_output = strncat(input_part_1, input_part_2, 106);
  char *actual_output = s21_strncat(input_part_1, input_part_2, 106);

  ck_assert(expected_output == actual_output);
}
END_TEST
START_TEST(s21_memchr_test1) {
  char *input = "I GIVE YOU SOME $ YOU GIVE ME SOME SUSSY";

  char *expected_output = memchr(input, '$', strlen(input));

  char *actual_output = s21_memchr(input, '$', strlen(input));

  ck_assert_str_eq(expected_output, actual_output);
}
END_TEST

START_TEST(s21_memchr_not_found) {
  char *input = "I GIVE YOU SOME $ YOU GIVE ME SOME SUSSY";

  char *expected_output = memchr(input, '.', strlen(input));

  char *actual_output = s21_memchr(input, '.', strlen(input));

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_strncat_test_cut) {
  char input_part_1[512] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  char input_part_2[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char *expected_output = strncat(input_part_1, input_part_2, 10);
  char *actual_output = s21_strncat(input_part_1, input_part_2, 10);
  ck_assert(expected_output == actual_output);
}
END_TEST
START_TEST(s21_memchr_put_null) {
  char *input = NULL;

  char *expected_output = memchr(input, '.', 0);

  char *actual_output = s21_memchr(input, '.', 0);

  ck_assert(expected_output == actual_output);
}
END_TEST

Suite *s21_strncat_test(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_strncat_tests");
  tcase = tcase_create("s21_strncat");

  tcase_add_test(tcase, s21_strncat_test_normal);
  tcase_add_test(tcase, s21_strncat_test_empty);
  tcase_add_test(tcase, s21_strncat_test_half);
  tcase_add_test(tcase, s21_strncat_test_cut);
  suite_add_tcase(suite, tcase);

  return suite;
}
Suite *s21_memchr_tests(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_memchr_tests");
  tcase = tcase_create("s21_memchr");

  tcase_add_test(tcase, s21_memchr_test1);
  tcase_add_test(tcase, s21_memchr_not_found);
  tcase_add_test(tcase, s21_memchr_put_null);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(s21_memset_test_normal) {
  char input[256] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  char *expected_output = memset(input, '@', 10);
  char *actual_output = s21_memset(input, '@', 10);

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_memset_test_empty) {
  char input[256] = "";

  char *expected_output = memset(input, '@', 10);
  char *actual_output = s21_memset(input, '@', 10);
  ck_assert(expected_output == actual_output);
}
END_TEST
START_TEST(s21_strtok_put_null) {
  char *input = NULL;

  char *expected_output = strtok(input, "c");

  char *actual_output = s21_strtok(input, "c");

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_memset_test_null_terminator) {
  char input[256] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  char *expected_output = memset(input, '\0', 1);
  char *actual_output = s21_memset(input, '\0', 1);

  ck_assert(expected_output == actual_output);
}
END_TEST

Suite *s21_memset_test(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_memset_test");
  tcase = tcase_create("s21_memset");

  tcase_add_test(tcase, s21_memset_test_normal);
  tcase_add_test(tcase, s21_memset_test_empty);
  tcase_add_test(tcase, s21_memset_test_null_terminator);
  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(s21_strtok_normal_check) {
  char input1[] = "What, do, you, want, fdads";
  char *token1;
  char input2[] = "What, do, you, want, fdads";
  char *token2;
  char *expected_last;
  char *actual_last;
  token1 = strtok(input1, ", ");
  while (token1 != NULL) {
    expected_last = token1;
    token1 = strtok(NULL, ", ");
  }
  token2 = s21_strtok(input2, ", ");
  while (token2 != NULL) {
    actual_last = token2;
    token2 = s21_strtok(NULL, ", ");
  }
  ck_assert_str_eq(expected_last, actual_last);
}
END_TEST

Suite *s21_strtok_tests(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_strtok_tests");
  tcase = tcase_create("s21_strtok");

  tcase_add_test(tcase, s21_strtok_put_null);
  tcase_add_test(tcase, s21_strtok_normal_check);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(s21_memcmp_test_less) {
  char input_part_1[512] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  char input_part_2[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  int expected_output = memcmp(input_part_1, input_part_2, 10);
  int actual_output = s21_memcmp(input_part_1, input_part_2, 10);

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_memcmp_test_equal) {
  char input_part_1[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char input_part_2[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  int expected_output = memcmp(input_part_1, input_part_2, 10);
  int actual_output = s21_memcmp(input_part_1, input_part_2, 10);

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_memcmp_test_greater) {
  char input_part_1[512] =
      "When these people talk too much, put that shit in slow motion, yeah\n"
      "I feel like an astronaut in the ocean, ayy";

  char input_part_2[512] =
      "What you know about rollin' down in the deep?\n"
      "When your brain goes numb, you can call that mental freeze\n";

  int expected_output = memcmp(input_part_1, input_part_2, 10);
  int actual_output = s21_memcmp(input_part_1, input_part_2, 10);

  ck_assert(expected_output == actual_output);
}
END_TEST

START_TEST(s21_memcmp_test_empty) {
  char input_part_1[512] = "";
  char input_part_2[512] = "";

  int expected_output = memcmp(input_part_1, input_part_2, 10);
  int actual_output = s21_memcmp(input_part_1, input_part_2, 10);

  ck_assert(expected_output == actual_output);
}
END_TEST

Suite *s21_memcmp_test(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_memcmp_test");
  tcase = tcase_create("s21_memcmp");

  tcase_add_test(tcase, s21_memcmp_test_less);
  tcase_add_test(tcase, s21_memcmp_test_equal);
  tcase_add_test(tcase, s21_memcmp_test_greater);
  tcase_add_test(tcase, s21_memcmp_test_empty);
  suite_add_tcase(suite, tcase);

  return suite;
}
START_TEST(s21_strerror_normal_check) {
  int errno = 5;

  char *actual_output = s21_strerror(errno);
  char *expected_output = strerror(errno);

  ck_assert_str_eq(expected_output, actual_output);
}
END_TEST

START_TEST(s21_strerror_unknown_error) {
  int errno = 5123;

  char *actual_output = s21_strerror(errno);
  char *expected_output = strerror(errno);

  ck_assert_str_eq(expected_output, actual_output);
}
END_TEST

Suite *s21_strerror_tests(void) {
  Suite *suite;
  TCase *tcase;

  suite = suite_create("s21_strerror_tests");
  tcase = tcase_create("s21_strerror");

  tcase_add_test(tcase, s21_strerror_unknown_error);
  tcase_add_test(tcase, s21_strerror_normal_check);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_memcpy_empty_string) {
  const char *src = "";
  char dest[10] = {0};
  char dest2[10] = {0};
  memcpy(dest, src, 0);
  s21_memcpy(dest2, src, 0);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_memcpy_same_string) {
  const char *src = "Hello, World!";
  char dest[20] = {0};
  char dest2[20] = {0};
  memcpy(dest, src, strlen(src) + 1);
  s21_memcpy(dest2, src, strlen(src) + 1);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_memcpy_partial_string) {
  const char *src = "Hello, World!";
  char dest[20] = {0};
  char dest2[20] = {0};

  memcpy(dest, src, 6);
  s21_memcpy(dest2, src, 6);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_memcpy_overlap) {
  char src[10] = "Hello";
  char dest[10] = "World";
  char dest2[10] = "World";

  memcpy(dest + 1, src, 5);
  s21_memcpy(dest2 + 1, src, 5);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_memcpy_null_pointer) {
  const char *src = "Hello";
  char *dest2 = NULL;

  void *expected_result = s21_memcpy(dest2, src, strlen(src) + 1);
  ck_assert_ptr_eq(expected_result, NULL);
}
END_TEST

START_TEST(test_strncpy_empty_string) {
  const char *src = "";
  char dest[10] = {0};
  char dest2[10] = {0};

  strncpy(dest, src, sizeof(dest));
  s21_strncpy(dest2, src, sizeof(dest2));

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_strncpy_same_string) {
  const char *src = "Hello, World!";
  char dest[20] = {0};
  char dest2[20] = {0};

  strncpy(dest, src, sizeof(dest));
  s21_strncpy(dest2, src, sizeof(dest2));

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_strncpy_partial_string) {
  const char *src = "Hello, World!";
  char dest[20] = {0};
  char dest2[20] = {0};

  strncpy(dest, src, 6);
  s21_strncpy(dest2, src, 6);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_strncpy_null_termination) {
  const char *src = "Hello";
  char dest[10] = {0};
  char dest2[10] = {0};

  strncpy(dest, src, sizeof(dest));
  s21_strncpy(dest2, src, sizeof(dest2));
  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_strcspn_no_matching_characters) {
  const char *str1 = "Hello, World!";
  const char *str2 = "1234567890";
  size_t expected_result = strcspn(str1, str2);

  size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected_result);
}
END_TEST

START_TEST(test_strcspn_matching_character_at_beginning) {
  const char *str1 = "Hello, World!";
  const char *str2 = "H";
  size_t expected_result = strcspn(str1, str2);

  size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected_result);
}
END_TEST

START_TEST(test_strcspn_matching_character_at_end) {
  const char *str1 = "Hello, World!";
  const char *str2 = "!";
  size_t expected_result = strcspn(str1, str2);

  size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected_result);
}
END_TEST

START_TEST(test_strcspn_matching_character_in_middle) {
  const char *str1 = "Hello, World!";
  const char *str2 = ",";
  size_t expected_result = strcspn(str1, str2);

  size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected_result);
}
END_TEST

START_TEST(test_strcspn_empty_string) {
  const char *str1 = "";
  const char *str2 = "abc";
  size_t expected_result = strcspn(str1, str2);

  size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, expected_result);
}
END_TEST

START_TEST(test_sprintf_1) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "char:%2c", 'A');
  int return2 = sprintf(buff2, "char:%2c", 'A');

  ck_assert_str_eq(buff, buff2);
  ck_assert_int_eq(return1, return2);
}

START_TEST(test_sprintf_2) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%%");
  int return2 = sprintf(buff2, "%%");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_3) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "char:%-5c", 'A');
  int return2 = sprintf(buff2, "char:%-5c", 'A');
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_4) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%s", "aboba");
  int return2 = sprintf(buff2, "%s", "aboba");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_5) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%10s", "aboba");
  int return2 = sprintf(buff2, "%10s", "aboba");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_6) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-10s", "aboba");
  int return2 = sprintf(buff2, "%-10s", "aboba");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_7) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-5d", 123);
  int return2 = sprintf(buff2, "%-5d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_8) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-5x", 123);
  int return2 = sprintf(buff2, "%-5x", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_9) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-5x, %#X, %#o, %+-6d", 123, 1000, 25, -123);
  int return2 = sprintf(buff2, "%-5x, %#X, %#o, %+-6d", 123, 1000, 25, -123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_10) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%5.5d, %2.9d, %.2d", 123, 123, 123);
  int return2 = sprintf(buff2, "%5.5d, %2.9d, %.2d", 123, 123, 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_11) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%d", 123);
  int return2 = sprintf(buff2, "%d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_12) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%10d", 123);
  int return2 = sprintf(buff2, "%10d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_13) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%+d", 123);
  int return2 = sprintf(buff2, "%+d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_14) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "% -10d", 123);
  int return2 = sprintf(buff2, "% -10d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_15) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%05d", 123);
  int return2 = sprintf(buff2, "%05d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_16) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.*d", 5, 123);
  int return2 = sprintf(buff2, "%.*d", 5, 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_17) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%x", 123);
  int return2 = sprintf(buff2, "%x", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_18) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%#x", 123);
  int return2 = sprintf(buff2, "%#x", 123);

  ck_assert_str_eq(buff, buff2);
  ck_assert_int_eq(return1, return2);
}

START_TEST(test_sprintf_19) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%10x", 123);
  int return2 = sprintf(buff2, "%10x", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_20) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.4x", 123);
  int return2 = sprintf(buff2, "%.4x", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_21) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%X", 123);
  int return2 = sprintf(buff2, "%X", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_22) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%o", 123);
  int return2 = sprintf(buff2, "%o", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_23) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%#o", 123);
  int return2 = sprintf(buff2, "%#o", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_24) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%10o", 123);
  int return2 = sprintf(buff2, "%10o", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_25) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-10o", 123);
  int return2 = sprintf(buff2, "%-10o", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_26) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.*o", 7, 123);
  int return2 = sprintf(buff2, "%.*o", 7, 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_27) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%s", "Hello");
  int return2 = sprintf(buff2, "%s", "Hello");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_28) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%11.11s", "Hello");
  int return2 = sprintf(buff2, "%11.11s", "Hello");

  ck_assert_str_eq(buff, buff2);
  ck_assert_int_eq(return1, return2);
}

START_TEST(test_sprintf_29) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.*s", 3, "Hello");
  int return2 = sprintf(buff2, "%.*s", 3, "Hello");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_30) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%c", 'A');
  int return2 = sprintf(buff2, "%c", 'A');
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_31) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-10c", 'A');
  int return2 = sprintf(buff2, "%-10c", 'A');
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_32) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%%");
  int return2 = sprintf(buff2, "%%");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_33) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%u", 12345);
  int return2 = sprintf(buff2, "%u", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_34) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%10u", 12345);
  int return2 = sprintf(buff2, "%10u", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_35) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%-10u", 12345);
  int return2 = sprintf(buff2, "%-10u", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_36) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.4u", 12345);
  int return2 = sprintf(buff2, "%.4u", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_37) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%lu", (unsigned long)123456789012345);
  int return2 = sprintf(buff2, "%lu", (unsigned long)123456789012345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_38) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%hx", (unsigned short)56789);
  int return2 = sprintf(buff2, "%hx", (unsigned short)56789);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_39) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%X", 255);
  int return2 = sprintf(buff2, "%X", 255);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_40) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%#o", 12345);
  int return2 = sprintf(buff2, "%#o", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_41) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%#x", 255);
  int return2 = sprintf(buff2, "%#x", 255);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_42) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%hd", (short)12345);
  int return2 = sprintf(buff2, "%hd", (short)12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_43) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%ld", (long)1234567890);
  int return2 = sprintf(buff2, "%ld", (long)1234567890);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_44) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%5.3d", 123);
  int return2 = sprintf(buff2, "%5.3d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_45) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%hd", (short)-123);
  int return2 = sprintf(buff2, "%hd", (short)-123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_46) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%10u", 12345);
  int return2 = sprintf(buff2, "%10u", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_47) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%ld", (long)-123);
  int return2 = sprintf(buff2, "%ld", (long)-123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_48) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.4u", 12345);
  int return2 = sprintf(buff2, "%.4u", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_49) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%lu", (unsigned long)123456789012345);
  int return2 = sprintf(buff2, "%lu", (unsigned long)123456789012345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_50) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%hx", (unsigned short)56789);
  int return2 = sprintf(buff2, "%hx", (unsigned short)56789);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_51) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%X", 255);
  int return2 = sprintf(buff2, "%X", 255);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_52) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%#o", 12345);
  int return2 = sprintf(buff2, "%#o", 12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_53) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%#x", 255);
  int return2 = sprintf(buff2, "%#x", 255);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_54) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%hd", (short)12345);
  int return2 = sprintf(buff2, "%hd", (short)12345);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_55) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%ld", (long)1234567890);
  int return2 = sprintf(buff2, "%ld", (long)1234567890);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_56) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%5.3d", 123);
  int return2 = sprintf(buff2, "%5.3d", 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_57) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%*.3d", 5, 123);
  int return2 = sprintf(buff2, "%*.3d", 5, 123);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_58) {
  char buff[100], buff2[100];
  int value = 123;
  int return1 = s21_sprintf(buff, "%p", &value);
  int return2 = sprintf(buff2, "%p", (void *)&value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_59) {
  char buff[100], buff2[100];
  int value = 456;
  int return1 = s21_sprintf(buff, "%15p", &value);
  int return2 = sprintf(buff2, "%15p", (void *)&value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_60) {
  char buff[100], buff2[100];
  int value = 789;
  int return1 = s21_sprintf(buff, "%-15p", &value);
  int return2 = sprintf(buff2, "%-15p", (void *)&value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_61) {
  char buff[100], buff2[100];
  int value = 5678;
  int return1 = s21_sprintf(buff, "%12p", &value);
  int return2 = sprintf(buff2, "%12p", (void *)&value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_62) {
  char buff[100], buff2[100];
  int return1 = s21_sprintf(buff, "%.s", "Hello");
  int return2 = sprintf(buff2, "%.s", "Hello");
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_63) {
  char buff[100], buff2[100];
  int b = 5;
  int *a = &b;
  int return1 = s21_sprintf(buff, "pointer: %p", a);
  int return2 = sprintf(buff2, "pointer: %p", (void *)a);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_64) {
  char buff[100], buff2[100];
  wchar_t ch = L'ア';
  int return1 = s21_sprintf(buff, "%-6lc", ch);
  int return2 = sprintf(buff2, "%-6lc", ch);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_65) {
  char buff[100], buff2[100];
  wchar_t *str = L"アボバ";
  int return1 = s21_sprintf(buff, "%5.20ls", str);
  int return2 = sprintf(buff2, "%5.20ls", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_66) {
  char buff[100], buff2[100];
  wchar_t unicode_char = L'€';
  int return1 = s21_sprintf(buff, "%lc", unicode_char);
  int return2 = sprintf(buff2, "%lc", unicode_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_67) {
  char buff[100], buff2[100];
  wchar_t unicode_char = L'♥';
  int return1 = s21_sprintf(buff, "%10lc", unicode_char);
  int return2 = sprintf(buff2, "%10lc", unicode_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_68) {
  char buff[100], buff2[100];
  wchar_t ascii_char = 'A';
  int return1 = s21_sprintf(buff, "%lc", ascii_char);
  int return2 = sprintf(buff2, "%lc", ascii_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_69) {
  char buff[100], buff2[100];
  wchar_t unicode_char = L'ƒ';
  int return1 = s21_sprintf(buff, "%-10lc", unicode_char);
  int return2 = sprintf(buff2, "%-10lc", unicode_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_70) {
  char buff[100], buff2[100];
  wchar_t unicode_char = L'Ü';
  int return1 = s21_sprintf(buff, "%-10lc", unicode_char);
  int return2 = sprintf(buff2, "%-10lc", unicode_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_71) {
  char buff[100], buff2[100];
  wchar_t unicode_char = L'æ';
  int return1 = s21_sprintf(buff, "%-10lc", unicode_char);
  int return2 = sprintf(buff2, "%-10lc", unicode_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_72) {
  char buff[100], buff2[100];
  wchar_t unicode_char = L'☺';
  int return1 = s21_sprintf(buff, "%lc", unicode_char);
  int return2 = sprintf(buff2, "%lc", unicode_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_73) {
  char buff[100], buff2[100];
  wchar_t ascii_char = 'a';
  int return1 = s21_sprintf(buff, "%-5lc", ascii_char);
  int return2 = sprintf(buff2, "%-5lc", ascii_char);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_74) {
  char buff[100], buff2[100];
  wchar_t unicode_str[] = L"Hello, 世界!";
  int return1 = s21_sprintf(buff, "%ls", unicode_str);
  int return2 = sprintf(buff2, "%ls", unicode_str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_75) {
  char buff[100], buff2[100];
  wchar_t unicode_str[] = L"∞ ☺ 🌟";
  int return1 = s21_sprintf(buff, "%15ls", unicode_str);
  int return2 = sprintf(buff2, "%15ls", unicode_str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_76) {
  char buff[500], buff2[500];
  wchar_t ascii_str[] = L"Hello, World!";
  int return1 = s21_sprintf(buff, "%ls", ascii_str);
  int return2 = sprintf(buff2, "%ls", ascii_str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_77) {
  char buff[100], buff2[100];
  wchar_t unicode_str[] = L"😊 Unicode 😊";
  int return1 = s21_sprintf(buff, "%-20ls", unicode_str);
  int return2 = sprintf(buff2, "%-20ls", unicode_str);
  ck_assert_str_eq(buff, buff2);
  ck_assert_int_eq(return1, return2);
}

START_TEST(test_sprintf_78) {
  char buff[100], buff2[100];
  wchar_t unicode_str[] = L"©";
  int return1 = s21_sprintf(buff, "%3.1ls", unicode_str);
  int return2 = sprintf(buff2, "%3.1ls", unicode_str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_79) {
  char buff[100], buff2[100];
  wchar_t ascii_str[] = L"Hello";
  int return1 = s21_sprintf(buff, "%3.10ls", ascii_str);
  int return2 = sprintf(buff2, "%3.10ls", ascii_str);

  ck_assert_str_eq(buff, buff2);
  ck_assert_int_eq(return1, return2);
}

START_TEST(test_sprintf_80) {
  char buff[500], buff2[500];
  wchar_t unicode_str[] = L"😄 Wide String 😄";
  int return1 = s21_sprintf(buff, "%3.10ls", unicode_str);
  int return2 = sprintf(buff2, "%3.10ls", unicode_str);

  ck_assert_str_eq(buff, buff2);
  ck_assert_int_eq(return1, return2);
}

START_TEST(test_sprintf_81) {
  char buff[100], buff2[100];
  wchar_t ascii_str[] = L"ASCII";
  int return1 = s21_sprintf(buff, "%-5ls", ascii_str);
  int return2 = sprintf(buff2, "%-5ls", ascii_str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_82) {
  char buff[100], buff2[100];
  char str[] = "aboba";
  int return1 = s21_sprintf(buff, "%6.4s", str);
  int return2 = sprintf(buff2, "%6.4s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_83) {
  char buff[100], buff2[100];
  char str[] = "Unicode 😊";
  int return1 = s21_sprintf(buff, "%10.6s", str);
  int return2 = sprintf(buff2, "%10.6s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_84) {
  char buff[100], buff2[100];
  char str[] = "ASCII";
  int return1 = s21_sprintf(buff, "%-8.3s", str);
  int return2 = sprintf(buff2, "%-8.3s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_85) {
  char buff[100], buff2[100];
  char str[] = "Testing";
  int return1 = s21_sprintf(buff, "%.2s", str);
  int return2 = sprintf(buff2, "%.2s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_86) {
  char buff[100], buff2[100];
  char str[] = "Wide String 😄";
  int return1 = s21_sprintf(buff, "%5.10s", str);
  int return2 = sprintf(buff2, "%5.10s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_87) {
  char buff[100], buff2[100];
  char str[] = "Testing";
  int return1 = s21_sprintf(buff, "%3.6s", str);
  int return2 = sprintf(buff2, "%3.6s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_88) {
  char buff[100], buff2[100];
  char str[] = "ASCII";
  int return1 = s21_sprintf(buff, "%10.5s", str);
  int return2 = sprintf(buff2, "%10.5s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_89) {
  char buff[100], buff2[100];
  char str[] = "😊 Unicode 😊";
  int return1 = s21_sprintf(buff, "%4.8s", str);
  int return2 = sprintf(buff2, "%4.8s", str);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_90) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%f", value);
  int return2 = sprintf(buff2, "%f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_91) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%.f", value);
  int return2 = sprintf(buff2, "%.f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_92) {
  char buff[100], buff2[100];
  float value = 15.4;
  int return1 = s21_sprintf(buff, "%.f", value);
  int return2 = sprintf(buff2, "%.f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_93) {
  char buff[100], buff2[100];
  float value = -15.5;
  int return1 = s21_sprintf(buff, "%10f", value);
  int return2 = sprintf(buff2, "%10f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_94) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10f", value);
  int return2 = sprintf(buff2, "%-10f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_95) {
  char buff[100], buff2[100];
  float value = -15.5;
  int return1 = s21_sprintf(buff, "%10.3f", value);
  int return2 = sprintf(buff2, "%10.3f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_96) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%10.15f", value);
  int return2 = sprintf(buff2, "%10.15f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_97) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.3f", value);
  int return2 = sprintf(buff2, "%-10.3f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_98) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.15f", value);
  int return2 = sprintf(buff2, "%-10.15f", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_99) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.15Lf", value);
  int return2 = sprintf(buff2, "%-10.15Lf", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_100) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "%+10.15Lf", value);
  int return2 = sprintf(buff2, "%+10.15Lf", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_101) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 10.15Lf", value);
  int return2 = sprintf(buff2, "% 10.15Lf", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_102) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 010.15Lf", value);
  int return2 = sprintf(buff2, "% 010.15Lf", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_103) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 020Lf", value);
  int return2 = sprintf(buff2, "% 020Lf", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_104) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%e", value);
  int return2 = sprintf(buff2, "%e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_105) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%.e", value);
  int return2 = sprintf(buff2, "%.e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_106) {
  char buff[100], buff2[100];
  float value = 15.4;
  int return1 = s21_sprintf(buff, "%.e", value);
  int return2 = sprintf(buff2, "%.e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_107) {
  char buff[100], buff2[100];
  float value = -15.5;
  int return1 = s21_sprintf(buff, "%10e", value);
  int return2 = sprintf(buff2, "%10e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_108) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10E", value);
  int return2 = sprintf(buff2, "%-10E", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_109) {
  char buff[100], buff2[100];
  float value = -15.5;
  int return1 = s21_sprintf(buff, "%10.3e", value);
  int return2 = sprintf(buff2, "%10.3e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_110) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%10.15E", value);
  int return2 = sprintf(buff2, "%10.15E", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_111) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.3e", value);
  int return2 = sprintf(buff2, "%-10.3e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_112) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.15e", value);
  int return2 = sprintf(buff2, "%-10.15e", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_113) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.15Le", value);
  int return2 = sprintf(buff2, "%-10.15Le", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_114) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "%+10.15Le", value);
  int return2 = sprintf(buff2, "%+10.15Le", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_115) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 10.15Le", value);
  int return2 = sprintf(buff2, "% 10.15Le", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_116) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 010.15Le", value);
  int return2 = sprintf(buff2, "% 010.15Le", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_117) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 020Le", value);
  int return2 = sprintf(buff2, "% 020Le", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_118) {
  char buff[100], buff2[100];
  double value = 10000000;
  int return1 = s21_sprintf(buff, "%g", value);
  int return2 = sprintf(buff2, "%g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_119) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%.g", value);
  int return2 = sprintf(buff2, "%.g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_120) {
  char buff[100], buff2[100];
  float value = 15.4;
  int return1 = s21_sprintf(buff, "%.g", value);
  int return2 = sprintf(buff2, "%.g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_121) {
  char buff[100], buff2[100];
  float value = -15.5;
  int return1 = s21_sprintf(buff, "|%10g|", value);
  int return2 = sprintf(buff2, "|%10g|", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_122) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10g", value);
  int return2 = sprintf(buff2, "%-10g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_123) {
  char buff[100], buff2[100];
  float value = -15.5;
  int return1 = s21_sprintf(buff, "%10.3g", value);
  int return2 = sprintf(buff2, "%10.3g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_124) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%10.15g", value);
  int return2 = sprintf(buff2, "%10.15g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_125) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.3g", value);
  int return2 = sprintf(buff2, "%-10.3g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_126) {
  char buff[100], buff2[100];
  float value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.15g", value);
  int return2 = sprintf(buff2, "%-10.15g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_127) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "%-10.15Lg", value);
  int return2 = sprintf(buff2, "%-10.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_128) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "%+10.15Lg", value);
  int return2 = sprintf(buff2, "%+10.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_129) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 10.15Lg", value);
  int return2 = sprintf(buff2, "% 10.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_130) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 010.15Lg", value);
  int return2 = sprintf(buff2, "% 010.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_131) {
  char buff[100], buff2[100];
  long double value = 15.5;
  int return1 = s21_sprintf(buff, "% 020Lg", value);
  int return2 = sprintf(buff2, "% 020Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_132) {
  char buff[100], buff2[100];
  double value = 150000000;
  int return1 = s21_sprintf(buff, "%g", value);
  int return2 = sprintf(buff2, "%g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_133) {
  char buff[100], buff2[100];
  float value = 150000000;
  int return1 = s21_sprintf(buff, "%.g", value);
  int return2 = sprintf(buff2, "%.g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_134) {
  char buff[100], buff2[100];
  float value = 150000000;
  int return1 = s21_sprintf(buff, "%.g", value);
  int return2 = sprintf(buff2, "%.g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_135) {
  char buff[100], buff2[100];
  float value = -150000000;
  int return1 = s21_sprintf(buff, "|%10g|", value);
  int return2 = sprintf(buff2, "|%10g|", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_136) {
  char buff[100], buff2[100];
  float value = 150000000;
  int return1 = s21_sprintf(buff, "%-10g", value);
  int return2 = sprintf(buff2, "%-10g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_137) {
  char buff[100], buff2[100];
  float value = -150000000;
  int return1 = s21_sprintf(buff, "%10.3g", value);
  int return2 = sprintf(buff2, "%10.3g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_138) {
  char buff[100], buff2[100];
  float value = 150000000;
  int return1 = s21_sprintf(buff, "%10.15g", value);
  int return2 = sprintf(buff2, "%10.15g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_139) {
  char buff[100], buff2[100];
  float value = 150000000;
  int return1 = s21_sprintf(buff, "%-10.3g", value);
  int return2 = sprintf(buff2, "%-10.3g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_140) {
  char buff[100], buff2[100];
  float value = 150000000;
  int return1 = s21_sprintf(buff, "%-10.15g", value);
  int return2 = sprintf(buff2, "%-10.15g", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_141) {
  char buff[100], buff2[100];
  long double value = 150000000;
  int return1 = s21_sprintf(buff, "%-10.15Lg", value);
  int return2 = sprintf(buff2, "%-10.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_142) {
  char buff[100], buff2[100];
  long double value = 150000000;
  int return1 = s21_sprintf(buff, "%+10.15Lg", value);
  int return2 = sprintf(buff2, "%+10.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_143) {
  char buff[100], buff2[100];
  long double value = 150000000;
  int return1 = s21_sprintf(buff, "% 10.15Lg", value);
  int return2 = sprintf(buff2, "% 10.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_144) {
  char buff[100], buff2[100];
  long double value = 150000000;
  int return1 = s21_sprintf(buff, "% 010.15Lg", value);
  int return2 = sprintf(buff2, "% 010.15Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

START_TEST(test_sprintf_145) {
  char buff[100], buff2[100];
  long double value = 150000000;
  int return1 = s21_sprintf(buff, "% 020Lg", value);
  int return2 = sprintf(buff2, "% 020Lg", value);
  ck_assert_int_eq(return1, return2);
  ck_assert_str_eq(buff, buff2);
}

Suite *s21_sprintftest(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sprintf_1);
  tcase_add_test(tc_core, test_sprintf_2);
  tcase_add_test(tc_core, test_sprintf_3);
  tcase_add_test(tc_core, test_sprintf_4);
  tcase_add_test(tc_core, test_sprintf_5);
  tcase_add_test(tc_core, test_sprintf_6);
  tcase_add_test(tc_core, test_sprintf_7);
  tcase_add_test(tc_core, test_sprintf_8);
  tcase_add_test(tc_core, test_sprintf_9);
  tcase_add_test(tc_core, test_sprintf_10);
  tcase_add_test(tc_core, test_sprintf_11);
  tcase_add_test(tc_core, test_sprintf_12);
  tcase_add_test(tc_core, test_sprintf_13);
  tcase_add_test(tc_core, test_sprintf_14);
  tcase_add_test(tc_core, test_sprintf_15);
  tcase_add_test(tc_core, test_sprintf_16);
  tcase_add_test(tc_core, test_sprintf_17);
  tcase_add_test(tc_core, test_sprintf_18);
  tcase_add_test(tc_core, test_sprintf_19);
  tcase_add_test(tc_core, test_sprintf_20);
  tcase_add_test(tc_core, test_sprintf_21);
  tcase_add_test(tc_core, test_sprintf_22);
  tcase_add_test(tc_core, test_sprintf_23);
  tcase_add_test(tc_core, test_sprintf_24);
  tcase_add_test(tc_core, test_sprintf_25);
  tcase_add_test(tc_core, test_sprintf_26);
  tcase_add_test(tc_core, test_sprintf_27);
  tcase_add_test(tc_core, test_sprintf_28);
  tcase_add_test(tc_core, test_sprintf_29);
  tcase_add_test(tc_core, test_sprintf_30);
  tcase_add_test(tc_core, test_sprintf_31);
  tcase_add_test(tc_core, test_sprintf_32);
  tcase_add_test(tc_core, test_sprintf_33);
  tcase_add_test(tc_core, test_sprintf_34);
  tcase_add_test(tc_core, test_sprintf_35);
  tcase_add_test(tc_core, test_sprintf_36);
  tcase_add_test(tc_core, test_sprintf_37);
  tcase_add_test(tc_core, test_sprintf_38);
  tcase_add_test(tc_core, test_sprintf_39);
  tcase_add_test(tc_core, test_sprintf_40);
  tcase_add_test(tc_core, test_sprintf_41);
  tcase_add_test(tc_core, test_sprintf_42);
  tcase_add_test(tc_core, test_sprintf_43);
  tcase_add_test(tc_core, test_sprintf_44);
  tcase_add_test(tc_core, test_sprintf_45);
  tcase_add_test(tc_core, test_sprintf_46);
  tcase_add_test(tc_core, test_sprintf_47);
  tcase_add_test(tc_core, test_sprintf_48);
  tcase_add_test(tc_core, test_sprintf_49);
  tcase_add_test(tc_core, test_sprintf_50);
  tcase_add_test(tc_core, test_sprintf_51);
  tcase_add_test(tc_core, test_sprintf_52);
  tcase_add_test(tc_core, test_sprintf_53);
  tcase_add_test(tc_core, test_sprintf_54);
  tcase_add_test(tc_core, test_sprintf_55);
  tcase_add_test(tc_core, test_sprintf_56);
  tcase_add_test(tc_core, test_sprintf_57);
  tcase_add_test(tc_core, test_sprintf_58);
  tcase_add_test(tc_core, test_sprintf_59);
  tcase_add_test(tc_core, test_sprintf_60);
  tcase_add_test(tc_core, test_sprintf_61);
  tcase_add_test(tc_core, test_sprintf_62);
  tcase_add_test(tc_core, test_sprintf_63);
  tcase_add_test(tc_core, test_sprintf_64);
  tcase_add_test(tc_core, test_sprintf_65);
  tcase_add_test(tc_core, test_sprintf_66);
  tcase_add_test(tc_core, test_sprintf_67);
  tcase_add_test(tc_core, test_sprintf_68);
  tcase_add_test(tc_core, test_sprintf_69);
  tcase_add_test(tc_core, test_sprintf_70);
  tcase_add_test(tc_core, test_sprintf_71);
  tcase_add_test(tc_core, test_sprintf_72);
  tcase_add_test(tc_core, test_sprintf_73);
  tcase_add_test(tc_core, test_sprintf_74);
  tcase_add_test(tc_core, test_sprintf_75);
  tcase_add_test(tc_core, test_sprintf_76);
  tcase_add_test(tc_core, test_sprintf_77);
  tcase_add_test(tc_core, test_sprintf_78);
  tcase_add_test(tc_core, test_sprintf_79);
  tcase_add_test(tc_core, test_sprintf_80);
  tcase_add_test(tc_core, test_sprintf_81);
  tcase_add_test(tc_core, test_sprintf_82);
  tcase_add_test(tc_core, test_sprintf_83);
  tcase_add_test(tc_core, test_sprintf_84);
  tcase_add_test(tc_core, test_sprintf_85);
  tcase_add_test(tc_core, test_sprintf_86);
  tcase_add_test(tc_core, test_sprintf_87);
  tcase_add_test(tc_core, test_sprintf_88);
  tcase_add_test(tc_core, test_sprintf_89);
  tcase_add_test(tc_core, test_sprintf_90);
  tcase_add_test(tc_core, test_sprintf_91);
  tcase_add_test(tc_core, test_sprintf_92);
  tcase_add_test(tc_core, test_sprintf_93);
  tcase_add_test(tc_core, test_sprintf_94);
  tcase_add_test(tc_core, test_sprintf_95);
  tcase_add_test(tc_core, test_sprintf_96);
  tcase_add_test(tc_core, test_sprintf_97);
  tcase_add_test(tc_core, test_sprintf_98);
  tcase_add_test(tc_core, test_sprintf_99);
  tcase_add_test(tc_core, test_sprintf_100);
  tcase_add_test(tc_core, test_sprintf_101);
  tcase_add_test(tc_core, test_sprintf_102);
  tcase_add_test(tc_core, test_sprintf_103);
  tcase_add_test(tc_core, test_sprintf_104);
  tcase_add_test(tc_core, test_sprintf_105);
  tcase_add_test(tc_core, test_sprintf_106);
  tcase_add_test(tc_core, test_sprintf_107);
  tcase_add_test(tc_core, test_sprintf_108);
  tcase_add_test(tc_core, test_sprintf_109);
  tcase_add_test(tc_core, test_sprintf_110);
  tcase_add_test(tc_core, test_sprintf_111);
  tcase_add_test(tc_core, test_sprintf_112);
  tcase_add_test(tc_core, test_sprintf_113);
  tcase_add_test(tc_core, test_sprintf_114);
  tcase_add_test(tc_core, test_sprintf_115);
  tcase_add_test(tc_core, test_sprintf_116);
  tcase_add_test(tc_core, test_sprintf_117);
  tcase_add_test(tc_core, test_sprintf_118);
  tcase_add_test(tc_core, test_sprintf_119);
  tcase_add_test(tc_core, test_sprintf_120);
  tcase_add_test(tc_core, test_sprintf_121);
  tcase_add_test(tc_core, test_sprintf_122);
  tcase_add_test(tc_core, test_sprintf_123);
  tcase_add_test(tc_core, test_sprintf_124);
  tcase_add_test(tc_core, test_sprintf_125);
  tcase_add_test(tc_core, test_sprintf_126);
  tcase_add_test(tc_core, test_sprintf_127);
  tcase_add_test(tc_core, test_sprintf_128);
  tcase_add_test(tc_core, test_sprintf_129);
  tcase_add_test(tc_core, test_sprintf_130);
  tcase_add_test(tc_core, test_sprintf_131);
  tcase_add_test(tc_core, test_sprintf_132);
  tcase_add_test(tc_core, test_sprintf_133);
  tcase_add_test(tc_core, test_sprintf_134);
  tcase_add_test(tc_core, test_sprintf_135);
  tcase_add_test(tc_core, test_sprintf_136);
  tcase_add_test(tc_core, test_sprintf_137);
  tcase_add_test(tc_core, test_sprintf_138);
  tcase_add_test(tc_core, test_sprintf_139);
  tcase_add_test(tc_core, test_sprintf_140);
  tcase_add_test(tc_core, test_sprintf_141);
  tcase_add_test(tc_core, test_sprintf_142);
  tcase_add_test(tc_core, test_sprintf_143);
  tcase_add_test(tc_core, test_sprintf_144);
  tcase_add_test(tc_core, test_sprintf_145);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_memcpytest(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("memcpy");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcpy_empty_string);
  tcase_add_test(tc_core, test_memcpy_same_string);
  tcase_add_test(tc_core, test_memcpy_partial_string);
  tcase_add_test(tc_core, test_memcpy_overlap);
  tcase_add_test(tc_core, test_memcpy_null_pointer);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_strncpytest(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strncpy");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncpy_empty_string);
  tcase_add_test(tc_core, test_strncpy_same_string);
  tcase_add_test(tc_core, test_strncpy_partial_string);
  tcase_add_test(tc_core, test_strncpy_null_termination);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_strcspntest(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strcpn");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strcspn_no_matching_characters);
  tcase_add_test(tc_core, test_strcspn_matching_character_at_beginning);
  tcase_add_test(tc_core, test_strcspn_matching_character_at_end);
  tcase_add_test(tc_core, test_strcspn_matching_character_in_middle);
  tcase_add_test(tc_core, test_strcspn_empty_string);

  suite_add_tcase(s, tc_core);

  return s;
}

/*--------------------Test strstr----------------------*/
START_TEST(test_strstr_1) {
  ck_assert_ptr_eq(strstr("Hello World", "d"), s21_strstr("Hello World", "d"));
}
END_TEST

START_TEST(test_strstr_2) {
  ck_assert_ptr_eq(strstr("Hello World", "ll"),
                   s21_strstr("Hello World", "ll"));
}
END_TEST

START_TEST(test_strstr_3) {
  ck_assert_ptr_eq(strstr("Hello World", ""), s21_strstr("Hello World", ""));
}

START_TEST(test_strstr_4) {
  ck_assert_ptr_eq(strstr("", "as"), s21_strstr("", "as"));
}
END_TEST

START_TEST(test_strstr_5) {
  ck_assert_ptr_eq(strstr("ABOBA privet ABOBY poka", "ABOBY"),
                   s21_strstr("ABOBA privet ABOBY poka", "ABOBY"));
}
END_TEST
START_TEST(test_strstr_6) {
  ck_assert_ptr_eq(strstr("ABOBA privet ABOBY poka", "j"),
                   s21_strstr("ABOBA privet ABOBY poka", "j"));
}
END_TEST

/*--------------------Test strrchr----------------------*/

START_TEST(test_strrchr_1) {
  ck_assert_ptr_eq(strrchr("ABOBA privet ABOBY poka", 'A'),
                   s21_strrchr("ABOBA privet ABOBY poka", 'A'));
}
END_TEST

START_TEST(test_strrchr_2) {
  ck_assert_ptr_eq(strrchr("", 'A'), s21_strrchr("", 'A'));
}
END_TEST

START_TEST(test_strrchr_3) {
  ck_assert_ptr_eq(strrchr("ABOBA privet ABOBY poka", 'h'),
                   s21_strrchr("ABOBA privet ABOBY poka", 'h'));
}
END_TEST

START_TEST(test_strrchr_4) {
  ck_assert_ptr_eq(strrchr("ABOBA privet ABOBY poka", 'B'),
                   s21_strrchr("ABOBA privet ABOBY poka", 'B'));
}
END_TEST

START_TEST(test_strrchr_5) {
  ck_assert_ptr_eq(strrchr("ABOBA privet! ABOBY poka!", '!'),
                   s21_strrchr("ABOBA privet! ABOBY poka!", '!'));
}
END_TEST

/*--------------------Test trim----------------------*/

START_TEST(test_trim_1) {
  char *expected_result = " privet ABOBY poka ";
  char *func_result = s21_trim("ABOBA privet ABOBY poka ABOBA", "ABOBA");

  ck_assert_str_eq(expected_result, func_result);
  free(func_result);
}
END_TEST

START_TEST(test_trim_2) {
  char *expected_result = " privet ABOBY poka ";
  char *func_result =
      s21_trim("ABOBAABOBAABOBA privet ABOBY poka ABOBAABOBAABOBA", "ABOBA");

  ck_assert_str_eq(expected_result, func_result);
  free(func_result);
}
END_TEST

START_TEST(test_trim_3) {
  char *expected_result = "yBAABOB privet ABOBY poka OBAAx";
  char *func_result =
      s21_trim("ABOyBAABOB privet ABOBY poka OBAAxBOBA", "ABOBA");

  ck_assert_str_eq(expected_result, func_result);
  free(func_result);
}
END_TEST

START_TEST(test_trim_4) {
  char *func_result = s21_trim("", "ABOBA");
  ck_assert_ptr_null(func_result);
  free(func_result);
}
END_TEST

START_TEST(test_trim_5) {
  char *expected_result = "ABOBA privet ABOBY poka ABOBA";
  char *func_result = s21_trim("ABOBA privet ABOBY poka ABOBA", "");

  ck_assert_str_eq(expected_result, func_result);
  free(func_result);
}
END_TEST

/*--------------------Test trim----------------------*/

START_TEST(test_sscanf_d) {
  int a1, a2, a5, a6, a7;
  int b1, b2, b5, b6, b7;
  short h1, h2;
  const char *str = "-123 -87246827234 111 0 5555 -234";
  ck_assert_int_eq(
      sscanf(str, "%d%d%d%d%*d%2d%hd", &a1, &a2, &a5, &a6, &a7, &h1),
      s21_sscanf(str, "%d%d%d%d%*d%2d%hd", &b1, &b2, &b5, &b6, &b7, &h2));

  ck_assert_int_eq(h1, h1);
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(a2, b2);
  ck_assert_int_eq(a5, b5);
  ck_assert_int_eq(a6, b6);
  ck_assert_int_eq(a7, b7);
}
END_TEST

START_TEST(test_sscanf_c) {
  char a1 = '0', a2 = '0', a4 = '0';
  char a5[3] = {'\0'};
  char b1 = '0', b2 = '0', b4 = '0';
  char b5[3] = {'\0'};
  const char *str = "ABcdйqw";
  int res = s21_sscanf(str, "%c%c%*c%c%*c%2c", &a1, &a2, &a4, a5);
  int res1 = sscanf(str, "%c%c%*c%c%*c%2c", &b1, &b2, &b4, b5);
  ck_assert_int_eq(res, res1);
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(a2, b2);
  ck_assert_int_eq(a4, b4);
  ck_assert_str_eq(a5, b5);
}
END_TEST

START_TEST(test_sscanf_s) {
  char a1[100] = {'\0'}, a2[100] = {'\0'}, a4[100] = {'\0'}, a5[100] = {'\0'},
       a6[100] = {'\0'};
  char b1[100] = {'\0'}, b2[100] = {'\0'}, b4[100] = {'\0'}, b5[100] = {'\0'},
       b6[100] = {'\0'};
  wchar_t a3[200] = {0}, b3[400] = {0};
  const char *wStr = "アボバ";
  const char *str = "ABOBA privet ABOBY poka ABOBA ABOBY Заобобил";
  int res = s21_sscanf(str, "%s%s%s%*s%s%s", a1, a2, a4, a5, a6);
  int res1 = sscanf(str, "%s%s%s%*s%s%s", b1, b2, b4, b5, b6);
  ck_assert_int_eq(res, res1);
  int resW1 = s21_sscanf(wStr, "%ls", b3);
  int resW2 = sscanf(wStr, "%ls", a3);
  ck_assert_int_eq(resW2, resW1);
  ck_assert_str_eq(a1, b1);
  ck_assert_str_eq(a2, b2);
  ck_assert_str_eq(a4, b4);
  ck_assert_str_eq(a5, b5);
  ck_assert_str_eq(a6, b6);
}
END_TEST

START_TEST(test_sscanf_f) {
  float a1 = 0.0, a2 = 0.0;
  float b1 = 0.0, b2 = 0.0;
  double a3 = 0.0, b3 = 0.0;
  long double a4 = 0.0, b4 = 0.0;
  const char str[] = "-12345.445 12.34e+07 -0.0 1234e-07 pisos";
  s21_sscanf(str, "%f%f%lf%Lf", &a1, &a2, &a3, &a4);
  sscanf(str, "%f%f%lf%Lf", &b1, &b2, &b3, &b4);
  ck_assert_float_eq(a1, b1);
  ck_assert_float_eq(a2, b2);
  ck_assert_float_eq(a3, b3);
  ck_assert_float_eq(a4, b4);
}
END_TEST

START_TEST(test_sscanf_u) {
  unsigned int a1, b1, a2, b2;
  unsigned short c1, c2;
  unsigned long d1, d2;
  const char str[] = "12 123 -1 3444 123456";
  int res1 = sscanf(str, "%u%*u%u%hu%lu", &a1, &b1, &c1, &d1);
  int res2 = s21_sscanf(str, "%u%*u%u%hu%lu", &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_o) {
  unsigned int a1, b1, c1, d1, a2, b2, c2, d2;
  a1 = 1, a2 = 1, b1 = 1, b2 = 1, c1 = 1, c2 = 1, d1 = 1, d2 = 1;
  const char str[] = "1775 012 1 674";
  int r1 = sscanf(str, "%o%o%o%o", &a1, &b1, &c1, &d1);
  int r2 = s21_sscanf(str, "%o%o%o%o", &a2, &b2, &c2, &d2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_i) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  const char str[] = "1775 12 0xA 0x2F -10";
  int r1 = sscanf(str, "%i%i%i%i%*i", &a1, &b1, &c1, &d1);
  int r2 = s21_sscanf(str, "%i%i%i%i%*i", &a2, &b2, &c2, &d2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_x) {
  unsigned int a1, b1, c1, d1, a2, b2, c2, d2;
  const char str[] = "1775 12 0xA 0x2F 0x1";
  int r1 = sscanf(str, "%x%x%x%x%*x", &a1, &b1, &c1, &d1);
  int r2 = s21_sscanf(str, "%x%x%x%x%*x", &a2, &b2, &c2, &d2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_p) {
  int i = 5;
  int *p1;
  int *p2;
  char str[50] = {'\0'};
  sprintf(str, "%p", (void *)&i);
  sscanf(str, "%p", (void **)&p1);
  s21_sscanf(str, "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(test_sscanf_g) {
  float a1 = 0.0, a2 = 0.0;
  float b1 = 0.0, b2 = 0.0;
  double a3 = 0.0, b3 = 0.0;
  long double a4 = 0.0, b4 = 0.0;
  const char str[] = "-12345.445 12.34e+07 -0.0 1234e-07 pisos";
  s21_sscanf(str, "%g%G%lg%Lg", &a1, &a2, &a3, &a4);
  sscanf(str, "%g%G%lg%Lg", &b1, &b2, &b3, &b4);
  ck_assert_float_eq(a1, b1);
  ck_assert_float_eq(a2, b2);
  ck_assert_float_eq(a3, b3);
  ck_assert_float_eq(a4, b4);
}
END_TEST

START_TEST(test_sscanf_e) {
  float a1 = 0.0, b1 = 0.0;
  double a2 = 0.0, b2 = 0.0;
  float a3 = 0.0, b3 = 0.0;
  float a4 = 0.0, b4 = 0.0;
  const char str[] = " 12.34e+07 -0.0e+01 1234e-07 12234e-07";
  s21_sscanf(str, "%e%le%e%e", &a1, &a2, &a3, &a4);
  sscanf(str, "%e%le%e%e", &b1, &b2, &b3, &b4);
  ck_assert_float_eq(a1, b1);
  ck_assert_float_eq(a2, b2);
  ck_assert_float_eq(a3, b3);
  ck_assert_float_eq(a4, b4);
}
END_TEST

START_TEST(test_sscanf_n) {
  char a1[100] = {'\0'}, a2[100] = {'\0'};
  int c1 = 0, c2 = 0;
  int b1 = 0, b2 = 0;
  int d1 = 0, d2 = 0;
  const char str[] = " helloqweasfdfh 123 23";
  int r1 = s21_sscanf(str, "%s%d%n%d", a1, &b1, &c1, &d1);
  int r2 = sscanf(str, "%s%d%n%d", a2, &b2, &c2, &d2);
  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

Suite *s21_strstr_test() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_strstr");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strstr_1);
  tcase_add_test(tc_core, test_strstr_2);
  tcase_add_test(tc_core, test_strstr_3);
  tcase_add_test(tc_core, test_strstr_4);
  tcase_add_test(tc_core, test_strstr_5);
  tcase_add_test(tc_core, test_strstr_6);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *s21_strrchr_test() {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strrchr_1);
  tcase_add_test(tc_core, test_strrchr_2);
  tcase_add_test(tc_core, test_strrchr_3);
  tcase_add_test(tc_core, test_strrchr_4);
  tcase_add_test(tc_core, test_strrchr_5);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *s21_trim_test() {
  Suite *s = suite_create("s21_trim");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_trim_1);
  tcase_add_test(tc_core, test_trim_2);
  tcase_add_test(tc_core, test_trim_3);
  tcase_add_test(tc_core, test_trim_4);
  tcase_add_test(tc_core, test_trim_5);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *s21_sscanf_test() {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sscanf_d);
  (void)(test_sscanf_c);
  (void)(test_sscanf_s);
  tcase_add_test(tc_core, test_sscanf_c);
  tcase_add_test(tc_core, test_sscanf_s);
  tcase_add_test(tc_core, test_sscanf_f);
  tcase_add_test(tc_core, test_sscanf_o);
  tcase_add_test(tc_core, test_sscanf_u);
  tcase_add_test(tc_core, test_sscanf_i);
  tcase_add_test(tc_core, test_sscanf_x);
  tcase_add_test(tc_core, test_sscanf_p);
  tcase_add_test(tc_core, test_sscanf_g);
  tcase_add_test(tc_core, test_sscanf_e);
  tcase_add_test(tc_core, test_sscanf_n);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  setlocale(LC_ALL, "");
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  typedef Suite *(*func)(void);
  func funcs[NUMBER_OF_FUNCS] = {
      &s21_memcpytest,    &s21_strncpytest,   &s21_strcspntest,
      &s21_sprintftest,   &s21_to_upper_test, &s21_strlen_test,
      &s21_strncmp_test,  &s21_strpbrk_test,  &s21_insert_test,
      &s21_strchr_test,   &s21_strncat_test,  &s21_memset_test,
      s21_memcmp_test,    s21_memchr_tests,   s21_strtok_tests,
      s21_to_lower_tests, s21_strerror_tests, &s21_strstr_test,
      &s21_strrchr_test,  &s21_trim_test,     &s21_sscanf_test};

  for (int i = 0; i < NUMBER_OF_FUNCS; i++) {
    s = funcs[i]();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
