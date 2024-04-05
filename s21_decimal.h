#ifndef SRC_S21_DECIMAL_TYPES_H_
#define SRC_S21_DECIMAL_TYPES_H_

#include <stdint.h>
#include <stdio.h>

#define BIG_DECIMAL_SIZE 8
#define DECIMAL_SIZE 8

//0-2 int мантисса, 3й - контрольный
typedef struct s21_decimal {
    int bits[4];
} s21_decimal;

//структура для контольного бита
typedef union control_bit {
    int integer;
    struct {
        uint32_t empty2 : 16;
        uint32_t scale : 8;
        uint32_t empty1 : 7;
        uint32_t sign : 1;
    } parts;
} control_bit;

typedef struct s21_big_decimal {
    unsigned bits[8];
} s21_big_decimal;

int s21_get_sign(int checkable_value);
int s21_get_scale(int checkable_value) ;
void s21_set_sign(int *mutable_value, int sign) ;
void s21_set_scale(int *mutable_value, int scale);
int s21_mantissa_even(int check_value) ;
void s21_convert_to_big_decimal(s21_decimal source, s21_big_decimal * result);
void s21_clear_big_decimal(s21_big_decimal *source) ;
void s21_clear_decimal(s21_decimal *source);
int s21_get_bit(int source, int index);
void s21_set_bit(int *source, int index) ;
void s21_set_no_bit(int *source, int index) ;




int s21_shift_left(s21_big_decimal *num, int shift_value) ;

int s21_binary_add(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal * result);

s21_big_decimal s21_get_zero_big_decimal();

s21_big_decimal s21_shift_left_light(s21_big_decimal num, int shift_value);
s21_big_decimal s21_increase_order_light(s21_big_decimal num) ;

s21_big_decimal s21_binary_add_light(s21_big_decimal value_1, s21_big_decimal value_2);

s21_big_decimal s21_convert_to_big_decimal_light(s21_decimal source);
void s21_convert_to_big_decimal(s21_decimal source, s21_big_decimal * result);
s21_big_decimal s21_binary_mult_light(s21_big_decimal value_1, s21_big_decimal value_2);

void s21_print_binary(int source);
void s21_print_b_decimal(s21_big_decimal source) ;


#endif  //  SRC_S21_DECIMAL_TYPES_H_