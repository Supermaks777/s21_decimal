#ifndef SRC_S21_DECIMAL_TYPES_H_
#define SRC_S21_DECIMAL_TYPES_H_

#include <stdint.h>

typedef struct s21_decimal {
    int bits[4];
} s21_decimal;

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
    int bits[8];
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






int s21_binary_add(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal * result);








#endif  //  SRC_S21_DECIMAL_TYPES_H_