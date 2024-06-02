#include "s21_decimal.h"

int s21_add(s21_decimal a, s21_decimal b, s21_decimal* res) {
  int code = OK;
  reset_decimal(res);
  int sign_a = get_sign(a);
  int sign_b = get_sign(b);

  if (sign_a != sign_b) {
    s21_decimal* positive = (sign_a == PLUS) ? &a : &b;
    s21_decimal* negative = (sign_a == MINUS) ? &a : &b;
    set_sign(negative, PLUS);
    code = s21_sub(*positive, *negative, res);
    // fix for tests
    if (sign_a == MINUS && is_decimal_equal_zero(*res)) set_sign(res, MINUS);
  } else {
    code = addition_handler(a, b, res);
  }

  return code;
}

int s21_sub(s21_decimal a, s21_decimal b, s21_decimal* res) {
  int code = OK;
  reset_decimal(res);
  int sign_a = get_sign(a);
  int sign_b = get_sign(b);

  if (sign_a != sign_b) {
    s21_decimal* negative = (sign_a == MINUS) ? &a : &b;
    set_sign(negative, PLUS);
    code = s21_add(a, b, res);
    if (sign_a) set_sign(res, MINUS);  // -a - b = - (a + b)
    if (code != OK) code += sign_a;
  } else {
    code = subtraction_handler(a, b, res);
    if (sign_a == MINUS) res->bits[3] ^= SIGN;
  }

  return code;
}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal* res) {
  int code = OK;
  reset_decimal(res);
  int sign = get_sign(a) ^ get_sign(b);
  int scale = get_scale(a) + get_scale(b);
  int count_a = count_set_bits(a);
  int count_b = count_set_bits(b);
  if (count_a && count_b) {
    work_decimal wa = to_work_decimal(a);
    work_decimal wb = to_work_decimal(b);
    work_decimal wres = {0};

    int count = (count_a > count_b) ? count_b : count_a;
    work_decimal* max = (count_a >= count_b) ? &wa : &wb;
    work_decimal* min = (count_a < count_b) ? &wa : &wb;
    int index = 0;
    while (count) {
      if (get_bit(*min, index)) {
        work_add(wres, *max, &wres);
        count--;
      }
      *max = binary_shift_left(*max, 1);
      index++;
    }
    wres.sign = sign;
    wres.scale = scale;
    code = to_decimal(wres, res);
    if (code != OK) code += wres.sign;
  }
  return code;
}

int s21_div(s21_decimal a, s21_decimal b, s21_decimal* res) {
  int code = OK;
  reset_decimal(res);
  int sign = get_sign(a) ^ get_sign(b);
  set_sign(&a, PLUS);
  set_sign(&b, PLUS);

  if (is_decimal_equal_zero(b)) {
    code = DIV_ZERO;
  } else if (!is_decimal_equal_zero(a)) {
    work_decimal wa = to_work_decimal(a);
    work_decimal wb = to_work_decimal(b);
    work_decimal wres = {0};
    work_decimal remainder = {0};

    to_equal_scale(&wa, &wb);
    binary_division(wa, wb, &wres, &remainder);
    code = division_handler(&wres, wb, remainder);
    if (code == OK) {
      code = to_decimal(wres, res);
    }

    if (code != OK) code += sign;
  }
  set_sign(res, sign);

  return code;
}