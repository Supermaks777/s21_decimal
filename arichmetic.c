#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
///в самом начале нужно прописать на равенство одного из слагаемых нулю. затем уже этот текст
    s21_big_decimal big_val_1 = s21_get_zero_big_decimal();
    s21_big_decimal big_val_2 = s21_get_zero_big_decimal();
    s21_big_decimal big_result;
    int sign_1 = s21_get_sign(value_1.bits[3]);
    int sign_2 = s21_get_sign(value_2.bits[3]);
    int scale_result;
    s21_normalization(value_1, value_2, &big_val_1, &big_val_2, &scale_result);
    if (sign_1 == sign_2) big_result = s21_binary_add(big_val_1, big_val_2);
    else big_result = (s21_binary_compare(big_val_1, big_val_2) == 1) ? s21_binary_sub(big_val_1, big_val_2) : s21_binary_sub(big_val_2, big_val_1);
//тут нужно добавить конвертацию в decimal   
}