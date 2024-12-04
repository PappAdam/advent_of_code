#include "../../lib/inc/aoc_helper.h"

int main()
{
    FileReader reader = new_reader("day_3/input");

    int sum = 0;
    bool active = true;
    while (get_next_line(&reader))
    {
        int line_size = strlen(reader.line_content);
        char *line = reader.line_content;
        for (int i = 0; i < line_size; i++)
        {
            if (!memcmp(&line[i], "do()", 4))
            {

                active = true;
            }
            if (!memcmp(&line[i], "don't()", 7))
            {

                active = false;
            }

            if (!memcmp(&line[i], "mul(", 4))
            {
                int l = i + 4;
                int num_i = 0;
                int nums[] = {0, 0};
                while (is_digit(line[l]) || line[l] == ',')
                {
                    if (is_digit(line[l]))
                    {
                        nums[num_i] = nums[num_i] * 10 + line[l] - 48;
                    }
                    else if (line[l] == ',')
                    {
                        num_i += 1;
                    }
                    l++;
                }

                if (line[l] == ')' && num_i == 1)
                {
                    if (active)
                        sum += nums[0] * nums[1];
                }

                i = l;
            }
        }
    }

    printf("%i\n", sum);

    drop_file(&reader);
}