#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
//проверяю корректность исходных данных
    s21_error_code err_code = S21_ARITHMETIC_OK;
    if (!result) err_code = S21_ARITHMETIC_ERROR;
    else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) err_code = S21_ARITHMETIC_ERROR;

//обрабатываю случай, если один из них равен нулю
    else if (is_null_decimal(value_1)) *result = value_2;
    else if (is_null_decimal(value_2)) *result = value_1;

///дальше функция
    else {
        s21_big_decimal big_val_1 = s21_get_zero_big_decimal();
        s21_big_decimal big_val_2 = s21_get_zero_big_decimal();
        s21_big_decimal big_result;
        int sign_1 = s21_get_sign(value_1.bits[3]);
        int sign_2 = s21_get_sign(value_2.bits[3]);
        int scale_result;
        int sign_result;
        s21_normalization(value_1, value_2, &big_val_1, &big_val_2, &scale_result);
        int compare_result = s21_binary_compare(big_val_1, big_val_2);
        if (sign_1 == sign_2) {
            big_result = s21_binary_add(big_val_1, big_val_2);
            sign_result = sign_1;
        } else if (compare_result == 0){
            big_result = s21_get_zero_big_decimal();
            sign_result = sign_1;
        } else if (compare_result == 1){
            big_result = s21_binary_sub(big_val_1, big_val_2);
            sign_result = sign_1;
        } else if (compare_result == -1){
            big_result = s21_binary_sub(big_val_2, big_val_1);
            sign_result = sign_2;
        }

//тут нужно добавить конвертацию в decimal   

    }
    return err_code;
}


int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
//проверяю корректность исходных данных
    s21_error_code err_code = S21_ARITHMETIC_OK;
    if (!result) err_code = S21_ARITHMETIC_ERROR;
    else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) err_code = S21_ARITHMETIC_ERROR;

//обрабатываю случай, если один из них равен нулю
    else if (is_null_decimal(value_1)) *result = value_2;
    else if (is_null_decimal(value_2)) *result = value_1;

///дальше функция
    else {
        s21_big_decimal big_val_1 = s21_get_zero_big_decimal();
        s21_big_decimal big_val_2 = s21_get_zero_big_decimal();
        s21_big_decimal big_result;
        int sign_1 = s21_get_sign(value_1.bits[3]);
        int sign_2 = s21_get_sign(value_2.bits[3]);
        int scale_result;
        s21_normalization(value_1, value_2, &big_val_1, &big_val_2, &scale_result);
        if (sign_1 != sign_2) big_result = s21_binary_add(big_val_1, big_val_2);
        else big_result = (s21_binary_compare(big_val_1, big_val_2) == 1) ? s21_binary_sub(big_val_1, big_val_2) : s21_binary_sub(big_val_2, big_val_1);

//тут нужно добавить конвертацию в decimal   

    }
    return err_code;

}