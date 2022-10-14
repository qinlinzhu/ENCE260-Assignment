#ifndef FLOAT24_C
#define FLOAT24_C
#include "float24.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



Float24_t float24_init(int16_t mantissa, int8_t exponent)
{
    Float24_t val;
    val.mantissa = mantissa;
    val.exponent = exponent;
    return val;
}


static Float24_t float24_normalise(int32_t oversizeMantissa, int8_t exponent) 
{
    Float24_t val;
    while (oversizeMantissa > INT16_MAX || oversizeMantissa < -INT16_MAX) {
        oversizeMantissa = oversizeMantissa / 2;
        exponent = exponent + 1;
    }
    val.mantissa = oversizeMantissa;
    val.exponent = exponent;
    return val;
}


Float24_t float24_multiply(Float24_t num1, Float24_t num2)
{
    int32_t mantissa;
    int32_t exponent;
    exponent = num1.exponent + num2.exponent;
    mantissa = num1.mantissa * num2.mantissa;
    return (float24_normalise(mantissa, exponent));
}
Float24_t float24_add(Float24_t num1, Float24_t num2)
{
    int32_t mantissa;
    int32_t exponent;
    if (num1.exponent == num2.exponent) {
        mantissa = num1.mantissa + num2.mantissa;
        exponent = num1.exponent;
    } else if (num1.exponent > num2.exponent) {

        while (num1.exponent > num2.exponent) {
            num2.mantissa = num2.mantissa / 2;
            num2.exponent = num2.exponent + 1;  
        } 
        exponent = num1.exponent;
        mantissa = num1.mantissa + num2.mantissa;
    } else if (num1.exponent < num2.exponent ) {
        while (num1.exponent < num2.exponent ) {
            num1.mantissa = num1.mantissa / 2;
            num1.exponent = num1.exponent + 1; 
        }
        exponent = num2.exponent;
        mantissa = num1.mantissa + num2.mantissa;
        
    }
    return (float24_normalise(mantissa, exponent));
        
} 

void float24_print(Float24_t value)
{
    printf("%d * 2 ^ %d\n", value.mantissa, value.exponent);
}

Float24_t float24_glance(char* array)
{
    Float24_t val;
    int32_t exponent;
    size_t j = 0;
    size_t i = 0;
    size_t otheri = 0;
    char stringtissa[5] = {0};
    char stringponent[5] = {0};
    while(isdigit(array[j]) || array[j] == '-'|| array[j] == '+') {
        stringtissa[i] = array[j];
        i++;
        j++;
    }
    j++;
    val.mantissa = atoi(stringtissa);
    do {
        stringponent[otheri] = array[j];
        otheri++;
        j++;
    } while (isdigit(array[j]) || array[j] == '-'|| array[j] == '+');
    exponent = atoi(stringponent);
    if (exponent > 127) {
        exponent = 127;
    } else if (exponent < -127) {
        exponent = -127;
    }
    val.exponent = exponent;
    return(val);
}

void float24_max(Float24_t* num1, Float24_t* num2, Float24_t** max)
{
    if ((num1->exponent == num2->exponent)) {
        if (num1->mantissa >= num2->mantissa) {
            *max = num1;
        } else {
            *max = num2;
        }
    } else if ((num1->mantissa * pow(2,num1->exponent)) > (num2->mantissa * pow(2,num2->exponent))) {
        *max = num1;
    } else {
        *max = num2;
    }
        
}


Float24_t float24_read(void) 
{
    Float24_t val;
    char c;
    char array[10] = {0};
    size_t i = 0;
    while((c=getchar()) != '\n' && c!= EOF && c!= ' ') {
        array[i] = c;
        i++;
    }
    for (int i = 0; i < sizeof(array); i++) {
        if (array[i] != 'b' && isalpha(array[i])) {
            val.mantissa = 0;
            val.exponent = -128;
            return (float24_normalise(val.mantissa, val.exponent));
            break;
        }
    }
    val = float24_glance(array);
    return (float24_normalise(val.mantissa, val.exponent));
}

Float24_t* float24_arrayMax(Float24_t* array, size_t size, void (*func)(Float24_t*, Float24_t*, Float24_t**))
{
    size_t i;
    Float24_t* pointer = &array[0];
    for (i = 1; i < size; i++) {
        (*func)(&array[i], pointer, &pointer);
    }
    return pointer;
}
#endif 
