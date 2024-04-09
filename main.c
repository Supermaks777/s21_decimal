
// #include "s21_decimal.h"

// int main(){
//     // int var = 0;
//     // s21_set_sign(&var, 1);
//     // s21_set_scale(&var, 10);
//     // printf("sing: %d\n", s21_get_sign(var));
//     // printf("scale: %d\n", s21_get_scale(var));
//     // printf("number (10): %d\n", var);
//     s21_big_decimal val1 = {0, 1, 0, 0};
//     s21_big_decimal val2 = {2, 0, 0, 0};
//     s21_big_decimal res = s21_get_zero_big_decimal();

//     printf("num_1: %u - %u - %u - %u\n", val1.bits[0], val1.bits[1], val1.bits[2], val1.bits[3]);
//     printf("num_2: %u - %u - %u - %u\n", val2.bits[0], val2.bits[1], val2.bits[2], val2.bits[3]);

//     res = s21_binary_sub_light(val1, val2);
//     printf("result: %u - %u - %u - %u\n", res.bits[0], res.bits[1], res.bits[2], res.bits[3]);
    
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

    printf("Quotient: %u\n", quotient);
    printf("Remainder: %u\n", remainder);
}

int main() {
    int dividend = 516;  // Делимое
    int divisor = 100;    // Делитель

    binary_division(dividend, divisor);

    return 0;
}

// #include <stdio.h>

// typedef struct s21_big_decimal {
//     unsigned bits[8];
// } s21_big_decimal;

// void binary_division(s21_big_decimal dividend, s21_big_decimal divisor);
// int compare(s21_big_decimal a, s21_big_decimal b);
// s21_big_decimal subtract(s21_big_decimal a, s21_big_decimal b);

// void binary_division(s21_big_decimal dividend, s21_big_decimal divisor) {
//     s21_big_decimal quotient = {0};
//     s21_big_decimal remainder = {0};

//     for (int bit = 31; bit >= 0; bit--) {
//         // Сдвигаем остаток на один бит влево и добавляем следующий бит из делимого
//         int shift = bit % 32;
//         for (int i = 7; i >= 0; i--) {
//             remainder.bits[i] = (remainder.bits[i] << 1) | ((dividend.bits[i] >> shift) & 1);
//         }

//         // Проверяем, больше ли остаток делителя
//         if (compare(remainder, divisor) >= 0) {
//             quotient.bits[bit / 32] |= (1 << (bit % 32));  // Устанавливаем бит в частное
//             remainder = subtract(remainder, divisor);      // Вычитаем делитель из остатка
//         }
//     }

//     // printf("Quotient: %u\n", quotient.bits[0]);
//     // printf("Remainder: %u\n", remainder.bits[0]);
//     printf("Quotient: %u - %u - %u - %u\n", quotient.bits[0], quotient.bits[1], quotient.bits[2], quotient.bits[3]);
//     printf("Remainder: %u - %u - %u - %u\n", remainder.bits[0], remainder.bits[1], remainder.bits[2], remainder.bits[3]);
// }

// // Функция для сравнения двух структур s21_big_decimal
// int compare(s21_big_decimal a, s21_big_decimal b) {
//     for (int i = 7; i >= 0; i--) {
//         if (a.bits[i] > b.bits[i]) return 1;
//         else if (a.bits[i] < b.bits[i]) return -1;
//     }
//     return 0;
// }

// // Функция для вычитания одной структуры из другой
// s21_big_decimal subtract(s21_big_decimal a, s21_big_decimal b) {
//     s21_big_decimal result = {0};
//     int borrow = 0;

//     for (int i = 7; i >= 0; i--) {
//         long long diff = (long long)a.bits[i] - b.bits[i] - borrow;
//         if (diff < 0) {
//             diff += (1LL << 32);  // Используем long long для предотвращения переполнения
//             borrow = 1;
//         } else {
//             borrow = 0;
//         }
//         result.bits[i] = (unsigned)diff; // Приводим результат к беззнаковому целому
//     }

//     return result;
// }

// int main() {
//     s21_big_decimal dividend = {{5, 0, 0, 0, 0, 0, 0, 0}};  // Делимое
//     s21_big_decimal divisor = {{0, 2, 0, 0, 0, 0, 0, 0}};    // Делитель

//     binary_division(dividend, divisor);
//     return 0;
// }