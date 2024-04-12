
#include "s21_decimal.h"



int main(){
    s21_big_decimal val1 = {317677687, 0, 0, 0, 0, 0, 0, 0};
    s21_big_decimal val2 = {3276, 0, 0, 0, 0, 0, 0, 0};
    s21_big_decimal res = s21_get_zero_big_decimal();
    s21_big_decimal remainder = s21_get_zero_big_decimal();

    printf("\nnum_1: %u - %u - %u - %u", val1.bits[0], val1.bits[1], val1.bits[2], val1.bits[3]);
    printf("\nnum_2: %u - %u - %u - %u", val2.bits[0], val2.bits[1], val2.bits[2], val2.bits[3]);
    printf("\ncmp: %d",s21_binary_compare(val1, val2));

    res = s21_binary_div(val1, val2, &remainder);
    // res = s21_binary_sub_light(val1, val2);
    printf("\nresult: %u - %u - %u - %u", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);
    printf("\nremainder: %u - %u - %u - %u", remainder.bits[0], remainder.bits[1], remainder.bits[2], remainder.bits[3]);
    
    // res = s21_shift_left_light(res, 3);
    // printf("swith left (3): %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

    // res = s21_increase_order_light(res);
    // printf("increase order: %d - %d - %d - %d\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

    // s21_print_big_decimal(val1);
    // s21_print_big_decimal(val2);
    // s21_print_big_decimal(res);
    // printf("%d\n", s21_get_highest_bit(val1));
    // printf("%d\n", s21_get_highest_bit(val2));

    return 0;
}

