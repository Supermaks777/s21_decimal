#include "s21_decimal.h"

/**
 * @brief Функция делает бинарное сложение двух чисел (без проверок)
 * @param term_1 первое слагаемое (s21_big_decimal)
 * @param term_2 второе слагаемое (s21_big_decimal)
 * @return сумма (s21_big_decimal)
 */
s21_big_decimal s21_binary_add(s21_big_decimal term_1, s21_big_decimal term_2){
    s21_big_decimal result = s21_get_zero_big_decimal();
    int overflow = 0;
    int summa = 0; 
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            summa = s21_get_bit(term_1.bits[i], j) + s21_get_bit(term_2.bits[i], j) + overflow;
            if (summa % 2) s21_set_bit(&result.bits[i], j);
            overflow = summa / 2;

        }
    }
    return result;
}

/**
 * @brief Функция делает бинарное вычитание двух чисел без проверок
 * @param minuend уменьшаемое (s21_big_decimal)
 * @param subtrahend вычитаемое (s21_big_decimal)
 * @return разность (s21_big_decimal)
 */
s21_big_decimal s21_binary_sub(s21_big_decimal minuend, s21_big_decimal subtrahend){
    s21_big_decimal result = s21_get_zero_big_decimal();
    int deficit = 0;
    int summa = 0; 
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            summa = s21_get_bit(minuend.bits[i], j) - s21_get_bit(subtrahend.bits[i], j) - deficit;
            if (!!(summa % 2)) s21_set_bit(&result.bits[i], j);
            deficit = !!(summa < 0);
        }
    }
    return result;
}

/**
 * @brief Функция делает бинарное умножение двух чисел без проверок
 * @param factor_1 первый множитель (s21_big_decimal)
 * @param factor_2 второй множитель (s21_big_decimal)
 * @return произведение (s21_big_decimal)
 */
s21_big_decimal s21_binary_mult(s21_big_decimal factor_1, s21_big_decimal factor_2){
    s21_big_decimal result = s21_get_zero_big_decimal();
    s21_big_decimal temp = factor_1;
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        for(int j = 0; j < 32; j++) {
            if (s21_get_bit(factor_2.bits[i], j)) result = s21_binary_add(result, temp);
            temp = s21_shift_left(temp, 1);
        }
    }
    return result;
}

/**
 * @brief Функция делает бинарное деление двух чисел и возвращает его по ссылке при условии целочисленного деления
 * @param dividend делимое (s21_big_decimal)
 * @param divisor делитель (s21_big_decimal)
 * @param result ссылка на результат (s21_big_decimal)
 * @return частное (s21_big_decimal)
 */
s21_big_decimal s21_binary_div(s21_big_decimal dividend, s21_big_decimal divisor, s21_big_decimal * remainder){
    s21_big_decimal result = s21_get_zero_big_decimal();
    s21_big_decimal temp = dividend;
    s21_big_decimal subtrahend;
    int shift_value;
    shift_value = s21_get_highest_bit(dividend) - s21_get_highest_bit(divisor);
    subtrahend = s21_shift_left(divisor, shift_value);
    for (int i = shift_value; i >= 0; i--) {
        result = s21_shift_left(result, 1);
        if (!(s21_binary_compare(temp, subtrahend) == -1)){
            s21_set_bit(&result.bits[0], 0);
            temp = s21_binary_sub(temp, subtrahend);  
        };
        subtrahend = s21_shift_right(subtrahend, 1);
    };
    if (remainder != NULL) *remainder = temp;
    return result;
}
