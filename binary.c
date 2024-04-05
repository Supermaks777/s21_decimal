#include "s21_decimal.h"

/**
 * @brief Функция делает бинарное сложение двух чисел
 * @param value_1 первое слагаемое (s21_big_decimal)
 * @param value_2 второе слагаемое (s21_big_decimal)
 * @param result указатель на результат (s21_big_decimal)
 * @return результат операции: 0 - все ОК, 1 - переполнение
 */
int s21_binary_add(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal * result){
    int overflow = 0;
    int summa = 0; 
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            summa = s21_get_bit(value_1.bits[i], j) + s21_get_bit(value_2.bits[i], j) + overflow;
            if (summa % 2) s21_set_bit(&result->bits[i], j);
            // printf("%d + %d = %d value %d overflow %d\n", s21_get_bit(value_1.bits[i], j), s21_get_bit(value_2.bits[i], j), summa, summa % 2, summa / 2);
            overflow = summa / 2;

        }
    }
    return overflow;
}

/**
 * @brief Функция делает бинарное сложение двух чисел (без проверок)
 * @param value_1 первое слагаемое (s21_big_decimal)
 * @param value_2 второе слагаемое (s21_big_decimal)
 * @return сумма (s21_big_decimal)
 */
s21_big_decimal s21_binary_add_light(s21_big_decimal value_1, s21_big_decimal value_2){
    s21_big_decimal result = s21_get_zero_big_decimal();
    int overflow = 0;
    int summa = 0; 
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            summa = s21_get_bit(value_1.bits[i], j) + s21_get_bit(value_2.bits[i], j) + overflow;
            if (summa % 2) s21_set_bit(&result.bits[i], j);
            // printf("%d + %d = %d value %d overflow %d\n", s21_get_bit(value_1.bits[i], j), s21_get_bit(value_2.bits[i], j), summa, summa % 2, summa / 2);
            overflow = summa / 2;

        }
    }
    return result;
}

/**
 * @brief Функция делает бинарное вычитание двух чисел без проверок
 * @param value_1 уменьшаемое (s21_big_decimal)
 * @param value_2 вычитаемое (s21_big_decimal)
 * @return разность (s21_big_decimal)
 */
s21_big_decimal s21_binary_sub_light(s21_big_decimal value_1, s21_big_decimal value_2){
    s21_big_decimal result = s21_get_zero_big_decimal();
    int overflow = 0;
    int summa = 0; 
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            summa = s21_get_bit(value_1.bits[i], j) + s21_get_bit(value_2.bits[i], j) + overflow;
            if (summa % 2) s21_set_bit(&result.bits[i], j);
            // printf("%d + %d = %d value %d overflow %d\n", s21_get_bit(value_1.bits[i], j), s21_get_bit(value_2.bits[i], j), summa, summa % 2, summa / 2);
            overflow = summa / 2;

        }
    }
    return result;
}

/**
 * @brief Функция делает бинарное умножение двух чисел без проверок
 * @param value_1 первый множитель (s21_big_decimal)
 * @param value_2 второй множитель (s21_big_decimal)
 * @return произведение (s21_big_decimal)
 */
s21_big_decimal s21_binary_mult_light(s21_big_decimal value_1, s21_big_decimal value_2){
    s21_big_decimal result = s21_get_zero_big_decimal();
    s21_big_decimal temp = value_1;
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            if (s21_get_bit(value_2.bits[i], j)) result = s21_binary_add_light(result, temp);
            temp = s21_shift_left_light(temp, 1);
        }
    }
    return result;
}

