#include "../readfile.h"
#include "../vector.h"
#include <stdbool.h>

typedef char *string;

DEFINE_VEC(string);

bool is_symbol(char c)
{
    return ((c < '0' || c > '9') && c != '.');
}

bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

bool has_surrounding_symbol(stringVector *vec, size_t i, size_t j)
{
    size_t y_max = vec->len - 1;
    size_t x_max = strlen(vec->content[i]) - 2;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {

            if (y == 0 && x == 0)
            {
                continue;
            }

            int cur_x = j + x;
            int cur_y = i + y;

            if (cur_x < 0 || cur_x > x_max || cur_y < 0 || cur_y > y_max)
            {
                continue;
            }

            if (is_symbol(vec->content[cur_y][cur_x]))
            {
                return true;
            }
        }
    }

    return false;
}
size_t get_part_sum(stringVector *vec)
{
    size_t sum = 0;
    for (size_t i = 0; i < vec->len; i++)
    {
        size_t line_len = strlen(vec->content[i]);
        bool has_symbol = false;
        size_t number = 0;
        for (size_t j = 0; j < line_len; j++)
        {
            char c = vec->content[i][j];
            if (!is_digit(c))
            {
                if (number != 0)
                {
                    if (has_symbol)
                    {
                        sum += number;
                    }

                    number = 0;
                    has_symbol = false;
                }
                continue;
            }

            if (!has_symbol && has_surrounding_symbol(vec, i, j))
            {
                has_symbol = true;
            }

            number *= 10;
            number += c - 48;
        }
    }

    return sum;
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
size_t get_ratio(stringVector *vec, size_t i, size_t j)
{
    uint8_t gear_parts = 0;
    size_t product = 1;
    bool skip = false;
    for (int cy = -1; cy <= 1; cy++)
    {
        bool has_middle = true;
        skip = false;
        for (int cx = -1; cx <= 1; cx += 2)
        {
            size_t x = cx + j;
            size_t y = cy + i;
            uint16_t number = vec->content[y][x] - 48;
            if (skip)
            {
                skip = false;
                continue;
            }

            if (is_digit(vec->content[y][x]))
            {
                has_middle = false;
                uint8_t digit_diff = 1;
                int tens = 10;
                while (is_digit(vec->content[y][x - digit_diff]))
                {
                    number += (vec->content[y][x - digit_diff] - 48) * tens;
                    tens *= 10;
                    digit_diff++;
                }

                digit_diff = 1;
                while (is_digit(vec->content[y][x + digit_diff]))
                {
                    number *= 10;
                    number += vec->content[y][x + digit_diff] - 48;
                    digit_diff++;
                }

                if (digit_diff > 2)
                {
                    skip = true;
                }
                product *= number;
                gear_parts++;
            }
        }
    }

    if (gear_parts == 2)
    {
        return product;
    }
    return 0;
}

size_t get_ratio_sum(stringVector *vec)
{
    size_t sum = 0;
    for (size_t i = 0; i < vec->len; i++)
    {
        size_t line_len = strlen(vec->content[i]);
        for (size_t j = 0; j < line_len; j++)
        {
            char c = vec->content[i][j];
            if (c == '*')
            {
                sum += get_ratio(vec, i, j);
            }
        }
    }

    return sum;
}

int main()
{
    FileReader reader = new_reader("input");
    stringVector matrix = new_string_vec(32);
    char *line;
    while (line = get_next_line(&reader))
    {
        char *copied_line = malloc(strlen(line));
        memcpy(copied_line, line, strlen(line));
        push_string(&matrix, copied_line);
    }

    printf("task1: %i\n", get_part_sum(&matrix));
    printf("task2: %i\n", get_ratio_sum(&matrix));

    for (size_t i = 0; i < matrix.len; i++)
    {
        free(matrix.content[i]);
    }

    free(matrix.content);
    drop_file(&reader);
}