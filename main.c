// #include <stdio.h>
// #include "s21_helper.c"
#include "s21_decimal.h"

int main(){
    // int var = 0;
    // s21_set_sign(&var, 1);
    // s21_set_scale(&var, 10);
    // printf("sing: %d\n", s21_get_sign(var));
    // printf("scale: %d\n", s21_get_scale(var));
    // printf("number (10): %d\n", var);
    s21_big_decimal val1 = {4294967295, 4294967295, 4294967295, 0};
    s21_big_decimal val2 = {4294967295, 4294967295, 4294967295, 0};
    s21_big_decimal res = s21_get_zero_big_decimal();

    // res = s21_binary_add_light(val1, val2);
    // printf("add: %d\n", res.bits[0]);
    
    // res = s21_shift_left_light(res, 3);
    // printf("swith left (3): %d\n", res.bits[0]);

    // res = s21_increase_order_light(res);
    // printf("increase order: %d\n", res.bits[0]);
    printf("num_1: %d - %d\n", val1.bits[0], val1.bits[1]);
    printf("num_2: %d - %d\n", val2.bits[0], val2.bits[1]);

    res = s21_binary_mult_light(val1, val2);
    printf("mult: %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);
    
    // res = s21_shift_left_light(res, 3);
    // printf("swith left (3): %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

    // res = s21_increase_order_light(res);
    // printf("increase order: %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

    s21_print_b_decimal(val1);
    s21_print_b_decimal(val2);
    s21_print_b_decimal(res);

    return 0;
}