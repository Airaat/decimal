#include "s21_decimal.h"

int get_bit(work_decimal num, int index) {
  const int shift = index % 32;
  const int word = index / 32;
  return (num.bits[word] >> shift) & 1;
}

void set_bit_dec(s21_decimal* num, int index, int bit) {
  const int shift = index % 32;
  const int word = index / 32;
  if (bit)
    num->bits[word] |= (1 << shift);
  else
    num->bits[word] &= ~(1 << shift);
}
void set_bit(work_decimal* num, int index, int bit) {
  const int shift = index % 32;
  const int word = index / 32;
  if (bit)
    num->bits[word] |= (1 << shift);
  else
    num->bits[word] &= ~(1 << shift);
}

int get_sign(s21_decimal a) { return (a.bits[3] & SIGN) >> 31; }

void set_sign(s21_decimal* a, int sign) {
  if (sign == MINUS)
    a->bits[3] |= SIGN;
  else
    a->bits[3] &= ~SIGN;
}

int get_scale(s21_decimal a) { return (a.bits[3] & SCALE) >> 16; }

void set_scale(s21_decimal* a, int scale) {
  a->bits[3] &= ~SCALE;
  a->bits[3] |= scale << 16;
}

int is_decimal_equal_zero(s21_decimal dec) {
  return (dec.bits[0] | dec.bits[1] | dec.bits[2]) == 0;
}

int is_work_equal_zero(work_decimal wdec) {
  unsigned result = 0;
  for (int i = 0; i < 7; i++) result |= wdec.bits[i];
  return result == 0;
}

unsigned get_work_mantissa(work_decimal wdec) {
  return (wdec.bits[6] | wdec.bits[5] | wdec.bits[4] | wdec.bits[3]);
}

void reset_decimal(s21_decimal* dec) {
  for (int i = 0; i < 4; i++) dec->bits[i] = 0;
}

int count_set_bits(s21_decimal dec) {
  int count = 0;
  for (int i = 2; i >= 0; i--) {
    while (dec.bits[i]) {
      dec.bits[i] &= (dec.bits[i] - 1);
      count++;
    }
  }
  return count;
}

void to_equal_scale(work_decimal* wa, work_decimal* wb) {
  int scale_a = wa->scale;
  int scale_b = wb->scale;
  int diff = abs(scale_a - scale_b);

  // Приводим к большему скейлу
  work_decimal* smaller_scale = (scale_a < scale_b) ? wa : wb;
  smaller_scale->scale += diff;
  while (diff) {
    multiply_by_10(smaller_scale);
    diff--;
  }
}

void multiply_by_10(work_decimal* wdec) {
  unsigned long long buffer = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long product =
        ((unsigned long long)wdec->bits[i] * 10) + buffer;
    wdec->bits[i] = product & __UINT32_MAX__;
    buffer = product >> 32;
  }
}

void bank_round(work_decimal* wdec, int remainder) {
  work_decimal one = {0};
  one.bits[0] = 1;
  int is_odd = get_bit(*wdec, 0);
  if (remainder == 5 && is_odd) {
    work_add(*wdec, one, wdec);
  } else if (remainder > 5) {
    work_add(*wdec, one, wdec);
  }
}

int divide_by_10(work_decimal* dec) {
  // Manipulate with mantissa
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned long long dividend =
        (unsigned long long)dec->bits[i] + (remainder << 32);
    dec->bits[i] = dividend / 10;
    remainder = dividend % 10;
  }

  return remainder;
}

/// @brief Делит число work_decimal до тех пор пока не влезет в децимал (или не
/// привысит скейл)
/// @param wdec
/// @return Остаток для дальнейшего банковского округления
int div_until_decimal(work_decimal* wdec) {
  unsigned work_mantissa = get_work_mantissa(*wdec);
  int remainder = 0;
  int temp = 0;
  while ((work_mantissa || wdec->scale > 28) && wdec->scale > 0) {
    remainder = divide_by_10(wdec);
    work_mantissa = get_work_mantissa(*wdec);
    if (work_mantissa) temp += remainder;
    wdec->scale--;
  }
  if (temp && remainder == 5) remainder++;
  return remainder;
}

int most_significant_bit(work_decimal dec) {
  int position = -1;
  int i = 223;
  while (position == -1 && i >= 0) {
    if (get_bit(dec, i)) position = i;
    i--;
  }

  return position;
}

work_decimal to_inverted(work_decimal dec) {
  work_decimal inverted_dec = {0};
  work_decimal one = {0};
  one.bits[0] = 1;
  for (int i = 0; i < 7; i++) dec.bits[i] = ~dec.bits[i];
  work_add(dec, one, &inverted_dec);
  return inverted_dec;
}