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









#endif  //  SRC_S21_DECIMAL_TYPES_H_