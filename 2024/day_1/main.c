#include "../../lib/inc/aoc_helper.h"

int main()
{
    FileReader reader = new_reader("day_1/input");

    uint32_tVector left_col = new_uint32_t_vec(1000);
    uint32_tVector right_col = new_uint32_t_vec(1000);

    while (get_next_line(&reader))
    {
        stringVector splitLine = split_string_by(reader.line_content, "   ");
        push_uint32_t(&left_col, to_int(get_string(&splitLine, 0)));
        push_uint32_t(&right_col, to_int(get_string(&splitLine, 1)));
        free(get_string(&splitLine, 0));
        free(get_string(&splitLine, 1));
        free_string_vec(&splitLine);
    }

    sort_array(left_col.content, left_col.len);
    sort_array(right_col.content, right_col.len);

    size_t sum1 = 0;
    size_t sum2 = 0;
    for (int i = 0; i < left_col.len; i++)
    {
        sum1 += abs(get_uint32_t(&left_col, i) - get_uint32_t(&right_col, i));
        size_t multip = 0;
        for (int j = 0; j < left_col.len; j++)
        {
            if (get_uint32_t(&left_col, i) == get_uint32_t(&right_col, j))
            {
                multip++;
            }
        }
        sum2 += get_uint32_t(&left_col, i) * multip;
    }

    free_uint32_t_vec(&left_col);
    free_uint32_t_vec(&right_col);
    drop_file(&reader);

    printf("1: %i\n", sum1);
    printf("2: %i\n", sum2);
}