// #include <stdio.h>
// #include "s21_helper.c"
#include "s21_decimal.h"

// int main(){
//     // int var = 0;
//     // s21_set_sign(&var, 1);
//     // s21_set_scale(&var, 10);
//     // printf("sing: %d\n", s21_get_sign(var));
//     // printf("scale: %d\n", s21_get_scale(var));
//     // printf("number (10): %d\n", var);
//     s21_big_decimal val1 = {500, 0, 0, 0};
//     s21_big_decimal val2 = {319, 0, 0, 0};
//     s21_big_decimal res = s21_get_zero_big_decimal();

//     printf("num_1: %d - %d - %d - %d\n", val1.bits[0], val1.bits[1], val1.bits[2], val1.bits[3]);
//     printf("num_2: %d - %d - %d - %d\n", val2.bits[0], val2.bits[1], val2.bits[2], val2.bits[3]);

//     res = s21_binary_sub_light(val1, val2);
//     printf("result: %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);
    
//     // res = s21_shift_left_light(res, 3);
//     // printf("swith left (3): %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

//     // res = s21_increase_order_light(res);
//     // printf("increase order: %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

//     s21_print_big_decimal(val1);
//     s21_print_big_decimal(val2);
//     s21_print_big_decimal(res);

//     return 0;
// }

void binary_division(int dividend, int divisor) {
    int quotient = 0;
    int remainder = 0;
    
    for (int bit = 31; bit >= 0; bit--) {
        remainder = (remainder << 1) | ((dividend >> bit) & 1);
        if (remainder >= divisor) {
            quotient = (quotient << 1) | 1;
            remainder -= divisor;
        } else {
            quotient = quotient << 1;
        }
    }

    printf("Quotient: %d\n", quotient);
    printf("Remainder: %d\n", remainder);
}

int main() {
    int dividend = 516;  // Делимое
    int divisor = 100;    // Делитель

    binary_division(dividend, divisor);

    return 0;
}