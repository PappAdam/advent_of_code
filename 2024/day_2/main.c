#include "../../lib/inc/aoc_helper.h"

bool correnct_sequence(int elem, int last_elem, int inc)
{
    return ((elem - last_elem) * inc > 0 && abs(last_elem - elem) < 4 && last_elem != elem);
}

bool check_line(uint32_tVector *vec)
{
    int inc = vec->ptr[1] - vec->ptr[0];
    for (int i = 1; i < vec->len; i++)
    {
        if (!correnct_sequence(vec->ptr[i], vec->ptr[i - 1], inc))
        {
            return false;
        }
    }

    return true;
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
        for (int i = 0; i < line.len; i++)
        {
            uint32_tVector cpy_v = copy_uint32_t_vec(&nums);
            remove_uint32_t(&cpy_v, i, 1);

            if (check_line(&cpy_v))
            {
                safe_count++;
                free_uint32_t_vec(&cpy_v);
                break;
            }
            free_uint32_t_vec(&cpy_v);
        }

        free_string_vec(&line);
        free_uint32_t_vec(&nums);
    }

    printf("%i\n", safe_count);

    drop_file(&reader);
}
