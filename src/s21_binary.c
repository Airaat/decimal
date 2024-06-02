#include "s21_decimal.h"

void binary_division(work_decimal wa, work_decimal wb, work_decimal* quotient,
                     work_decimal* remainder) {
  for (int i = 0; i < 7; i++) quotient->bits[i] = 0;
  *remainder = wa;
  if (work_compare(wa, wb) < 1) {
    int msb_a = most_significant_bit(wa);
    int msb_b = most_significant_bit(wb);
    int shift = msb_a - msb_b;

    wb = binary_shift_left(wb, shift);
    work_decimal minus_wb = to_inverted(wb);
    work_add(*remainder, minus_wb, remainder);
    int tech_bit = 0;

    for (int i = 0; i < shift; i++) {
      *remainder = binary_shift_left(*remainder, 1);

      tech_bit = remainder->bits[6] >> 31;
      *quotient = binary_shift_left(*quotient, 1);
      set_bit(quotient, 0, !tech_bit);

      if (tech_bit) {
        work_add(*remainder, wb, remainder);
      } else {
        work_add(*remainder, minus_wb, remainder);
      }
    }
    tech_bit = remainder->bits[6] >> 31;

    *quotient = binary_shift_left(*quotient, 1);
    set_bit(quotient, 0, !tech_bit);
    if (tech_bit) work_add(*remainder, wb, remainder);
    *remainder = binary_shift_right(*remainder, shift);
  }
}

work_decimal binary_shift_left(work_decimal dec, int shift) {
  // Нормализуем
  shift %= 223;

  int shift_words = shift / 32;
  int shift_bits = shift % 32;

  // Сдвигаем биты на целое количество слов
  for (int i = 6; i >= shift_words; i--) {
    dec.bits[i] = dec.bits[i - shift_words];
  }

  // Обнуляем биты в начале результата
  for (int i = 0; i < shift_words; i++) dec.bits[i] = 0;

  // Выполняем сдвиг оставшихся бит в последнем слове
  if (shift_bits > 0) {
    for (int i = 6; i >= shift_words + 1; i--) {
      dec.bits[i] =
          (dec.bits[i] << shift_bits) | (dec.bits[i - 1] >> (32 - shift_bits));
    }
    dec.bits[shift_words] <<= shift_bits;
  }

  return dec;
}

work_decimal binary_shift_right(work_decimal dec, int shift) {
  // Нормализуем сдвиг
  shift %= 223;

  int shift_words = shift / 32;
  int shift_bits = shift % 32;

  // Сдвигаем биты на целое количество слов
  for (int i = 0; i <= 6 - shift_words; i++) {
    dec.bits[i] = dec.bits[i + shift_words];
  }

  // Обнуляем биты в конце результата
  for (int i = 6 - shift_words + 1; i <= 6; i++) {
    dec.bits[i] = 0;
  }

  // Выполняем сдвиг оставшихся бит в последнем слове
  if (shift_bits > 0) {
    for (int i = 0; i < 6 - shift_words; i++) {
      dec.bits[i] =
          (dec.bits[i] >> shift_bits) | (dec.bits[i + 1] << (32 - shift_bits));
    }
    dec.bits[6 - shift_words] >>= shift_bits;
  }

  return dec;
}