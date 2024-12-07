#include "../../lib/inc/aoc_helper.h"

DEFINE_VEC_HEADER(uint32_tVector);
DEFINE_VEC(uint32_tVector);

bool check_page_numbers(uint32_tVector *pagenums, uint32_tVectorVector *rules, int latter, int former)
{
    int i;
    for (i = 0; i < pagenums->len; i++)
    {
        if (pagenums->ptr[i] == latter)
        {
            int j;
            for (j = 0; j < rules->ptr[i].len; j++)
            {
                if (rules->ptr[i].ptr[j] == former)
                {
                    return false;
                }
            }
            break;
        }
    }
    return true;
}

int sort_nums(uint32_tVector *pagenums, uint32_tVectorVector *rules, uint32_tVector *nums)
{
    bool swapped = false;
    // for (int k = 0; k < nums->len; k++)
    // {
    //     printf("%i, ", nums->ptr[k]);
    // }
    printf("\n");

    for (int i = nums->len - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (!check_page_numbers(pagenums, rules, nums->ptr[i], nums->ptr[j]))
            {
                swap(&nums->ptr[i], &nums->ptr[j]);

                swapped = true;
                i += 1;
                break;
            }
        }
    }
    if (swapped)
    {
        return nums->ptr[(nums->len - 1) / 2];
    }

    return 0;
}

int main()
{
    FileReader reader = new_reader("day_5/input");

    uint32_tVector pagenums = new_uint32_t_vec(90);
    uint32_tVectorVector rules = new_uint32_tVector_vec(90);
    while (get_next_line(&reader)[0] != '\n')
    {
        stringVector line = split_string_by(reader.line_content, "|");
        int num1 = to_int(line.ptr[0]);
        int num2 = to_int(line.ptr[1]);

        int i;
        for (i = 0; i < pagenums.len; i++)
        {
            if (pagenums.ptr[i] == num1)
            {
                push_uint32_t(&rules.ptr[i], num2);
                break;
            }
        }

        if (i == pagenums.len)
        {
            push_uint32_t(&pagenums, num1);
            uint32_tVector vec = new_uint32_t_vec(1);
            push_uint32_t(&vec, num2);
            push_uint32_tVector(&rules, vec);
        }

        free(line.ptr[0]);
        free(line.ptr[1]);
        free_string_vec(&line);
    }

    for (int i = 0; i < pagenums.len; i++)
    {
        printf("num: %i\n\t", pagenums.ptr[i]);
        for (int j = 0; j < rules.ptr[i].len; j++)
        {
            printf("%i, ", rules.ptr[i].ptr[j]);
        }
        printf("\n");
    }

    int sum = 0;
    while (get_next_line(&reader))
    {
        stringVector line = split_string_by(reader.line_content, ",");
        uint32_tVector nums = new_uint32_t_vec(2);

        for (int i = 0; i < line.len; i++)
        {
            push_uint32_t(&nums, to_int(line.ptr[i]));
        }

        sum += sort_nums(&pagenums, &rules, &nums);

        int correct = true;
        for (int i = nums.len - 1; i >= 0; i--)
        {
            if (!correct)
            {
                break;
            }
            for (int j = 0; j < i; j++)
            {
                if (!check_page_numbers(&pagenums, &rules, nums.ptr[i], nums.ptr[j]))
                {
                    correct = false;
                    printf("%i, %i\n", nums.ptr[i], nums.ptr[j]);
                    for (int i = 0; i < nums.len; i++)
                    {
                        printf("%i,", nums.ptr[i]);
                    }
                    printf("\n");
                    printf("%s", reader.line_content);
                    break;
                }
            }
        }

        // if (correct)
        // {
        //     sum += nums.ptr[(nums.len - 1) / 2];
        // }

        for (int i = 0; i < line.len; i++)
        {
            free(line.ptr[i]);
        }
        free_string_vec(&line);
        free_uint32_t_vec(&nums);
    }

    printf("%i\n", sum);

    for (int i = 0; i < rules.len; i++)
    {
        free_uint32_t_vec(&rules.ptr[i]);
    }
    free_uint32_tVector_vec(&rules);
    free_uint32_t_vec(&pagenums);

    drop_file(&reader);
}