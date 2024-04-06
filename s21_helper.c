#include "s21_decimal.h"

//это тестовое изменение

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
 * @brief Функция определяет масштаб числа по контрольному int
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
 * @brief Процедура устанавливает масштаб контрольному int
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
 * @brief Процедура очищает big_decimal, зануляя его int
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
 * @brief Функция осуществляет левое смещение в заданном big_decimal на заданное количество знаков
 * @param num указатель на заданный big_decimal, в котором будет реализовано левое смещение (s21_big_decimal)
 * @param shift_value задание количество знаков для смещения (int)
 * @return результат операции: 0 - все ОК; 1 - произошло переполнение
 */
int s21_shift_left(s21_big_decimal *num, int shift_value) {
    s21_big_decimal temp_value = *num;    
    unsigned memo = 0;
    unsigned temp_int = 0;

    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
        temp_int = temp_value.bits[i];
        temp_value.bits[i] <<= shift_value;
        temp_value.bits[i] |= memo;
        memo = temp_int >> (32 - shift_value);
    };
    if (!memo) *num = temp_value;
    return !!memo;
}

/**
 * @brief Функция осуществляет левое смещение в заданном big_decimal на заданное количество знаков
 * @param num заданный big_decimal, относительно которого будет реализовано левое смещение (s21_big_decimal)
 * @param shift_value задание количество знаков для смещения (int)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_shift_left_light(s21_big_decimal num, int shift_value){
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

/**
 * @brief Функция умножает значение мантиссы на 10 (10x = 8x + 2x = x<<3 + x<<1)
 * @param num заданный big_decimal (s21_big_decimal)
 * @return результирующий big_decimal
 */
s21_big_decimal s21_increase_order_light(s21_big_decimal num) {
    s21_big_decimal term_1 = s21_shift_left_light(num, 3);
    s21_big_decimal term_2 = s21_shift_left_light(num, 1);

    return s21_binary_add_light(term_1, term_2);
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
void s21_print_binary(int source) {
    for (int i = 31; i >= 0; i--) printf("%d", (source >> i) & 1);
    printf("\n");
}

/**
 * @brief Процедура печатает заданный decimal
 * @param source заданное значение (big_decimal)
 */
void s21_print_b_decimal(s21_big_decimal source) {
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
 * @brief Функция выдает инвертированное значение int
 * @param source заданное значение (unsigned)
 * @return инвертированное значение(unsigned)
 */
int s21_get_invert_int(int source) {
    return (~source);
}

/**
 * @brief Функция выдает двоичное дополнение к заданному big_decimal
 * @param source заданное значение (big_decimal)
 * @return двоичное дополнение (big_decimal)
 */
s21_big_decimal s21_get_complement(s21_big_decimal source) {
    s21_big_decimal result = s21_get_zero_big_decimal(); 
    s21_big_decimal one = {0,0,0,1};
    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) result.bits[i] = s21_get_invert_int(source.bits[i]);
    result = s21_binary_add_light(result, one);
    return result;
}


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