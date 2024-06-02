#include "s21_decimal.h"

/// @brief Сравнивает 2 числа типа work_decimal
/// @param wa
/// @param wb
/// @return -1 если wa больше, 1 если wb больше, 0 если равны
int work_compare(work_decimal wa, work_decimal wb) {
  int compare = 0;
  int is_zero1 = is_work_equal_zero(wa);
  int is_zero2 = is_work_equal_zero(wb);
  if (is_zero1 && is_zero2) {
    compare = 0;
  } else if (wa.sign != wb.sign) {
    compare = (wa.sign == MINUS) ? 1 : -1;
  } else {
    int i = 223;
    while (i >= 0 && compare == 0) {
      int wa_bit = get_bit(wa, i);
      int wb_bit = get_bit(wb, i);
      if (wa_bit != wb_bit) compare = (wb_bit) ? 1 : -1;
      i--;
    }
    if (wa.sign) compare *= -1;
  }

  return compare;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int status = 0;
  work_decimal wa = to_work_decimal(a);
  work_decimal wb = to_work_decimal(b);
  to_equal_scale(&wa, &wb);
  status = work_compare(wa, wb);
  return status == 0;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  int status = 0;
  work_decimal wa = to_work_decimal(a);
  work_decimal wb = to_work_decimal(b);
  to_equal_scale(&wa, &wb);
  status = work_compare(wa, wb);
  return status == 1;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int status = 0;
  work_decimal wa = to_work_decimal(a);
  work_decimal wb = to_work_decimal(b);
  to_equal_scale(&wa, &wb);
  status = work_compare(wa, wb);
  return status == -1;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_less(a, b) || s21_is_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_greater(a, b) || s21_is_equal(a, b);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}