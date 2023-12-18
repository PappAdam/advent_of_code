#include "../readfile.h"

#define TASK2

typedef struct _LetterDigit
{
    const char *letters;
    uint8_t actual;
} LetterDigit;

const LetterDigit digit_lookup[] = {
    {
        .letters = "one",
        .actual = 1,
    },
    {
        .letters = "two",
        .actual = 2,
    },
    {
        .letters = "three",
        .actual = 3,
    },
    {
        .letters = "four",
        .actual = 4,
    },
    {
        .letters = "five",
        .actual = 5,
    },
    {
        .letters = "six",
        .actual = 6,
    },
    {
        .letters = "seven",
        .actual = 7,
    },
    {
        .letters = "eight",
        .actual = 8,
    },
    {
        .letters = "nine",
        .actual = 9,
    },
};

uint8_t check_digit(char *c)
{
    if (*c > '0' && *c <= '9')
    {
        return *c - 48;
    }

#ifdef TASK2
    for (uint8_t j = 0; j < 9; j++)
    {
        if (!memcmp(c, digit_lookup[j].letters, strlen(digit_lookup[j].letters)))
        {
            return digit_lookup[j].actual;
        }
    }
#endif

    return 0;
}

uint16_t get_sum(FileReader *reader)
{
    uint16_t sum = 0;
    char *line;
    while (line = get_next_line(reader))
    {
        size_t line_len = strlen(line);
        uint8_t digit_found;
        for (size_t i = 0; i < line_len; i++)
        {
            digit_found = check_digit(&line[i]);
            if (digit_found != 0)
            {
                sum += digit_found * 10;
                break;
            }
        }

        for (size_t i = line_len - 1; i >= 0; i--)
        {
            digit_found = check_digit(&line[i]);
            if (digit_found)
            {
                sum += digit_found;
                break;
            }
        }
    }

    return sum;
}

int main()
{
    FileReader reader = new_reader("input");
    printf("%i\n", get_sum(&reader));
    drop_file(&reader);
}
