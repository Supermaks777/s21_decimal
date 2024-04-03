#include <stdio.h>
// #include "s21_helper.c"
#include "s21_decimal.h"

int main(){
    int var = 0;
    s21_set_sign(&var, 1);
    s21_set_scale(&var, 10);
    printf("sing: %d\n", s21_get_sign(var));
    printf("scale: %d\n", s21_get_scale(var));
    printf("number (10): %d\n", var);
    return 0;
}