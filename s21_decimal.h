#ifndef SRC_S21_DECIMAL_TYPES_H_
#define SRC_S21_DECIMAL_TYPES_H_

#include <stdint.h>
#include <stdio.h>

#define BIG_DECIMAL_SIZE 8
#define DECIMAL_SIZE 8
#define INT_SIZE 32

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

/**
 * @brief коды ошибок арифметических операторов
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
typedef enum s21_error_code {
    S21_ARITHMETIC_OK = 0,
    S21_ARITHMETIC_BIG = 1,
    S21_ARITHMETIC_SMALL = 2,
    S21_ARITHMETIC_ZERO_DIV = 3,
    S21_ARITHMETIC_ERROR = 4
} s21_error_code;

//binary
s21_big_decimal s21_binary_add(s21_big_decimal term_1, s21_big_decimal term_2);
s21_big_decimal s21_binary_sub(s21_big_decimal minuend, s21_big_decimal subtrahend);
s21_big_decimal s21_binary_mult(s21_big_decimal factor_1, s21_big_decimal factor_2);
s21_big_decimal s21_binary_div(s21_big_decimal dividend, s21_big_decimal divisor, s21_big_decimal * remainder);

//helper
int s21_get_sign(int checkable_value);
int s21_get_scale(int checkable_value);
void s21_set_sign(int *mutable_value, int sign);
void s21_set_scale(int *mutable_value, int scale);
void s21_convert_to_big_decimal(s21_decimal source, s21_big_decimal * result);
s21_big_decimal s21_convert_to_big_decimal_light(s21_decimal source);
void s21_clear_big_decimal(s21_big_decimal *source);
void s21_clear_decimal(s21_decimal *source);
int s21_get_bit(int source, int index);
void s21_set_bit(int *source, int index);
void s21_set_no_bit(int *source, int index);
s21_big_decimal s21_get_zero_big_decimal();
s21_big_decimal s21_shift_left_into_integer(s21_big_decimal num, int shift_value);
int s21_bit_compare(int check_value, int reference);
s21_big_decimal s21_shift_left(s21_big_decimal num, int shift_value);
s21_big_decimal s21_shift_right_into_integer(s21_big_decimal num, int shift_value);
s21_big_decimal s21_shift_right(s21_big_decimal num, int shift_value);
int s21_get_highest_bit(s21_big_decimal source);
int s21_binary_compare(s21_big_decimal check_value, s21_big_decimal reference);
s21_big_decimal s21_increase_order_light(s21_big_decimal num);
int s21_mantissa_even(int check_value);
void s21_print_binary(unsigned source);
void s21_print_big_decimal(s21_big_decimal source);
void s21_print_b_decimal_10(s21_big_decimal source);


void s21_standartization_(s21_decimal * source);
int s21_is_divisible_by_10(s21_decimal source);
void s21_normalization(s21_decimal source_1, s21_decimal source_2, s21_big_decimal * result_1, s21_big_decimal * result_2, int * scale_result);
int s21_max(int val_1, int val_2);
s21_big_decimal s21_scaling_up(s21_decimal source, int scale_up);
int is_null_decimal(s21_decimal source);
int s21_is_correct_decimal(s21_decimal source);





#endif  //  SRC_S21_DECIMAL_TYPES_H_