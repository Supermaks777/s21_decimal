#include <stdio.h>
// #include "s21_helper.c"
#include "s21_decimal.h"

int main(){
    // int var = 0;
    // s21_set_sign(&var, 1);
    // s21_set_scale(&var, 10);
    // printf("sing: %d\n", s21_get_sign(var));
    // printf("scale: %d\n", s21_get_scale(var));
    // printf("number (10): %d\n", var);
    s21_big_decimal val1;
    s21_big_decimal val2;
    s21_big_decimal res;
    s21_clear_big_decimal(&val1);
    s21_clear_big_decimal(&val2);
    s21_clear_big_decimal(&res);
    val1.bits[0] = 5;
    val2.bits[0] = 7;
    s21_binary_add(val1, val2, &res);
    printf("result: %d\n", res.bits[0]);
    return 0;
}