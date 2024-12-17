#include "../../lib/inc/aoc_helper.h"

int main()
{
    FileReader reader = new_reader("day_9/input");
    get_next_line(&reader);
    int line_len = strlen(reader.line_content) - 1;
    uint32_tVector vec = new_uint32_t_vec(100);
    bool alternate;
    int id = 0;
    for (int i = 0; i < line_len; i++)
    {
        char c = reader.line_content[i] - 48;
        for (int j = 0; j < c; j++)
        {
            push_uint32_t(&vec, id | (UINT32_MAX * alternate));
        }

        id += !alternate;
        alternate = !alternate;
    }

    uint32_t bwd_i = vec.len - 1;
    uint64_t result = 0;
    for (int i = 0; i < bwd_i; i++)
    {
        if (vec.ptr[i] == UINT32_MAX)
        {
            while (vec.ptr[bwd_i] == UINT32_MAX)
            {
                bwd_i--;
            }

            swap(&vec.ptr[i], &vec.ptr[bwd_i]);
        }
        result += i * vec.ptr[i];
    }

    printf("%lld\n", result);

    drop_file(&reader);
}
