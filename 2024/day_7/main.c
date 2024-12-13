#include "../../lib/inc/aoc_helper.h"

int main()
{
    FileReader reader = new_reader("day_7/input");

    int final_sum = 0;
    int index = 0;
    while (get_next_line(&reader))
    {
        stringVector l = split_string_by(reader.line_content, " ");
        uint64_t exp_res = to_insanely_fucking_long(l.ptr[0]);
        int ops_len = l.len - 2;
        uint8_t *ops = malloc(ops_len);
        uint32_t max_var = 1 << ops_len;
        bool found = false;

        for (uint32_t i = 0; i < max_var; i++)
        {
            uint64_t res = to_insanely_fucking_long(l.ptr[1]);
            for (int j = 0; j < ops_len; j++)
            {
                int bitmask = 1 << j;
                if (bitmask & i)
                {
                    res *= to_insanely_fucking_long(l.ptr[j + 2]);
                }
                else
                {
                    res += to_insanely_fucking_long(l.ptr[j + 2]);
                }
            }
            if (exp_res == res)
            {
                printf(l.ptr[1]);
                for (int j = 0; j < ops_len; j++)
                {
                    int bitmask = 1 << j;
                    if (bitmask & i)
                    {
                        printf(" * %lld", to_insanely_fucking_long(l.ptr[j + 2]));
                    }
                    else
                    {
                        printf(" + %lld", to_insanely_fucking_long(l.ptr[j + 2]));
                    }
                }
                printf(" = %lld", exp_res);
                printf("\n");
                found = true;
                break;
            }
        }

        if (found)
        {
            final_sum += exp_res;
        }
        index++;
    }

    printf("%lld\n", final_sum);

    drop_file(&reader);
}