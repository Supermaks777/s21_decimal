#include "s21_decimal.h"

/**
 * @brief Функция определяет знак по контрольному int
 * @param check_value контрольный int (3й для decimal, 7й для big_decimal)
 * @return искомый знак (1 - положительный; 0 - отрицательный)
 */
int s21_get_sign(int checkable_value) {
    control_bit ctrl_bit;
    ctrl_bit.integer = checkable_value;
    return ctrl_bit.parts.sign;
}

/**
 * @brief Функция определяет масштаб числа по контрольному int
 * @param check_value контрольный int (3й для decimal, 7й для big_decimal)
 * @return искомый масштаб (степень десятки в знаменателе числа)
 */
int s21_get_scale(int checkable_value) {
    control_bit ctrl_bit;
    ctrl_bit.integer = checkable_value;
    return ctrl_bit.parts.scale;
}

/**
 * @brief Процедура устанавливает знак контрольному int
 * @param mutable_value указатель на контрольный int (3й для decimal, 7й для big_decimal)
 * @param sign необходимый знак  (1 - положительный; 0 - отрицательный)
 */
void s21_set_sign(int *mutable_value, int sign) {
    control_bit ctrl_bit;
    ctrl_bit.integer = *mutable_value;
    ctrl_bit.parts.sign = sign ? 1 : 0;
    *mutable_value = ctrl_bit.integer;
}

/**
 * @brief Процедура устанавливает масштаб контрольному int
 * @param mutable_value указатель на контрольный int (3й для decimal, 7й для big_decimal)
 * @param sign необходимый масштаб 
 */
void s21_set_scale(int *mutable_value, int scale) {
    control_bit ctrl_bit;
    ctrl_bit.integer = *mutable_value;
    ctrl_bit.parts.scale = scale;
    *mutable_value = ctrl_bit.integer;
}

/**
 * @brief Функция проверяет четность мантисы
 * @param check_value младший бит числа (нулевой int)
 * @return четность числа (1 - четное; 0 - нечетное)
 */
int s21_mantissa_even(int check_value) {
    return (check_value & 1) != 1;
}

// int s21_get_sign(s21_decimal decimal) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal.bits[3];
//     return ctrl_bit.parts.sign;
// }

// int s21_get_scale(s21_decimal decimal) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal.bits[3];
//     return ctrl_bit.parts.scale;
// }

// void s21_set_sign(s21_decimal *decimal, int sign) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal->bits[3];
//     ctrl_bit.parts.sign = sign ? 1 : 0;
//     decimal->bits[3] = ctrl_bit.integer;
// }

// void s21_decimal_set_power(s21_decimal *decimal, int scale) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal->bits[3];
//     ctrl_bit.parts.scale = scale;
//     decimal->bits[3] = ctrl_bit.integer;
// }

// //проверяет четность мантиссы (не всего числа)
// int s21_mantissa_even(s21_decimal value) {
//     return (value.bits[0] & 1) != 1;
// }