#include "../../lib/inc/aoc_helper.h"

bool correnct_sequence(int elem, int last_element, int inc)
{
    return ((elem - last_element) * inc > 0 && abs(last_element - elem) < 4 && last_element != elem);
}

bool check_line_exc_index(uint32_tVector *vec, size_t index)
{
    for (int i = 0; i < vec->len; i++)
    {
        if (i == index)
        {
            continue;
        }
    }
}

int main()
{
    FileReader reader = new_reader("day_2/input");

    int safe_count = 0;

    while (
        get_next_line(&reader))
    {
        uint32_tVector nums = new_uint32_t_vec(4);
        stringVector line = split_string_by(reader.line_content, ";");
        for (int i = 0; i < line.len; i++)
        {
            push_uint32_t(&nums, to_int(line.ptr[i]));
        }

        free_string_vec(&line);
        free_uint32_t_vec(&nums);
    }

    printf("%i\n", safe_count);

    drop_file(&reader);
}
