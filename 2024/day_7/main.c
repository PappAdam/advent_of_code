#include "../../lib/inc/aoc_helper.h"

int main()
{
    FileReader reader = new_reader("day_7/input");

    uint64_t final_sum = 0;
    int index = 0;
    while (get_next_line(&reader))
    {
        stringVector l = split_string_by(reader.line_content, " ");
        uint64_t exp_res = to_insanely_fucking_long(l.ptr[0]);

        uint64_t ops_len = l.len - 2;
        uint64_t max_var = 1 << ops_len;
        bool found = false;
        for (uint32_t ops = 0; ops < max_var; ops++)
        {
            for (uint32_t join = 0; join < max_var; join++)
            {
                uint64_t res = to_insanely_fucking_long(l.ptr[1]);
                for (int op_i = 0; op_i < ops_len; op_i++)
                {
                    int bitmask = 1 << op_i;
                    if (bitmask & join)
                    {
                        res = res * int_pow(10, digit_count(l.ptr[op_i + 2])) + to_insanely_fucking_long(l.ptr[op_i + 2]);
                    }
                    else if (bitmask & ops)
                    {
                        res *= to_insanely_fucking_long(l.ptr[op_i + 2]);
                    }
                    else
                    {
                        res += to_insanely_fucking_long(l.ptr[op_i + 2]);
                    }
                }

                if (exp_res == res)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
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