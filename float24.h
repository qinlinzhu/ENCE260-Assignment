#ifndef FLOAT24_H
#define FLOAT24_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int16_t mantissa;
    int8_t exponent;

} Float24_t;

Float24_t float24_init(int16_t mantissa, int8_t exponent);
Float24_t float24_multiply(Float24_t num1, Float24_t num2);
Float24_t float24_add(Float24_t num1, Float24_t num2);
void float24_print(Float24_t value);
Float24_t float24_glance(char* array);
Float24_t float24_read(void);
float float24_asIEEE();
void float24_max(Float24_t* num1, Float24_t* num2, Float24_t** max);
Float24_t* float24_arrayMax(Float24_t* array, size_t size, void (*func)(Float24_t*, Float24_t*, Float24_t**));

#endif 
