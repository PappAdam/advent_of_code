#include "../aoc_helper.h"

typedef struct _range
{
    size_t dst;
    size_t src;
    size_t len;
} Range;

DEFINE_VEC(Range);
DEFINE_VEC(uint64_t);

void parse_file(FileReader *reader, RangeVector *convert_ranges, uint64_tVector *seeds);

size_t
find_range_index(RangeVector *ranges, size_t value)
{
    size_t range_index = ~0;

    for (size_t i = 0; i < ranges->len; i++)
    {
        if (value > ranges->ptr[i].src && value < ranges->ptr[i].src + ranges->ptr[i].len - 1)
        {
            range_index = i;
            break;
        }
    }

    return range_index;
}

size_t
get_location(uint64_t seed, RangeVector *convert_ranges)
{
    size_t converted_val = seed;
    for (size_t r = 0; r < 7; r++)
    {
        RangeVector ranges = convert_ranges[r];
        size_t range_index = find_range_index(&ranges, converted_val);

        if (range_index == ~0)
        {
            continue;
        }
        Range range = ranges.ptr[range_index];

        converted_val = (converted_val - range.src) + range.dst;
    }

    return converted_val;
}

size_t search_ranges()
{
}

int main()
{
    FileReader reader = new_reader("input");
    RangeVector convert_ranges[7];
    uint64_tVector seeds = new_uint64_t_vec(16);

    parse_file(&reader, convert_ranges, &seeds);
    size_t lowest = ~0;
    for (size_t i = 0; i < seeds.len; i++)
    {
        size_t current = get_location(seeds.ptr[i], convert_ranges);
        if (current < lowest)
        {
            lowest = current;
        }
    }
    printf("task1: %u\n", lowest);

    for (size_t i = 0; i < 7; i++)
    {
        free(convert_ranges[i].ptr);
    }
    free(seeds.ptr);
    drop_file(&reader);
}

void parse_file(FileReader *reader, RangeVector *convert_ranges, uint64_tVector *seeds)
{
    char *line = get_next_line(reader);
    size_t line_len = strlen(line);
    uint64_t number = 0;
    for (size_t i = 6; i < line_len; i++)
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
                push_uint64_t(seeds, number);
                number = 0;
            }
        }
    }

    uint8_t converter_index = 0;
    RangeVector *converter;
    while (line = get_next_line(reader))
    {
        line_len = strlen(line);
        if (line[0] == '\n')
        {
            continue;
        }
        if (!is_digit(line[0]))
        {
            convert_ranges[converter_index] = new_Range_vec(16);
            converter = &convert_ranges[converter_index++];
            continue;
        }
        size_t _range[3];
        size_t *range = _range;
        number = 0;
        for (size_t i = 0; i < line_len; i++)
        {
            if (!is_digit(line[i]))
            {
                *range = number;
                range++;
                number = 0;
            }
            else
            {
                number *= 10;
                number += line[i] - 48;
            }
        }

        range -= 3;
        Range r = {.dst = range[0], .src = range[1], .len = range[2]};
        push_Range(converter, r);
    }
}