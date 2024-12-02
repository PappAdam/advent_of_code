#include "inc/aoc_helper.h"

DEFINE_VEC(string);
DEFINE_VEC(uint32_t);

bool is_digit(char ptr)
{
    return (ptr >= '0' && ptr <= '9');
}

void swap(int *a, int *b)
{
    int ptr = *a;
    *a = *b;
    *b = ptr;
}

void sort_array(uint32_t *array, size_t len)
{
    for (int i = 0; i < len - 1; i++)
    {
        size_t min_i = i;
        for (int j = i + 1; j < len; j++)
        {
            if (array[j] < array[min_i])
            {
                min_i = j;
            }
        }
        swap(&array[min_i], &array[i]);
    }
}

/// Returned string vector array needs to be freed
stringVector split_string_by(char *input, char *separator)
{
    stringVector result = new_string_vec(2);
    size_t input_len = strlen(input);
    size_t separator_len = strlen(separator);
    size_t last_segment_index = 0;
    for (size_t i = 0; i < input_len; i++)
    {
        size_t j;
        for (j = 0; j < separator_len; j++)
        {
            if (input[i + j] != separator[j])
            {
                break;
            }
        }

        if (j == separator_len)
        {
            string new_str = malloc(i - last_segment_index + 1);
            memcpy(new_str, input + last_segment_index, i - last_segment_index);
            new_str[i - last_segment_index] = '\0';
            push_string(&result, new_str);
            last_segment_index = i + j;
        }
        i += j;
    }

    string new_str = malloc(input_len - last_segment_index + 1);
    memcpy(new_str, input + last_segment_index, input_len - last_segment_index);
    push_string(&result, new_str);

    return result;
}

size_t int_pow(size_t num, size_t p)
{
    size_t res = 1;
    for (size_t i = 0; i < p; i++)
    {
        res *= num;
    }
    return res;
}

int to_int(char *input)
{

    int neg = 0;
    if (input[0] == '-')
    {
        neg = 1;
    }
    int res = 0;
    size_t len = strlen(input);
    for (int i = 0; i < len && is_digit(input[i + neg]); i++)
    {
        res *= 10;
        res += input[i + neg] - 48;
    }

    return res * -(neg * 2 - 1);
}