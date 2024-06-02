#include <check.h>
#include <limits.h>

#include "s21_decimal.h"
#define CONVERTING_ERROR 1
#define SUCCESS 0

START_TEST(is_less_0) {
  s21_decimal value_1 = {0}, value_2 = {0};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_1) {
  s21_decimal value_1 = {{134, 0, 0, 0}}, value_2 = {{0, 556, 0, 0}};
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_2) {
  s21_decimal value_1 = {{777, 0, 0, 0}}, value_2 = {{777, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_3) {
  s21_decimal value_1 = {{5566, 0, 0, 0}}, value_2 = {{4674, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_4) {
  s21_decimal value_1 = {{12, 0, 0, 0}}, value_2 = {{12, 0, 0, 0}};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_5) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_6) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 0);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_7) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 0);
  set_bit_dec(&value_1, 77, 1);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_8) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 77, 1);
  set_scale(&value_1, 5);
  set_scale(&value_2, 5);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_9) {
  s21_decimal value_1 = {{12, UINT_MAX, 111, 0}},
              value_2 = {{0, UINT_MAX, 112, 0}};
  set_scale(&value_1, 12);
  set_scale(&value_2, 11);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_10) {
  s21_decimal value_1 = {{567, 443, 0, 0}}, value_2 = {{567, 444, 0, 0}};
  set_scale(&value_1, 13);
  set_scale(&value_2, 14);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_11) {
  s21_decimal value_1 = {{0, 44567, 0, 0}}, value_2 = {{0, 0, 0, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_12) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 45, 1);
  set_scale(&value_1, 16);
  set_scale(&value_2, 15);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

START_TEST(is_less_13) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 77, 1);
  set_bit_dec(&value_2, 76, 1);
  set_scale(&value_1, 15);
  set_scale(&value_2, 16);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Больше
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_greater_0) {
  s21_decimal value_1 = {0}, value_2 = {0};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_1) {
  s21_decimal value_1 = {{134, 0, 0, 0}}, value_2 = {{0, 556, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_2) {
  s21_decimal value_1 = {{777, 0, 0, 0}}, value_2 = {{777, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_3) {
  s21_decimal value_1 = {{5566, 0, 0, 0}}, value_2 = {{4674, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_4) {
  s21_decimal value_1 = {{12, 0, 0, 0}}, value_2 = {{12, 0, 0, 0}};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_5) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_6) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 0);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_7) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 0);
  set_bit_dec(&value_1, 77, 1);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}

END_TEST

START_TEST(is_greater_8) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 77, 1);
  set_scale(&value_1, 5);
  set_scale(&value_2, 5);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_9) {
  s21_decimal value_1 = {{UINT_MAX, 345, 111, 0}},
              value_2 = {{UINT_MAX, 345, 112, 0}};
  set_scale(&value_1, 12);
  set_scale(&value_2, 11);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_10) {
  s21_decimal value_1 = {{567, 443, 0, 0}}, value_2 = {{567, 444, 0, 0}};
  set_scale(&value_1, 13);
  set_scale(&value_2, 14);
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_11) {
  s21_decimal value_1 = {{0, 44567, 0, 0}}, value_2 = {{0, 0, 0, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_12) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 45, 1);
  set_scale(&value_1, 16);
  set_scale(&value_2, 15);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_13) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 77, 1);
  set_bit_dec(&value_2, 76, 1);
  set_scale(&value_1, 15);
  set_scale(&value_2, 16);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_14) {
  s21_decimal value_1 = {{0, 346678, 0, 0}}, value_2 = {{0, 0, 455678, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// меньше или равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_greater_or_equal_0) {
  s21_decimal value_1 = {{0, 0, 0, 0}}, value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal value_1 = {{655678, 0, 0, 0}}, value_2 = {{655678, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}}, value_2 = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal value_1 = {{455678, 246678, 0, 0}},
              value_2 = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal value_1 = {{455678, 346678, 0, 0}},
              value_2 = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}},
              value_2 = {{777, 346678, 455678, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal value_1 = {{455678, 346678, 0, 0}},
              value_2 = {{455678, 346678, 0, 0}};
  set_scale(&value_1, 14);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_8) {
  s21_decimal value_1 = {{777, 0, 1234567, 0}},
              value_2 = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_9) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}},
              value_2 = {{777, 346678, 555678, 0}};
  set_scale(&value_1, 12);
  set_scale(&value_2, 13);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_10) {
  s21_decimal value_1 = {{333, 0, 1234567, 0}},
              value_2 = {{333, 202, 1234567, 0}};
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_11) {
  s21_decimal value_1 = {{0, 346678, 0, 0}}, value_2 = {{0, 0, 455678, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_12) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 10);
  set_scale(&value_2, 12);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_greater_or_equal_13) {
  s21_decimal value_1 = {{67295, 7777666, 1234567, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 10);
  set_scale(&value_2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// больше или равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_less_or_equal_0) {
  s21_decimal value_1 = {{655678, 0, 0, 0}}, value_2 = {{655678, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal value_1 = {0}, value_2 = {0};
  value_1.bits[0] = 655678;
  value_2.bits[0] = 455678;
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}}, value_2 = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal value_1 = {{455678, 246678, 0, 0}},
              value_2 = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal value_1 = {{455678, 346678, 0, 0}},
              value_2 = {{455678, 346678, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}},
              value_2 = {{777, 346678, 455678, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal value_1 = {{455678, 346678, 0, 0}},
              value_2 = {{455678, 346678, 0, 0}};
  set_scale(&value_1, 14);
  set_scale(&value_2, 13);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal value_1 = {{777, 0, 1234567, 0}},
              value_2 = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_9) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}},
              value_2 = {{777, 346678, 555678, 0}};
  set_scale(&value_1, 12);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_10) {
  s21_decimal value_1 = {{333, 0, 1234567, 0}},
              value_2 = {{333, 202, 1234567, 0}};
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_11) {
  s21_decimal value_1 = {{0, 346678, 0, 0}}, value_2 = {{0, 0, 455678, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_12) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 10);
  set_scale(&value_2, 12);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

START_TEST(is_less_or_equal_13) {
  s21_decimal value_1 = {{67295, 7777666, 1234567, ~(UINT_MAX / 2)}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 10);
  set_scale(&value_2, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_equal_0) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_sign(&value_2, 1);
  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_2) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_2, 56, 1);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_3) {
  s21_decimal value_1 = {{0, 0, UINT_MAX, 0}},
              value_2 = {{0, 0, UINT_MAX, ~(UINT_MAX / 2)}};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_4) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_5) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 23, 1);
  set_bit_dec(&value_2, 34, 1);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_6) {
  s21_decimal value_1 = {{777, 0, 1234567, 0}},
              value_2 = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_7) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}},
              value_2 = {{777, 346678, 555678, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 3);
  set_scale(&value_2, 3);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_8) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 45, 1);
  set_bit_dec(&value_2, 56, 1);
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_9) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_scale(&value_1, 20);
  set_scale(&value_2, 5);
  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_10) {
  s21_decimal value_1 = {{0, 346678, 0, 0}}, value_2 = {{0, 455678, 0, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_11) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, 0, 0}};
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_12) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 53, 1);
  set_bit_dec(&value_2, 53, 1);
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

START_TEST(is_equal_13) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, 0, 0}};
  set_scale(&value_1, 13);
  set_scale(&value_2, 12);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// не равно
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(is_not_equal_0) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_sign(&value_2, 1);
  ck_assert_int_eq(0, s21_is_not_equal(value_1, value_2));
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_2, 56, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal value_1 = {{0, 0, UINT_MAX, 0}}, value_2 = {{0, 0, UINT_MAX, 0}};
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 23, 1);
  set_bit_dec(&value_2, 34, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal value_1 = {{777, 0, 1234567, 0}},
              value_2 = {{777, 202, 1234567, 0}};
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}},
              value_2 = {{777, 346678, 555678, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 3);
  set_scale(&value_2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 45, 1);
  set_bit_dec(&value_2, 56, 1);
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_9) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_scale(&value_1, 20);
  set_scale(&value_2, 5);
  ck_assert_int_eq(0, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_10) {
  s21_decimal value_1 = {{0, 346678, 0, 0}}, value_2 = {{0, 455678, 0, 0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_11) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, 0, 0}};
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_12) {
  s21_decimal value_1 = {0}, value_2 = {0};
  set_bit_dec(&value_1, 53, 1);
  set_bit_dec(&value_2, 53, 1);
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

START_TEST(is_not_equal_13) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, 0, 0}};
  set_scale(&value_1, 13);
  set_scale(&value_2, 12);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARITHMETICS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// вычитание
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(sub_0) {
  s21_decimal value_1 = {{345668, 3455, 234355, 0}},
              value_2 = {{678567, 435, 345554, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_1) {
  s21_decimal value_1 = {{345668, 3455, 234355, ~(UINT_MAX / 2)}},
              value_2 = {{678567, 435, 345554, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_2) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 654, 321, 0}},
              result;
  set_scale(&value_1, 13);
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_3) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 654, 321, 0}},
              result;
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_4) {
  s21_decimal value_1 = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_2 = {{987, 654, 321, 0}}, result;
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_5) {
  s21_decimal value_1 = {{123, 456, 789, ~(UINT_MAX / 2)}},
              value_2 = {{987, 654, 321, 0}}, result;
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_6) {
  s21_decimal value_1 = {{123, 456, 789, 0}},
              value_2 = {{987, 654, 321, ~(UINT_MAX / 2)}}, result;
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_7) {
  s21_decimal value_1 = {0}, value_2 = {0}, result;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_2 = {{987, 654, 321, 0}}, result;
  ck_assert_int_eq(2, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_9) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{987, 654, 321, 0}}, result;
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_2, 13);
  ck_assert_int_eq(2, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_10) {
  s21_decimal value_1 = {{5677, 0, 0, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_11) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{667, 545, 43, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(1, s21_sub(value_1, value_2, &result));
}

END_TEST

START_TEST(sub_12) {
  s21_decimal value_1 = {{667, 545, 43, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              result;
  ck_assert_int_eq(1, s21_sub(value_1, value_2, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// сложение
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(add_0) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 654, 321, 0}},
              result;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_1) {
  s21_decimal value_1 = {{UINT_MAX, 65656, 9876, 0}},
              value_2 = {{677, 0, 777, 0}}, result;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_2) {
  s21_decimal value_1 = {{5677, 0, 12333, 0}}, value_2 = {{0, 0, 0, 0}}, result;
  set_scale(&value_1, 19);
  set_bit_dec(&value_2, 86, 1);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_3) {
  s21_decimal value_1 = {{UINT_MAX, 456, 789, 0}},
              value_2 = {{987, UINT_MAX, 321, 0}}, result;
  set_scale(&value_1, 6);
  set_scale(&value_2, 4);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_4) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, value_2 = {{8, 0, 0, 0}},
              result;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_5) {
  s21_decimal value_1 = {0}, value_2 = {0}, result;
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_2, 33, 1);
  set_bit_dec(&value_1, 86, 1);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_6) {
  s21_decimal value_1 = {{123, 456, 789, 0}},
              value_2 = {{987, 654, 321, ~(UINT_MAX / 2)}}, result;
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_7) {
  s21_decimal value_1 = {{456, 321, 7777, ~(UINT_MAX / 2)}}, value_2 = {0},
              result;
  set_bit_dec(&value_2, 127, 1);
  set_bit_dec(&value_2, 77, 1);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_2 = {{987, UINT_MAX, 321, 0}}, result;
  set_scale(&value_2, 12);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_9) {
  s21_decimal value_1 = {{UINT_MAX, 0, 24444444, 0}},
              value_2 = {{UINT_MAX, 45666656, 234444, 0}}, result;
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

START_TEST(add_10) {
  s21_decimal value_1 = {{123, 0, 0, ~(UINT_MAX / 2)}},
              value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// умножение
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(mul_0) {
  s21_decimal value_1 = {{123, 1, 0, ~(UINT_MAX / 2)}},
              value_2 = {{987, 1, 0, 0}}, result = {{0}};
  set_scale(&value_1, 3);
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
}  // 2 -INF

END_TEST

START_TEST(mul_1) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 654, 321, 0}},
              result = {{0}};
  set_scale(&value_1, 8);
  set_scale(&value_2, 8);
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
}  // 1 +INF

END_TEST

START_TEST(mul_2) {
  s21_decimal value_1 = {{123, 456, UINT_MAX, 0}},
              value_2 = {{987, UINT_MAX, 321, 0}}, result = {{0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(1, s21_mul(value_1, value_2, &result));
}

END_TEST

START_TEST(mul_3) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 654, 321, 0}},
              result = {{0}};
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 12);
  set_scale(&value_2, 14);
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
}  // 1 +INF

END_TEST

START_TEST(mul_4) {
  s21_decimal value_1 = {{123, 456, 0, ~(UINT_MAX / 2)}},
              value_2 = {{987, 654, 0, 0}}, result = {{0}};
  set_bit_dec(&value_1, 33, 1);
  set_bit_dec(&value_2, 22, 1);
  set_scale(&value_1, 2);
  set_scale(&value_2, 2);
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
}  // 2 -INF

END_TEST

START_TEST(mul_5) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_2 = {{777, 0, 0, ~(UINT_MAX / 2)}}, result = {{0}};
  ck_assert_int_eq(1, s21_mul(value_1, value_2, &result));
}

END_TEST

START_TEST(mul_6) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_2 = {{2, 0, 0, 0}}, result = {{0}};
  ck_assert_int_eq(2, s21_mul(value_1, value_2, &result));
}

END_TEST

START_TEST(mul_7) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{22, 0, 0, 0}}, result = {{0}};
  ck_assert_int_eq(1, s21_mul(value_1, value_2, &result));
}

END_TEST

START_TEST(mul_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}},
              value_2 = {{0, 0, 0, 0}}, result = {{0}};
  set_bit_dec(&value_2, 35, 1);
  ck_assert_int_eq(2, s21_mul(value_1, value_2, &result));
}

END_TEST

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// деление
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(div_0) {
  s21_decimal value_1 = {{123, 456, 0, ~(UINT_MAX / 2)}},
              value_2 = {{987, 654, 0, 0}}, result;
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_1) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 0, 0, 0}},
              result;
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_2) {
  s21_decimal value_1 = {{12, 0, 0, 0}}, value_2 = {{3, 0, 0, 0}}, result;
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_3) {
  s21_decimal value_1 = {{12, 0, UINT_MAX, 0}}, value_2 = {{3, 345, 345, 0}},
              result;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_2, 15);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_4) {
  s21_decimal value_1 = {{123, 456, 789, 0}}, value_2 = {{987, 654, 321, 0}},
              result;
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 0, 0}},
              value_2 = {{UINT_MAX, UINT_MAX, 0, 0}}, result;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{100, 0, 0, 0}}, value_2 = {{25, 0, 0, 0}}, result;
  set_bit_dec(&value_1, 77, 1);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{12, 0, UINT_MAX, 0}}, value_2 = {{3, 0, UINT_MAX, 0}},
              result;
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {0}, value_2 = {0}, result;
  set_bit_dec(&value_1, 88, 1);
  set_bit_dec(&value_2, 88, 1);
  set_scale(&value_1, 4);
  set_scale(&value_2, 4);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{0, 0, 36, 0}}, value_2 = {{0, 0, 6, 0}}, result;
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 6);
  set_scale(&value_2, 6);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_10) {
  s21_decimal value_1 = {{50, 0, 0, 0}},
              value_2 = {{10, 0, 0, ~(UINT_MAX / 2)}}, result;
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_11) {
  s21_decimal value_1 = {{36, 0, 0, ~(UINT_MAX / 2)}},
              value_2 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result;
  set_bit_dec(&value_1, 127, 1);
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_12) {
  s21_decimal value_1 = {{12, 23, 123, ~(UINT_MAX / 2)}},
              value_2 = {{0, 0, 0, 0}}, result;
  ck_assert_int_eq(3, s21_div(value_1, value_2, &result));
}

END_TEST

START_TEST(div_13) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_2 = {{0, 0, 0, 0}}, result;
  ck_assert_int_eq(3, s21_div(value_1, value_2, &result));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Отбрасываем знаки после запятой
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(truncate_0) {
  s21_decimal value_1 = {{7, 7, 7, 0}}, result = {0};
  float result_f = 0, value_two_f = (float)129127208515966861312.0;
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(truncate_1) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0, value_two_f = (float)-2.0;
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(truncate_2) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0, value_two_f = (float)-2.0;
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(truncate_3) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0, value_two_f = (float)-0.0;
  set_scale(&value_1, 5);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal value_1 = {{128, 0, 0, 0}};
  s21_decimal result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  float result_f = 0;
  s21_from_decimal_to_float(result, &result_f);
  float value_two_f = 12;
  ck_assert_float_eq(value_two_f, result_f);
}
END_TEST

START_TEST(truncate_5) {
  s21_decimal value_1 = {{123456, 0, 0, 0}}, value_2 = {{123, 0, 0, 0}}, result;
  float result_f, value_two_f;
  set_scale(&value_1, 3);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(truncate_6) {
  s21_decimal value_1 = {{34445667, 0, 0, 0}}, value_2 = {{3, 0, 0, 0}}, result;
  float result_f, value_two_f;
  set_scale(&value_1, 7);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}}, value_2 = {{4294967, 0, 0, 0}},
              result;
  float result_f, value_two_f;
  set_scale(&value_1, 3);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(truncate_8) {
  s21_decimal value_1 = {{UINT_MAX, 1, 0, 0}}, value_2 = {{8, 0, 0, 0}}, result;
  float result_f, value_two_f;
  set_scale(&value_1, 9);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(truncate_10) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}}, value_2 = {{4, 0, 0, 0}}, result;
  float result_f, value_two_f;
  set_scale(&value_1, 9);
  ck_assert_int_eq(0, s21_truncate(value_1, &result));
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Возвращает результат умножения указанного Decimal на -1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(negate_0) {
  s21_decimal value_1 = {{2, 0, 0, 0}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(value_1), get_sign(result));
}

END_TEST

START_TEST(negate_1) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(value_1), get_sign(result));
}

END_TEST

START_TEST(negate_2) {
  s21_decimal value_1 = {{0, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(value_1), get_sign(result));
}

END_TEST

START_TEST(negate_3) {
  s21_decimal value_1 = {0}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(value_1), get_sign(result));
}

END_TEST

START_TEST(negate_4) {
  s21_decimal value_1 = {{655678, 0, 0, 0}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

START_TEST(negate_5) {
  s21_decimal value_1 = {{777, 346678, 455678, 0}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

START_TEST(negate_6) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

START_TEST(negate_7) {
  s21_decimal value_1 = {{67295, 7777666, 1234567, 0}}, result = {0};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 10);
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

START_TEST(negate_8) {
  s21_decimal value_1 = {{0, 346678, 0, 0}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

START_TEST(negate_9) {
  s21_decimal value_1 = {{UINT_MAX, 346678, UINT_MAX, 0}}, result = {0};
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

START_TEST(negate_10) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, 0, 0}}, result = {0};
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 5);
  s21_negate(value_1, &result);
  ck_assert_int_ne(get_sign(result), get_sign(value_1));
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(floor_0) {
  s21_decimal value_1 = {{4, 0, 0, 0}}, result = {0};
  ck_assert_int_eq(0, s21_floor(value_1, &result));
}

END_TEST

START_TEST(floor_1) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(-2, result_f);
}

END_TEST

START_TEST(floor_2) {
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  float result_f = 0;
  set_scale(&value_1, 5);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(-1, result_f);
}

END_TEST

START_TEST(floor_3) {
  s21_decimal value_1 = {{2, 0, 0, 0}}, result = {0};
  float result_f = 0;
  set_scale(&value_1, 5);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(0, result_f);
}

END_TEST

START_TEST(floor_4) {
  s21_decimal value_1 = {{123456, 0, 0, 0}}, value_2 = {{124, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 3);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_6) {
  s21_decimal value_1 = {{11, 0, 0, 0}}, value_2 = {{2, 0, 0, 0}}, result = {0};
  float result_f, value_two_f;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 1);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_7) {
  s21_decimal value_1 = {{34, 0, 0, 0}}, value_2 = {{1, 0, 0, 0}}, result = {0};
  float result_f, value_two_f;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 3);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_8) {
  s21_decimal value_1 = {{7777777, 0, 0, 0}}, value_2 = {{78, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 5);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_9) {
  s21_decimal value_1 = {{123456789, 0, 0, 0}}, value_2 = {{1, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 9);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

START_TEST(floor_10) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}}, value_2 = {{43, 0, 0, 0}},
              result = {0};
  float result_f, value_two_f;
  set_bit_dec(&value_1, 127, 1);
  set_bit_dec(&value_2, 127, 1);
  set_scale(&value_1, 8);
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция округляет Decimal до ближайшего целого числа
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(round_0) {
  s21_decimal value_1 = {{7, 7, 7, 0}}, result = {0};
  float result_f = 0, value_two_f = (float)129127208515966861312.0;
  s21_round(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

START_TEST(round_1) {
  s21_decimal value_1 = {{3, 3, 3, ~(UINT_MAX / 2)}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_2) {
  s21_decimal value_1 = {{3, 3, 3, 0}}, result = {0};
  set_scale(&value_1, 5);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_3) {
  s21_decimal value_1 = {{7, 7, 7, ~(UINT_MAX / 2)}}, result = {0};
  set_scale(&value_1, 5);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_4) {
  s21_decimal value_1 = {{25, 0, 0, ~(UINT_MAX / 2)}}, result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_5) {
  s21_decimal value_1 = {{26, 0, 0, 0}}, result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_6) {
  s21_decimal value_1 = {{115, 0, 0, 0}}, result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_7) {
  s21_decimal value_1 = {{118, 0, 0, 0}}, result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_8) {
  s21_decimal value_1 = {{125, 0, 0, 0}}, result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_9) {
  s21_decimal value_1 = {{345, 0, 0, 0}}, result = {0};
  set_scale(&value_1, 1);
  ck_assert_int_eq(0, s21_round(value_1, &result));
}

END_TEST

START_TEST(round_10) {
  s21_decimal value_1 = {{128, 0, 0, 0}}, result = {0};
  float result_f = 0, value_two_f = 13;
  set_scale(&value_1, 1);
  s21_round(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // CONVERSION
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Из s21_decimal во float
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_decimal_to_float_0) {
  s21_decimal value_1 = {{456123, 0, 0, 0}};
  float result = 0.456123, value_one_f = 0;
  set_scale(&value_1, 6);
  s21_from_float_to_decimal(result, &value_1);
  s21_from_decimal_to_float(value_1, &value_one_f);

  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal value_1 = {{77777, 0, 0, 0}};
  float result = -777.77, value_one_f;
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 2);
  s21_from_decimal_to_float(value_1, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal value_1 = {{123456789, 0, 0, 0}};
  float result = -1234.56789, value_one_f;
  set_bit_dec(&value_1, 127, 1);
  set_scale(&value_1, 5);
  s21_from_decimal_to_float(value_1, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_3) {
  s21_decimal value_1 = {{123456789, 1, 0, 0}};
  float result = 4.418424084, value_one_f;
  set_scale(&value_1, 9);
  s21_from_decimal_to_float(value_1, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_4) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}};
  float result = 42.94967295, value_one_f;
  set_scale(&value_1, 8);
  s21_from_decimal_to_float(value_1, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_5) {
  s21_decimal value_1 = {{UINT_MAX, 1, 0, 0}};
  float result = 85.89934590, value_one_f;
  set_scale(&value_1, 8);
  s21_from_decimal_to_float(value_1, &value_one_f);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_decimal_to_float_6) {
  s21_decimal value = {{18122, 0, 0, 0}};
  set_scale(&value, 3);
  set_sign(&value, 1);
  float end;
  float check = -18.122;
  int return_value = s21_from_decimal_to_float(value, &end);
  ck_assert_float_eq(end, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(from_decimal_to_float_7) {
  s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
  float end;
  float check = 16777215;
  int return_value = s21_from_decimal_to_float(value, &end);
  ck_assert_float_eq(end, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(from_decimal_to_float_8) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  float end;
  float check = 0xFFFFFFFFFFFFFFFF;
  int return_value = s21_from_decimal_to_float(value, &end);
  ck_assert_float_eq(end, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(from_decimal_to_float_9) {
  s21_decimal src;
  int end = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  end = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(end, 0);
}
END_TEST

START_TEST(from_decimal_to_float_10) {
  float src = 0.00000000000;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs(src - temp) < pow(10, -7)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(from_decimal_to_float_11) {
  float src = 0.01;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000100000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(from_decimal_to_float_12) {
  float src = 0.00000123;
  float temp = 0;
  s21_decimal value_1 = {{123, 0, 0, 0b00000000000010000000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(from_decimal_to_float_13) {
  float src = -0.01;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0x80020000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(from_decimal_to_float_14) {
  s21_decimal value = {{1812, 0, 0, 0}};
  set_sign(&value, 1);
  float end;
  float check = -1812;
  int return_value = s21_from_decimal_to_float(value, &end);
  ck_assert_float_eq(end, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из float во s21_decimal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_float_to_decimal_0) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  float result, value_one_f = -INFINITY;
  s21_from_float_to_decimal(value_one_f, &value_1);
  s21_from_decimal_to_float(value_1, &result);
  ck_assert_float_eq(result, 0);
}

END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  float result, value_one_f = -7777777.777;
  s21_from_float_to_decimal(value_one_f, &value_1);
  s21_from_decimal_to_float(value_1, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  float result, value_one_f = 4294.967;
  s21_from_float_to_decimal(value_one_f, &value_1);
  s21_from_decimal_to_float(value_1, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_3) {
  float f = 0.03;
  s21_decimal end;
  s21_decimal check = {{3, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = s21_from_float_to_decimal(f, &end);
  ck_assert_int_eq(s21_is_equal(end, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  float f = 1.0 / 0.0;
  s21_decimal end;
  int return_value = s21_from_float_to_decimal(f, &end);
  ck_assert_int_eq(return_value, CONVERTING_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  float f = 0.0 / 0.0;
  s21_decimal end;
  int return_value = s21_from_float_to_decimal(f, &end);
  ck_assert_int_eq(return_value, CONVERTING_ERROR);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  float src = 0.0000000;
  s21_decimal value_1 = {{0xffffff, 0xffffff, 0xffffff, 0xffffff}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(from_float_to_decimal_7) {
  float src = 1.23456789999;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {0};
  return_value = s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 1e-06);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  float src = 7.92281625143e+30;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  return_value = s21_from_float_to_decimal(src, &value_1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из s21_decimal в int
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_decimal_to_int_0) {
  s21_decimal value_1 = {{456789, 0, 0, 0}};
  int result = 456789, value_one_i = 0;
  s21_from_decimal_to_int(value_1, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal value_1 = {{123456789, 0, 0, 0}};
  int result = 123456789, value_one_i = 0;
  s21_from_decimal_to_int(value_1, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal value_1 = {{19121993, 0, 0, 0}};
  int result = -19121993, value_one_i = 0;
  set_bit_dec(&value_1, 127, 1);
  s21_from_decimal_to_int(value_1, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal value_1 = {{7777777, 0, 0, 0}};
  int result = 7777777, value_one_i = 0;
  s21_from_decimal_to_int(value_1, &value_one_i);
  ck_assert_int_eq(value_one_i, result);
}

END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Из int в s21_decimal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(from_int_to_decimal_0) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int result, value_one_i = 987654321;
  s21_from_int_to_decimal(value_one_i, &value_1);
  s21_from_decimal_to_int(value_1, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int result, value_one_i = -123456789;
  s21_from_int_to_decimal(value_one_i, &value_1);
  s21_from_decimal_to_int(value_1, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int result, value_one_i = -19121993;
  s21_from_int_to_decimal(value_one_i, &value_1);
  s21_from_decimal_to_int(value_1, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int result, value_one_i = 7777777;
  s21_from_int_to_decimal(value_one_i, &value_1);
  s21_from_decimal_to_int(value_1, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int result, value_one_i = UINT_MAX;
  s21_from_int_to_decimal(value_one_i, &value_1);
  s21_from_decimal_to_int(value_1, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

START_TEST(from_int_to_decimal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int result, value_one_i = -UINT_MAX;
  s21_from_int_to_decimal(value_one_i, &value_1);
  s21_from_decimal_to_int(value_1, &result);
  ck_assert_int_eq(result, value_one_i);
}

END_TEST

Suite *

s21_decimal_suite(void) {
  Suite *suite;

  suite = suite_create("s21_decimal");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, is_less_0);
  tcase_add_test(tcase_core, is_less_1);
  tcase_add_test(tcase_core, is_less_2);
  tcase_add_test(tcase_core, is_less_3);
  tcase_add_test(tcase_core, is_less_4);
  tcase_add_test(tcase_core, is_less_5);
  tcase_add_test(tcase_core, is_less_6);
  tcase_add_test(tcase_core, is_less_7);
  tcase_add_test(tcase_core, is_less_8);
  tcase_add_test(tcase_core, is_less_9);
  tcase_add_test(tcase_core, is_less_10);
  tcase_add_test(tcase_core, is_less_11);
  tcase_add_test(tcase_core, is_less_12);
  tcase_add_test(tcase_core, is_less_13);

  tcase_add_test(tcase_core, is_greater_0);
  tcase_add_test(tcase_core, is_greater_1);
  tcase_add_test(tcase_core, is_greater_2);
  tcase_add_test(tcase_core, is_greater_3);
  tcase_add_test(tcase_core, is_greater_4);
  tcase_add_test(tcase_core, is_greater_5);
  tcase_add_test(tcase_core, is_greater_6);
  tcase_add_test(tcase_core, is_greater_7);
  tcase_add_test(tcase_core, is_greater_8);
  tcase_add_test(tcase_core, is_greater_9);
  tcase_add_test(tcase_core, is_greater_10);
  tcase_add_test(tcase_core, is_greater_11);
  tcase_add_test(tcase_core, is_greater_12);
  tcase_add_test(tcase_core, is_greater_13);
  tcase_add_test(tcase_core, is_greater_14);

  tcase_add_test(tcase_core, is_greater_or_equal_0);
  tcase_add_test(tcase_core, is_greater_or_equal_1);
  tcase_add_test(tcase_core, is_greater_or_equal_2);
  tcase_add_test(tcase_core, is_greater_or_equal_3);
  tcase_add_test(tcase_core, is_greater_or_equal_4);
  tcase_add_test(tcase_core, is_greater_or_equal_5);
  tcase_add_test(tcase_core, is_greater_or_equal_6);
  tcase_add_test(tcase_core, is_greater_or_equal_7);
  tcase_add_test(tcase_core, is_greater_or_equal_8);
  tcase_add_test(tcase_core, is_greater_or_equal_9);
  tcase_add_test(tcase_core, is_greater_or_equal_10);
  tcase_add_test(tcase_core, is_greater_or_equal_11);
  tcase_add_test(tcase_core, is_greater_or_equal_12);
  tcase_add_test(tcase_core, is_greater_or_equal_13);

  tcase_add_test(tcase_core, is_less_or_equal_0);
  tcase_add_test(tcase_core, is_less_or_equal_1);
  tcase_add_test(tcase_core, is_less_or_equal_2);
  tcase_add_test(tcase_core, is_less_or_equal_3);
  tcase_add_test(tcase_core, is_less_or_equal_4);
  tcase_add_test(tcase_core, is_less_or_equal_5);
  tcase_add_test(tcase_core, is_less_or_equal_6);
  tcase_add_test(tcase_core, is_less_or_equal_7);
  tcase_add_test(tcase_core, is_less_or_equal_8);
  tcase_add_test(tcase_core, is_less_or_equal_9);
  tcase_add_test(tcase_core, is_less_or_equal_10);
  tcase_add_test(tcase_core, is_less_or_equal_11);
  tcase_add_test(tcase_core, is_less_or_equal_12);
  tcase_add_test(tcase_core, is_less_or_equal_13);

  tcase_add_test(tcase_core, is_equal_0);
  tcase_add_test(tcase_core, is_equal_1);
  tcase_add_test(tcase_core, is_equal_2);
  tcase_add_test(tcase_core, is_equal_3);
  tcase_add_test(tcase_core, is_equal_4);
  tcase_add_test(tcase_core, is_equal_5);
  tcase_add_test(tcase_core, is_equal_6);
  tcase_add_test(tcase_core, is_equal_7);
  tcase_add_test(tcase_core, is_equal_8);
  tcase_add_test(tcase_core, is_equal_9);
  tcase_add_test(tcase_core, is_equal_10);
  tcase_add_test(tcase_core, is_equal_11);
  tcase_add_test(tcase_core, is_equal_12);
  tcase_add_test(tcase_core, is_equal_13);

  tcase_add_test(tcase_core, is_not_equal_0);
  tcase_add_test(tcase_core, is_not_equal_1);
  tcase_add_test(tcase_core, is_not_equal_2);
  tcase_add_test(tcase_core, is_not_equal_3);
  tcase_add_test(tcase_core, is_not_equal_4);
  tcase_add_test(tcase_core, is_not_equal_5);
  tcase_add_test(tcase_core, is_not_equal_6);
  tcase_add_test(tcase_core, is_not_equal_7);
  tcase_add_test(tcase_core, is_not_equal_8);
  tcase_add_test(tcase_core, is_not_equal_9);
  tcase_add_test(tcase_core, is_not_equal_10);
  tcase_add_test(tcase_core, is_not_equal_11);
  tcase_add_test(tcase_core, is_not_equal_12);
  tcase_add_test(tcase_core, is_not_equal_13);

  tcase_add_test(tcase_core, sub_0);
  tcase_add_test(tcase_core, sub_1);
  tcase_add_test(tcase_core, sub_2);
  tcase_add_test(tcase_core, sub_3);
  tcase_add_test(tcase_core, sub_4);
  tcase_add_test(tcase_core, sub_5);
  tcase_add_test(tcase_core, sub_6);
  tcase_add_test(tcase_core, sub_7);
  tcase_add_test(tcase_core, sub_8);
  tcase_add_test(tcase_core, sub_9);
  tcase_add_test(tcase_core, sub_10);
  tcase_add_test(tcase_core, sub_11);
  tcase_add_test(tcase_core, sub_12);

  tcase_add_test(tcase_core, add_0);
  tcase_add_test(tcase_core, add_1);
  tcase_add_test(tcase_core, add_2);
  tcase_add_test(tcase_core, add_3);
  tcase_add_test(tcase_core, add_4);
  tcase_add_test(tcase_core, add_5);
  tcase_add_test(tcase_core, add_6);
  tcase_add_test(tcase_core, add_7);
  tcase_add_test(tcase_core, add_8);
  tcase_add_test(tcase_core, add_9);
  tcase_add_test(tcase_core, add_10);

  tcase_add_test(tcase_core, mul_0);
  tcase_add_test(tcase_core, mul_1);
  tcase_add_test(tcase_core, mul_2);
  tcase_add_test(tcase_core, mul_3);
  tcase_add_test(tcase_core, mul_4);
  tcase_add_test(tcase_core, mul_5);
  tcase_add_test(tcase_core, mul_6);
  tcase_add_test(tcase_core, mul_7);
  tcase_add_test(tcase_core, mul_8);

  tcase_add_test(tcase_core, div_0);
  tcase_add_test(tcase_core, div_1);
  tcase_add_test(tcase_core, div_2);
  tcase_add_test(tcase_core, div_3);
  tcase_add_test(tcase_core, div_4);
  tcase_add_test(tcase_core, div_5);
  tcase_add_test(tcase_core, div_6);
  tcase_add_test(tcase_core, div_7);
  tcase_add_test(tcase_core, div_8);
  tcase_add_test(tcase_core, div_9);
  tcase_add_test(tcase_core, div_10);
  tcase_add_test(tcase_core, div_11);
  tcase_add_test(tcase_core, div_12);
  tcase_add_test(tcase_core, div_13);

  tcase_add_test(tcase_core, truncate_0);
  tcase_add_test(tcase_core, truncate_1);
  tcase_add_test(tcase_core, truncate_2);
  tcase_add_test(tcase_core, truncate_3);
  tcase_add_test(tcase_core, truncate_4);
  tcase_add_test(tcase_core, truncate_5);
  tcase_add_test(tcase_core, truncate_6);
  tcase_add_test(tcase_core, truncate_6);
  tcase_add_test(tcase_core, truncate_7);
  tcase_add_test(tcase_core, truncate_8);
  tcase_add_test(tcase_core, truncate_10);

  tcase_add_test(tcase_core, negate_0);
  tcase_add_test(tcase_core, negate_1);
  tcase_add_test(tcase_core, negate_2);
  tcase_add_test(tcase_core, negate_3);
  tcase_add_test(tcase_core, negate_4);
  tcase_add_test(tcase_core, negate_5);
  tcase_add_test(tcase_core, negate_6);
  tcase_add_test(tcase_core, negate_7);
  tcase_add_test(tcase_core, negate_8);
  tcase_add_test(tcase_core, negate_9);
  tcase_add_test(tcase_core, negate_10);

  tcase_add_test(tcase_core, floor_0);
  tcase_add_test(tcase_core, floor_1);
  tcase_add_test(tcase_core, floor_2);
  tcase_add_test(tcase_core, floor_3);
  tcase_add_test(tcase_core, floor_4);
  tcase_add_test(tcase_core, floor_6);
  tcase_add_test(tcase_core, floor_7);
  tcase_add_test(tcase_core, floor_8);
  tcase_add_test(tcase_core, floor_9);
  tcase_add_test(tcase_core, floor_10);

  tcase_add_test(tcase_core, round_0);
  tcase_add_test(tcase_core, round_1);
  tcase_add_test(tcase_core, round_2);
  tcase_add_test(tcase_core, round_3);
  tcase_add_test(tcase_core, round_4);
  tcase_add_test(tcase_core, round_5);
  tcase_add_test(tcase_core, round_6);
  tcase_add_test(tcase_core, round_7);
  tcase_add_test(tcase_core, round_8);
  tcase_add_test(tcase_core, round_9);
  tcase_add_test(tcase_core, round_10);

  tcase_add_test(tcase_core, from_decimal_to_float_0);
  tcase_add_test(tcase_core, from_decimal_to_float_1);
  tcase_add_test(tcase_core, from_decimal_to_float_2);
  tcase_add_test(tcase_core, from_decimal_to_float_3);
  tcase_add_test(tcase_core, from_decimal_to_float_4);
  tcase_add_test(tcase_core, from_decimal_to_float_5);
  tcase_add_test(tcase_core, from_decimal_to_float_6);
  tcase_add_test(tcase_core, from_decimal_to_float_7);
  tcase_add_test(tcase_core, from_decimal_to_float_8);
  tcase_add_test(tcase_core, from_decimal_to_float_9);
  tcase_add_test(tcase_core, from_decimal_to_float_10);
  tcase_add_test(tcase_core, from_decimal_to_float_11);
  tcase_add_test(tcase_core, from_decimal_to_float_12);
  tcase_add_test(tcase_core, from_decimal_to_float_13);
  tcase_add_test(tcase_core, from_decimal_to_float_14);

  tcase_add_test(tcase_core, from_float_to_decimal_0);
  tcase_add_test(tcase_core, from_float_to_decimal_1);
  tcase_add_test(tcase_core, from_float_to_decimal_2);
  tcase_add_test(tcase_core, from_float_to_decimal_3);
  tcase_add_test(tcase_core, from_float_to_decimal_4);
  tcase_add_test(tcase_core, from_float_to_decimal_5);
  tcase_add_test(tcase_core, from_float_to_decimal_6);
  tcase_add_test(tcase_core, from_float_to_decimal_7);
  tcase_add_test(tcase_core, from_float_to_decimal_8);

  tcase_add_test(tcase_core, from_decimal_to_int_0);
  tcase_add_test(tcase_core, from_decimal_to_int_1);
  tcase_add_test(tcase_core, from_decimal_to_int_2);
  tcase_add_test(tcase_core, from_decimal_to_int_3);

  tcase_add_test(tcase_core, from_int_to_decimal_0);
  tcase_add_test(tcase_core, from_int_to_decimal_1);
  tcase_add_test(tcase_core, from_int_to_decimal_2);
  tcase_add_test(tcase_core, from_int_to_decimal_3);
  tcase_add_test(tcase_core, from_int_to_decimal_4);
  tcase_add_test(tcase_core, from_int_to_decimal_5);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = s21_decimal_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  if (failed_count == 0) {
    printf("\033[32mAll tests passed!\033[0m\n");
    return EXIT_SUCCESS;
  } else {
    printf("\033[31mSome tests failed!\033[0m\n");
    return EXIT_FAILURE;
  }
}
