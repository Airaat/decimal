#include "s21_decimal.h"
#define OK 0
#define FAIL 1

s21_decimal abs_decimal(s21_decimal num, int sign) {
  s21_decimal num1 = num;
  num1.bits[3] = (num1.bits[3] & ~(1 << 31)) | (sign << 31);
  return num1;
}

int is_correct(s21_decimal value) {
  unsigned int bits = value.bits[3];
  for (int i = 0; i <= 15; ++i) {
    if ((bits & (1 << i)) != 0) {
      return 1;
    }
  }

  for (int i = 24; i <= 30; ++i) {
    if ((bits & (1 << i)) != 0) {
      return 1;
    }
  }

  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = OK;

  if (!result) {
    status = FAIL;
  } else {
    int sign = get_sign(value);
    *result = abs_decimal(value, !sign);  // проверка скейл зачем
    if (get_scale(value) < 0 || get_scale(value) > 28 || is_correct(value)) {
      status = FAIL;
    }
  }
  return status;
}

int s21_truncate(s21_decimal dec, s21_decimal *res) {
  int status = OK;
  if (!res) {
    status = FAIL;
  } else {
    reset_decimal(res);
    work_decimal wdec = to_work_decimal(dec);
    for (; wdec.scale > 0; wdec.scale--) divide_by_10(&wdec);
    to_decimal(wdec, res);
  }

  return status;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int exp = (value.bits[3] >> 16) & 0x00ff;
  if (exp != 0) {
    s21_decimal one = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};
    bool sign = (value.bits[3] >> 31) & 1;
    s21_truncate(value, result);
    if (sign && (exp != 0)) s21_sub(*result, one, result);
  } else
    *result = value;
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = OK;
  s21_decimal a = {{0}};

  if (!result) {
    status = FAIL;
  } else if (is_correct(value) == 1) {
    status = FAIL;
    *result = a;
  } else {
    *result = a;
    int sign = get_sign(value);

    s21_decimal without_sign = abs_decimal(value, 0);

    s21_decimal without_whole;
    s21_decimal whole_without_sign1;

    s21_truncate(without_sign, &whole_without_sign1);
    s21_sub(without_sign, whole_without_sign1, &without_whole);

    float ostatok;
    work_decimal whole_without_sign2 = to_work_decimal(whole_without_sign1);
    s21_from_decimal_to_float(without_whole, &ostatok);

    bank_round(&whole_without_sign2, (int)(ostatok * 10));

    s21_decimal res;
    to_decimal(whole_without_sign2, &res);
    *result = abs_decimal(res, sign);
  }
  return status;
}
