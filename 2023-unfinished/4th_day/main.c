#include "../readfile.h"
#include "../vector.h"
#include "../aoc_helper.h"
#include <stdbool.h>

DEFINE_VEC(uint8_t);
typedef struct _scratchcard
{
    size_t index;
    uint8_t numbers_won;
    size_t quantity;
} ScratchCard;
DEFINE_VEC(ScratchCard);

bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

bool is_winning_num(uint8_tVector *vec, uint8_t number)
{
    for (size_t i = 0; i < vec->len; i++)
    {
        if (number == vec->content[i])
        {
            return true;
        }
    }
    return false;
}

size_t get_points(char *line, ScratchCardVector *sc_vec)
{
    uint8_tVector winning_numbers = new_uint8_t_vec(20);
    size_t line_len = strlen(line);
    uint32_t i = 8;
    uint8_t number = 0;
    size_t points = 0;
    while (line[i] != '|')
    {
        if (is_digit(line[i]))
        {
            number *= 10;
            number += line[i] - 48;
        }
        else
        {
            if (number != 0)
            {
                push_uint8_t(&winning_numbers, number);
                number = 0;
            }
        }
        i++;
    }

    uint8_t numbers_won = 0;
    for (; i < line_len; i++)
    {
        if (is_digit(line[i]))
        {
            number *= 10;
            number += line[i] - 48;
        }
        else
        {
            if (number != 0)
            {
                if (is_winning_num(&winning_numbers, number))
                {
                    if (!points)
                    {
                        points = 1;
                    }
                    else
                    {
                        points = points << 1;
                    }
                    numbers_won++;
                }
                number = 0;
            }
        }
    }

    push_ScratchCard(sc_vec, (ScratchCard){
                                 .index = sc_vec->len,
                                 .numbers_won = numbers_won,
                                 .quantity = 1});

    free(winning_numbers.content);

    return points;
}

size_t get_total_cards(ScratchCardVector *sc_vec)
{
    size_t total = 0;
    for (size_t i = 0; i < sc_vec->len; i++)
    {
        total += sc_vec->content[i].quantity;
        for (size_t j = 0; j < sc_vec->content[i].numbers_won; j++)
        {
            if (i + j + 1 < sc_vec->len)
            {
                sc_vec->content[i + j + 1].quantity += sc_vec->content[i].quantity;
            }
        }
    }
    return total;
}

int main()
{
    FileReader reader = new_reader("input");
    char *line;
    size_t sum = 0;
    ScratchCardVector sc_vec = new_ScratchCard_vec(198);
    while (line = get_next_line(&reader))
    {
        sum += get_points(line, &sc_vec);
    }
    printf("task 1: %i\n", sum);
    printf("task 2: %i\n", get_total_cards(&sc_vec));
    drop_file(&reader);
    free(sc_vec.content);
}