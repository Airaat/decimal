#include "s21_decimal.h"

int addition_handler(s21_decimal a, s21_decimal b, s21_decimal* res) {
  int code = OK;
  work_decimal wa = to_work_decimal(a);
  work_decimal wb = to_work_decimal(b);
  work_decimal wres = {0};
  to_equal_scale(&wa, &wb);
  work_add(wa, wb, &wres);
  code = to_decimal(wres, res);
  if (code != OK) code += wa.sign;
  return code;
}

int subtraction_handler(s21_decimal a, s21_decimal b, s21_decimal* res) {
  int code = OK;
  work_decimal wa = to_work_decimal(a);
  work_decimal wb = to_work_decimal(b);
  to_equal_scale(&wa, &wb);
  wa.sign = 0;
  wb.sign = 0;
  int compare = work_compare(wa, wb);

  if (compare != 0) {
    work_decimal wres = {0};
    work_decimal* bigger = (compare == 1) ? &wb : &wa;
    work_decimal* smaller = (compare == 1) ? &wa : &wb;
    work_sub(*bigger, *smaller, &wres);
    code = to_decimal(wres, res);
    if (compare == 1) res->bits[3] ^= SIGN;
  } else {
    reset_decimal(res);
    set_scale(res, wa.scale);
    set_sign(res, wa.sign);
  }
  return code;
}

int division_handler(work_decimal* wres, work_decimal dividend,
                     work_decimal remainder) {
  int code = OK;
  work_decimal fractional = *wres;
  work_decimal int_part = {0};

  while (!is_work_equal_zero(remainder) && fractional.scale < 28) {
    multiply_by_10(&remainder);
    binary_division(remainder, dividend, &int_part, &remainder);
    multiply_by_10(&fractional);
    work_add(fractional, int_part, &fractional);
    fractional.scale++;
  }

  *wres = fractional;

  work_decimal one = {0};
  one.bits[0] = 1;
  to_equal_scale(&dividend, &one);
  code = (work_compare(*wres, remainder) == 1) &&
         (work_compare(dividend, one) == 1);

  return code;
}

void work_add(work_decimal wa, work_decimal wb, work_decimal* wres) {
  unsigned long long buffer = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long product =
        ((unsigned long long)wa.bits[i] + (unsigned long long)wb.bits[i]) +
        buffer;
    wres->bits[i] = product & __UINT32_MAX__;
    buffer = product >> 32;
  }
  wres->scale = wa.scale;
  wres->sign = wa.sign;
}

void work_sub(work_decimal wa, work_decimal wb, work_decimal* wres) {
  unsigned long long borrow = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long diff = (unsigned long long)wa.bits[i] -
                              (unsigned long long)wb.bits[i] - borrow;
    if (diff > (unsigned long long)__UINT32_MAX__) {
      borrow = 1;
      diff += (unsigned long long)__UINT32_MAX__ + 1;
    } else {
      borrow = 0;
    }
    wres->bits[i] = diff & __UINT32_MAX__;
  }
  wres->scale = wa.scale;
  wres->sign = wa.sign;
}
