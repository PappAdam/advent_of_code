#pragma once
#include <stdbool.h>
#include "readfile.h"
#include "vector.h"

typedef char *string;

DEFINE_VEC_HEADER(string);
DEFINE_VEC_HEADER(stringVector);
DEFINE_VEC_HEADER(uint32_t);

bool is_digit(char c);
stringVector split_string_by(char *input, char *separator);
int to_int(char *input);
size_t int_pow(size_t num, size_t p);
void sort_array(uint32_t *array, size_t len);
void swap(int *a, int *b);