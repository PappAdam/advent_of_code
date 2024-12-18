#pragma once
#include <stdbool.h>
#include "readfile.h"
#include "vector.h"

typedef char *string;

DEFINE_VEC_HEADER(string);
DEFINE_VEC_HEADER(stringVector);
DEFINE_VEC_HEADER(uint32_t);
DEFINE_VEC_HEADER(uint8_t);
DEFINE_VEC_HEADER(char);
DEFINE_VEC_HEADER(uint64_t);

bool is_digit(char c);
uint32_t digit_count(char *c);
stringVector split_string_by(char *input, char *separator);
int to_int(char *input);
size_t int_pow(size_t num, size_t p);
void sort_array(uint32_t *array, size_t len);
void swap(int *a, int *b);
uint64_t to_insanely_fucking_long(char *input);