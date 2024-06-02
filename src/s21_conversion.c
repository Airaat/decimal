#include "s21_decimal.h"
#define CONVERSION_OK 0
#define CONVERSION_ERROR 1

work_decimal to_work_decimal(s21_decimal dec) {
  work_decimal wdec = {0};
  wdec.sign = get_sign(dec);
  wdec.scale = get_scale(dec);
  for (int i = 0; i < 3; i++) wdec.bits[i] = dec.bits[i];
  return wdec;
}

int to_decimal(work_decimal wdec, s21_decimal *dec) {
  int code = OK;
  int remainder = div_until_decimal(&wdec);
  bank_round(&wdec, remainder);
  unsigned work_mantissa = get_work_mantissa(wdec);
  if (work_mantissa || wdec.scale < 0) code = TOO_BIG;
  for (int i = 0; i < 3; i++) dec->bits[i] = wdec.bits[i];

  set_scale(dec, wdec.scale);
  set_sign(dec, wdec.sign);

  return code;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = CONVERSION_ERROR;
  if (dst) {
    int sign = (src < 0);
    reset_decimal(dst);
    dst->bits[0] = abs(src);
    set_sign(dst, sign);
    status = CONVERSION_OK;
  }
  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = CONVERSION_ERROR;
  if (dst) {
    int sign = (get_sign(src)) ? -1 : 1;

    work_decimal wdec = to_work_decimal(src);
    while (wdec.scale) {
      divide_by_10(&wdec);
      wdec.scale--;
    }

    reset_decimal(&src);
    to_decimal(wdec, &src);

    if ((src.bits[2] | src.bits[1]) != 0 || src.bits[0] > INT32_MAX) {
      status = CONVERSION_ERROR;
    } else {
      *dst = (int)src.bits[0] * sign;
      status = CONVERSION_OK;
    }
  }

  return status;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = CONVERSION_OK;
  int sign = (src < 0);
  int scale = 0;
  src = fabs(src);

  if (!dst || isnan(src) || isinf(src) || (src > 0 && src < 1e-28) ||
      src > MAX_DECIMAL) {
    result = CONVERSION_ERROR;
  } else {
    reset_decimal(dst);
    int int_part = (int)src;

    while (src - ((float)int_part / (int)(pow(10, scale))) != 0) {
      scale++;
      int_part = src * (int)(pow(10, scale));
    }

    s21_from_int_to_decimal(int_part, dst);
    set_sign(dst, sign);
    set_scale(dst, scale);
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = CONVERSION_ERROR;
  if (dst) {
    int scale = get_scale(src);
    int sign = get_sign(src) ? -1 : 1;
    double result = 0;
    work_decimal wdec = to_work_decimal(src);
    for (int i = 0; i < 96; i++) {
      if (get_bit(wdec, i)) result += pow(2.0, i);
    }

    result /= pow(10.0, scale);
    result *= sign;
    *dst = (float)result;
    status = CONVERSION_OK;
  }

  return status;
}
