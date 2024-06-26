#include "s21_decimal.h"

/**
 * @brief Функция определяет знак по контрольному int
 * @param check_value контрольный int (3й для decimal, 7й для big_decimal)
 * @return искомый знак (1 - положительный; 0 - отрицательный)
 */
int s21_get_sign(int checkable_value) {
    control_bit ctrl_bit;
    ctrl_bit.integer = checkable_value;
    return ctrl_bit.parts.sign;
}

/**
 * @brief Функция определяет скейл по контрольному int
 * @param check_value контрольный int (3й для decimal, 7й для big_decimal)
 * @return искомый масштаб (степень десятки в знаменателе числа)
 */
int s21_get_scale(int checkable_value) {
    control_bit ctrl_bit;
    ctrl_bit.integer = checkable_value;
    return ctrl_bit.parts.scale;
}

/**
 * @brief Процедура устанавливает знак контрольному int
 * @param mutable_value указатель на контрольный int (3й для decimal, 7й для big_decimal)
 * @param sign необходимый знак  (1 - положительный; 0 - отрицательный)
 */
void s21_set_sign(int *mutable_value, int sign) {
    control_bit ctrl_bit;
    ctrl_bit.integer = *mutable_value;
    ctrl_bit.parts.sign = sign ? 1 : 0;
    *mutable_value = ctrl_bit.integer;
}

/**
 * @brief Процедура скейл контрольному int
 * @param mutable_value указатель на контрольный int (3й для decimal, 7й для big_decimal)
 * @param sign необходимый масштаб (int)
 */
void s21_set_scale(int *mutable_value, int scale) {
    control_bit ctrl_bit;
    ctrl_bit.integer = *mutable_value;
    ctrl_bit.parts.scale = scale;
    *mutable_value = ctrl_bit.integer;
}

/**
 * @brief Процедура конвертирует decimal в big_decimal, перенося только мантиссу (т.е. первые 3 int)
 * @param source значение, которое необходимо конвертировать (s21_decimal)
 * @param result указатель на результат (s21_big_decimal *)
 */
void s21_convert_to_big_decimal(s21_decimal source, s21_big_decimal * result){
    s21_clear_big_decimal(result);
    result->bits[0] = (unsigned) source.bits[0];
    result->bits[1] = (unsigned) source.bits[1];
    result->bits[2] = (unsigned) source.bits[2];
}

/**
 * @brief Функция конвертирует decimal в big_decimal, перенося только мантиссу (т.е. первые 3 int)
 * @param source значение, которое необходимо конвертировать (s21_decimal)
 * @return получшившийся big_decimal
 */
s21_big_decimal s21_convert_to_big_decimal_light(s21_decimal source){
    s21_big_decimal result = s21_get_zero_big_decimal();
    result.bits[0] = (unsigned) source.bits[0];
    result.bits[1] = (unsigned) source.bits[1];
    result.bits[2] = (unsigned) source.bits[2];
    return result;
}

/**
 * @brief Процедура очищает big_decimal, зануляя его int
 * @param source указатель на результат (s21_big_decimal *)
 */
void s21_clear_big_decimal(s21_big_decimal *source) {
    for(int i = 0; i < BIG_DECIMAL_SIZE; i++) source->bits[i] = 0;
}

/**
 * @brief Процедура очищает decimal, зануляя его int
 * @param source указатель на результат (s21_decimal *)
 */
void s21_clear_decimal(s21_decimal *source) {
    for(int i = 0; i < DECIMAL_SIZE; i++) source->bits[i] = 0;
}

/**
 * @brief Функция определяет значение заданного бита
 * @param source заданный int в котором будет осуществляться изменение (int)
 * @param index положение бита (int)
 * @return значение искомого бита (int)
 */
int s21_get_bit(int source, int index){
    return !!(source & (1U << index));
}

/**
 * @brief Процедура устанавливает 1 в заданном месте заданного бита
 * @param source указатель на изменяемый int
 * @param index положение бита (int)
 */
void s21_set_bit(int *source, int index) {
    * source = *source | (1U << index);
}

/**
 * @brief Процедура устанавливает 0 в заданном месте заданного бита
 * @param source указатель на изменяемый int
 * @param index положение бита (int)
 */
void s21_set_no_bit(int *source, int index) {
    * source = *source & ~(1U << index);
}

/**
 * @brief Функция возвращает пустой big_decimal с зануленными интами
 * @return пустой big_decimal
 */
s21_big_decimal s21_get_zero_big_decimal() {
    s21_big_decimal temp;
    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) temp.bits[i] = 0;
    return temp;
}

/**
 * @brief Функция осуществляет левое смещение в заданном big_decimal на заданное количество знаков, но в пределах одного инта
 * @param num заданный big_decimal, относительно которого будет реализовано левое смещение (s21_big_decimal)
 * @param shift_value задание количество знаков для смещения (int)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_shift_left_into_integer(s21_big_decimal num, int shift_value){
    unsigned memo = 0;
    unsigned temp_int = 0;
    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        temp_int = num.bits[i];
        num.bits[i] <<= shift_value;
        num.bits[i] |= memo;
        memo = temp_int >> (32 - shift_value);
    };
    return num;    
}

int s21_bit_compare(int check_value, int reference){
    int result;
    if (check_value == reference) result = 0;
    if (check_value > reference) result = 1;
    if (check_value < reference) result = -1;
    return result;
}


/**
 * @brief Функция осуществляет левое смещение в заданном big_decimal на заданное количество знаков (не ограничиваясь пределами инта)
 * @param num заданный big_decimal, относительно которого будет реализовано левое смещение (s21_big_decimal)
 * @param shift_value задание количество знаков для смещения (int)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_shift_left(s21_big_decimal num, int shift_value){
    while (shift_value > 32) {
        shift_value -= 32;
        for (int i = 0; i < BIG_DECIMAL_SIZE - 1; i++) {
            num.bits[i] = num.bits[i + 1];
        }
    }
    num = s21_shift_left_into_integer(num, shift_value);
    return num;    
}

/**
 * @brief Функция осуществляет правое смещение в заданном big_decimal на заданное количество знаков (в пределах одного integer)
 * @param num заданный big_decimal, относительно которого будет реализовано правое смещение (s21_big_decimal)
 * @param shift_value задание количество знаков для смещения (int)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_shift_right_into_integer(s21_big_decimal num, int shift_value){
    unsigned memo = 0;
    unsigned temp_int = 0;
    for (int i = BIG_DECIMAL_SIZE - 1; i >= 0; i--) {
        temp_int = num.bits[i];
        num.bits[i] >>= shift_value;
        num.bits[i] |= memo;
        memo = temp_int << (32 - shift_value);
    }
    return num;    
}

/**
 * @brief Функция осуществляет правое смещение в заданном big_decimal на заданное количество знаков (не ограничиваясь пределами инта)
 * @param num заданный big_decimal, относительно которого будет реализовано правое смещение (s21_big_decimal)
 * @param shift_value задание количество знаков для смещения (int)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_shift_right(s21_big_decimal num, int shift_value){
    while (shift_value > 32) {
        shift_value -= 32;
        for (int i = BIG_DECIMAL_SIZE - 1; i > 0; i--) {
            num.bits[i] = num.bits[i - 1];
        }
    }
    num = s21_shift_right_into_integer(num, shift_value);
    return num;    
}

 /**
 * @brief Функция получает значение самого старшего бита (первый не нулевой бит)
 * @param source заданный big_decimal, в котором осуществляется поиск старшего бита (s21_big_decimal)
 * @return номер бита (int)
 */
int s21_get_highest_bit(s21_big_decimal source){
    int flag_exit = 0;
    int i;
    for (i = (BIG_DECIMAL_SIZE * INT_SIZE - 1); i >= 0 && !flag_exit; i--) if (s21_get_bit(source.bits[i / INT_SIZE], i % INT_SIZE)) flag_exit = 1;
    return ++i;    
}

/**
 * @brief Функция проверяет, что check_value больше чем reference
 * @param check_value проверяемое значение (s21_big_decimal)
 * @param reference эталонное значение (int)
 * @return результат сравнения: 1 - проверяемое значение больше эталона, 0 - они равны, -1 - проверяемое значение меньше эталона
 */
int s21_binary_compare(s21_big_decimal check_value, s21_big_decimal reference){
    int result = 0;
    for (int i = BIG_DECIMAL_SIZE - 1; i >= 0 && !result; i--){
        for (int j = INT_SIZE - 1; j >= 0 && !result; j--){
            result = s21_bit_compare(s21_get_bit(check_value.bits[i], j), s21_get_bit(reference.bits[i], j));
        }
    }
    return result;
}

/**
 * @brief Функция умножает значение мантиссы на 10 (10x = 8x + 2x = x<<3 + x<<1)
 * @param num заданный big_decimal (s21_big_decimal)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_increase_order_light(s21_big_decimal num) {
    s21_big_decimal term_1 = s21_shift_left(num, 3);
    s21_big_decimal term_2 = s21_shift_left(num, 1);
    return s21_binary_add(term_1, term_2);
}

/**
 * @brief Функция проверяет четность мантисы
 * @param check_value младший бит числа (нулевой int)
 * @return четность числа (1 - четное; 0 - нечетное)
 */
int s21_mantissa_even(int check_value) {
    return (check_value & 1) != 1;
}

/**
 * @brief Процедура печатает заданный int
 * @param source заданное значение (int)
 */
void s21_print_binary(unsigned source) {
    for (int i = 31; i >= 0; i--) printf("%d", (source >> i) & 1);
    // printf("\n");
}

/**
 * @brief Процедура печатает заданный decimal
 * @param source заданное значение (big_decimal)
 */
void s21_print_big_decimal(s21_big_decimal source) {
    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) s21_print_binary(source.bits[BIG_DECIMAL_SIZE - i - 1]);
    printf("\n");
}

/**
 * @brief Процедура печатает заданный decimal в десятичном формате
 * @param source заданное значение (big_decimal)
 */
void s21_print_b_decimal_10(s21_big_decimal source) {
    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) printf("%d ", source.bits[BIG_DECIMAL_SIZE - i - 1]);
    printf("\n");
}

/**
 * @brief процедура убирает замыкающие нули (для decimal) НЕ ГОТОВО
 * @param source число для обработки (decimal)
 */
void s21_standartization_(s21_decimal * source) {
    // while (s21_is_divisible_by_10(source->bits[0]) && s21_get_scale(source->bits[3]) > 0){
    //     printf("sd");
    // }
}

/**
 * @brief функция определяет делится ли число на 10
 * @param source проверяемое число (decimal)
 * @return результат проверки: 1 - делится на 10; 0 - не делится на 10 (int)
 */
 int s21_is_divisible_by_10(s21_decimal source) {
    return (source.bits[0] % 10 == 0);
}

/**
 * @brief процедура нормализует значения, т.е. приводит их к одному скейлу (требуется для сложения и вычитания)
 * @param source_1 исходное число 1 (s21_decimal)
 * @param source_2 исходное число 2 (s21_decimal)
 * @param result_1 ссылка для сохранения результата 1 (*s21_decimal)
 * @param result_2 ссылка для сохранения результата 2 (*s21_decimal)
 * @param scale_result ссылка для сохранения итогового скейла (*int)
 */
void s21_normalization(s21_decimal source_1, s21_decimal source_2, s21_big_decimal * result_1, s21_big_decimal * result_2, int * scale_result) {
    int scale_1 = s21_get_scale(source_1.bits[3]);
    int scale_2 = s21_get_scale(source_2.bits[3]);
    *scale_result = s21_max(scale_1, scale_2);
    *result_1 = (scale_1 < scale_2) ? s21_scaling_up(source_1, scale_2 - scale_1) : s21_convert_to_big_decimal_light(source_1);
    *result_2 = (scale_2 < scale_1) ? s21_scaling_up(source_2, scale_1 - scale_2) : s21_convert_to_big_decimal_light(source_2);
}

/**
 * @brief функция определяет максимум из двух чисел
 * @param val_1 проверяемое число (int)
 * @param val_2 проверяемое число (int)
 * @return максимальное число (int)
 */
int s21_max(int val_1, int val_2) {
    return (val_1 > val_2) ? val_1 : val_2;
}

/**
 * @brief функция преобразует децимал в бигдецимал и повышеает скейл на указанный уровень
 * @param source исходное число (s21_decimal)
 * @param scale_up порядок изменения масштаба (int)
 * @return результат (s21_big_decimal)
 */
s21_big_decimal s21_scaling_up(s21_decimal source, int scale_up) {
    s21_big_decimal result = s21_convert_to_big_decimal_light(source);
    s21_big_decimal ten = {10,0,0,0,0,0,0,0};
    for (int i = 0; i < scale_up; i++) result = s21_binary_mult(result, ten);
    return result;
}

/**
 * @brief функция определеяет равна ли мантиса децимал нулю
 * @param source исходное число (s21_decimal)
 * @return результат: 1 - истина; 0 - ложь (int)
 */
int is_null_decimal(s21_decimal source) {
    return source.bits[0] == 0 && source.bits[1] == 0 && source.bits[2] == 0;
}

/**
 * @brief проверяет корректность данных, записанных в decimal () 
  * @param source проверяемый decimal (s21_decimal)
 * @return int 1 - ок, 0 - некорректные данные
 */
int s21_is_correct_decimal(s21_decimal source) {
    int result = 1;

    control_bit ctrl_bit;
    ctrl_bit.integer = source.bits[3];

    if (ctrl_bit.parts.empty1 != 0 || ctrl_bit.parts.empty2 != 0) result = 0;
    else if (ctrl_bit.parts.scale < 0 || ctrl_bit.parts.scale >28) result = 0;

    return result;
}

/**
 * @brief конвертирует bigdecimal в decimal
 * @param source исходный bigdecimal (s21_bigdecimal)
 * @return int результат преобразния (код ошибки):
 */
int s21_convert_to_decimal(s21_big_decimal source, s21_decimal * result, int * scale, int sign) {
    s21_big_decimal ten = {10,0,0,0,0,0,0,0};
    s21_big_decimal one = {1,0,0,0,0,0,0,0};
    int err_code = 0;
    unsigned last_digit, pre_last_digit;
    while (s21_is_overflow_mantissa(source) && *scale) {
        last_digit = source.bits[0] % 10;
        pre_last_digit = (source.bits[0] / 10) % 10;
        source = s21_binary_div(source, ten);
        * scale -= 1;
        if (last_digit > 5 || (last_digit = 5 && (pre_last_digit % 2))) source = s21_binary_add(source,one);
    }

    if (!s21_is_overflow_mantissa(source)){
        s21_set_mantissa(source, result);
        s21_set_sign(result, sign);
        s21_set_scale(result, scale);
    } else {
        * result = s21_get_inf(sign);
        s21_set_sign(result, sign);
        err_code = (sign) ? S21_ARITHMETIC_SMALL : S21_ARITHMETIC_BIG; 
    }
    return err_code;
}

/**
 * @brief переносит мантиссу в decimal
 * @param source исходный bigdecimal (s21_bigdecimal)
 * @param result ссылка на результат (s21_decimal)
 */
s21_decimal s21_set_mantissa(s21_big_decimal source, s21_decimal * result){
    result->bits[0] = source.bits[0];
    result->bits[1] = source.bits[1];
    result->bits[2] = source.bits[2];
}

/**
 * @brief проверяет переполнение при попытке переноса мантисы из bigdecimal в decimal
 * @param source проверяемый bigdecimal (s21_bigdecimal)
 * @return int результат проверки: 1 - переполнение; 0 - нет переполнения
 */
int s21_is_overflow_mantissa(s21_big_decimal source) {
    return !!source.bits[7] || !!source.bits[6] || !!source.bits[5] || !!source.bits[4] || !!source.bits[3];
}

/**
 * @brief выдает максимальное значение нужного знака
 * @param source проверяемый bigdecimal (s21_bigdecimal)
 * @param sign знак (int)
 * @return s21_decimal результат
 */
s21_decimal s21_get_inf(int sign) {
    s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00}};
    s21_set_sign(&result, sign);
    return result;
}

// /**
//  * @brief проверяет переполнение при попытке переноса мантисы из bigdecimal в decimal
//  * @param source проверяемый bigdecimal (s21_bigdecimal)
//  * @return int результат проверки: 1 - переполнение; 0 - нет переполнения
//  */
// s21_big_decimal s21_div_ten(s21_decimal source, int scale_up) {
//     s21_big_decimal result = s21_convert_to_big_decimal_light(source);
//     s21_big_decimal ten = {10,0,0,0,0,0,0,0};
//     for (int i = 0; i < scale_up; i++) result = s21_binary_mult(result, ten);
//     return result;
// }

// /** НЕАКТУАЛЬНО, т.к. работает только на интах, а у меня беззнаковые используются
//  * @brief Функция выдает инвертированное значение int
//  * @param source заданное значение (unsigned)
//  * @return инвертированное значение(unsigned)
//  */
// int s21_get_invert_int(int source) {
//     return (~source);
// }

// /** НЕАКТУАЛЬНО, т.к. работает только на интах, а у меня беззнаковые используются
//  * @brief Функция выдает двоичное дополнение к заданному big_decimal
//  * @param source заданное значение (big_decimal)
//  * @return двоичное дополнение (big_decimal)
//  */
// s21_big_decimal s21_get_complement(s21_big_decimal source) {
//     s21_big_decimal result = s21_get_zero_big_decimal(); 
//     s21_big_decimal one = {0,0,0,1};
//     for (int i = 0; i < BIG_DECIMAL_SIZE; i++) result.bits[i] = s21_get_invert_int(source.bits[i]);
//     result = s21_binary_add_light(result, one);
//     return result;
// }


// int s21_get_sign(s21_decimal decimal) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal.bits[3];
//     return ctrl_bit.parts.sign;
// }

// int s21_get_scale(s21_decimal decimal) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal.bits[3];
//     return ctrl_bit.parts.scale;
// }

// void s21_set_sign(s21_decimal *decimal, int sign) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal->bits[3];
//     ctrl_bit.parts.sign = sign ? 1 : 0;
//     decimal->bits[3] = ctrl_bit.integer;
// }

// void s21_decimal_set_power(s21_decimal *decimal, int scale) {
//     control_bit ctrl_bit;
//     ctrl_bit.integer = decimal->bits[3];
//     ctrl_bit.parts.scale = scale;
//     decimal->bits[3] = ctrl_bit.integer;
// }

// //проверяет четность мантиссы (не всего числа)
// int s21_mantissa_even(s21_decimal value) {
//     return (value.bits[0] & 1) != 1;
// }

// /**
//  * @brief Функция осуществляет левое смещение в заданном big_decimal на один бит
//  * @param num заданный big_decimal, относительно которого будет реализовано левое смещение (s21_big_decimal)
//  * @return результирующий big_decimal
//  */
// s21_big_decimal s21_shift_left_single(s21_big_decimal num){
//     unsigned memo = 0;
//     unsigned temp_int = 0;
//     for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
//         temp_int = num.bits[i];
//         num.bits[i] <<= 1;
//         num.bits[i] |= memo;
//         memo = temp_int >> (32 - shift_value);
//     };
//     return num;    
// }

// /**
//  * @brief Функция осуществляет правое смещение в заданном big_decimal на один бит
//  * @param num заданный big_decimal, относительно которого будет реализовано левое смещение (s21_big_decimal)
//  * @return результирующий big_decimal
//  */
// s21_big_decimal s21_shift_left_single(s21_big_decimal num){
//     unsigned memo = 0;
//     unsigned temp_int = 0;
//     for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
//         temp_int = num.bits[i];
//         num.bits[i] <<= 1;
//         num.bits[i] |= memo;
//         memo = temp_int >> (32 - shift_value);
//     };
//     return num;    
// }

// /**
//  * @brief Функция осуществляет левое смещение в заданном big_decimal на заданное количество знаков
//  * @param num указатель на заданный big_decimal, в котором будет реализовано левое смещение (s21_big_decimal)
//  * @param shift_value задание количество знаков для смещения (int)
//  * @return результат операции: 0 - все ОК; 1 - произошло переполнение
//  */
// int s21_shift_left(s21_big_decimal *num, int shift_value) {
//     s21_big_decimal temp_value = *num;    
//     unsigned memo = 0;
//     unsigned temp_int = 0;

//     for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
//         temp_int = temp_value.bits[i];
//         temp_value.bits[i] <<= shift_value;
//         temp_value.bits[i] |= memo;
//         memo = temp_int >> (32 - shift_value);
//     };
//     if (!memo) *num = temp_value;
//     return !!memo;
// }


// /**
//  * @brief Функция осуществляет левое смещение в заданном big_decimal на заданное количество знаков, но не больше размера инта
//  * @param num заданный big_decimal, относительно которого будет реализовано левое смещение (s21_big_decimal)
//  * @param shift_value задание количество знаков для смещения (int)
//  * @return результирующий big_decimal
//  */
// s21_big_decimal s21_shift_left_light(s21_big_decimal num, int shift_value){
//     unsigned memo = 0;
//     unsigned temp_int = 0;
//     for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
//         temp_int = num.bits[i];
//         num.bits[i] <<= shift_value;
//         num.bits[i] |= memo;
//         memo = temp_int >> (32 - shift_value);
//     };
//     return num;    
// }