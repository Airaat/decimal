#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define PLUS 0
#define MINUS 1
#define SCALE 0xff0000
#define SIGN 0x80000000
#define MAX_DECIMAL 79228162514264337593543950335.0f

// Decimal Representation
/*
S - sign (0 - positive, 1 - negative)
X = {0, 1}
S.......XXXXXXXX................-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

MAX_DECIMAL: 79_228_162_514_264_337_593_543_950_335
szzzzzzz00000000zzzzzzzzzzzzzzzz-11111111111111111111111111111111-11111111111111111111111111111111-11111111111111111111111111111111
*/

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[7];
  int sign;
  int scale;
} work_decimal;

enum status_code { OK, TOO_BIG, TOO_SMALL, DIV_ZERO };

/*============ARITHMETIC==============*/
int s21_add(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_div(s21_decimal a, s21_decimal b, s21_decimal *res);
/*============COMPARISON==============*/
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
/*============CONVERTORS==============*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
/*============CONVERTORS==============*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
/*============HELPERS==============*/
int get_sign(s21_decimal a);
int get_scale(s21_decimal a);
int get_bit(work_decimal num, int index);
unsigned get_work_mantissa(work_decimal wdec);

void set_sign(s21_decimal *a, int sign);
void set_scale(s21_decimal *a, int scale);
void set_bit(work_decimal *num, int index, int bit);
void set_bit_dec(s21_decimal *num, int index, int bit);

work_decimal to_work_decimal(s21_decimal dec);
int to_decimal(work_decimal wdec, s21_decimal *dec);
void multiply_by_10(work_decimal *wdec);
int divide_by_10(work_decimal *dec);
int div_until_decimal(work_decimal *wdec);
void bank_round(work_decimal *wdec, int remainder);
void to_equal_scale(work_decimal *wa, work_decimal *wb);
void reset_decimal(s21_decimal *dec);
int is_decimal_equal_zero(s21_decimal dec);
int is_work_equal_zero(work_decimal dec);
int count_set_bits(s21_decimal dec);
int most_significant_bit(work_decimal dec);
work_decimal to_inverted(work_decimal dec);
int addition_handler(s21_decimal wa, s21_decimal wb, s21_decimal *res);
int subtraction_handler(s21_decimal wa, s21_decimal wb, s21_decimal *res);
int division_handler(work_decimal *wres, work_decimal dividend,
                     work_decimal remainder);
void work_add(work_decimal wa, work_decimal wb, work_decimal *wres);
void work_sub(work_decimal wa, work_decimal wb, work_decimal *wres);
int work_compare(work_decimal wa, work_decimal wb);
void binary_division(work_decimal wa, work_decimal wb, work_decimal *quotient,
                     work_decimal *remainder);
work_decimal binary_shift_left(work_decimal dec, int shift);
work_decimal binary_shift_right(work_decimal dec, int shift);

#endif