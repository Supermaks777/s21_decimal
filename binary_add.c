#include "s21_decimal.h"

int s21_binary_add(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal * result){
    int overflow = 0;
    int summa = 0; 
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 32; j++) {
            summa = s21_get_bit(value_1.bits[i], j) + s21_get_bit(value_2.bits[i], j) + overflow;
            if (summa % 2) s21_set_bit(&result->bits[j], j);
            else s21_set_no_bit(&result->bits[j], j);
            overflow = summa / 2;
        }
    }
    return overflow;

}