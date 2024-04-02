#include "s21_decimal.h"

int s21_get_sign(s21_decimal decimal) {
    control_bit ctrl_bit;
    ctrl_bit.integer = decimal.bits[3];
    return ctrl_bit.parts.sign;
}

int s21_get_scale(s21_decimal decimal) {
    control_bit ctrl_bit;
    ctrl_bit.integer = decimal.bits[3];
    return ctrl_bit.parts.scale;
}

void s21_set_sign(s21_decimal *decimal, int sign) {
    control_bit ctrl_bit;
    ctrl_bit.integer = decimal->bits[3];
    ctrl_bit.parts.sign = sign ? 1 : 0;
    decimal->bits[3] = ctrl_bit.integer;
}

void s21_decimal_set_power(s21_decimal *decimal, int scale) {
    control_bit ctrl_bit;
    ctrl_bit.integer = decimal->bits[3];
    ctrl_bit.parts.scale = scale;

    decimal->bits[3] = ctrl_bit.integer;
}

//проверяет четность мантиссы (не всего числа)
int s21_mantissa_even(s21_decimal value) {
    return (value.bits[0] & 1) != 1;
}