#include "../../lib/inc/aoc_helper.h"

bool correct_sequece(stringVector *mat, int x, int y, int xo, int yo, int iteration)
{
    if (mat->ptr[y + yo * iteration][x + xo * iteration] == "XMAS"[iteration])
    {
        if (iteration == 3)
        {
            return true;
        }
        return correct_sequece(mat, x, y, xo, yo, iteration + 1);
    }

    return false;
}

void p1(stringVector *mat);
void p2(stringVector *mat);

int main()
{
    FileReader reader = new_reader("day_4/input");

    stringVector mat = new_string_vec(140);
    while (get_next_line(&reader))
    {
        int len = strlen(reader.line_content);
        string line = malloc(len + 1);
        memcpy(line, reader.line_content, len + 1);
        push_string(&mat, line);
    }

    p2(&mat);

    for (int i = 0; i < mat.len; i++)
    {
        free(mat.ptr[i]);
    }

    free_string_vec(&mat);

    drop_file(&reader);
}

void p2(stringVector *mat)
{
    int sum = 0;
    for (int y = 4; y < mat->len - 4; y++)
    {
        for (int x = 4; x < mat->len - 4; x++)
        {
            if (mat->ptr[y][x] == 'A')
            {
                int i;
                for (i = -1; i <= 1; i += 2)
                {
                    if (!((mat->ptr[y + 1][x + i] == 'M' && mat->ptr[y - 1][x - i] == 'S') || (mat->ptr[y + 1][x + i] == 'S' && mat->ptr[y - 1][x - i] == 'M')))
                    {
                        break;
                    }
                }

                if (i > 1)
                {
                    sum += 1;
                }
            }
        }
    }

    printf("p2: %i\n", sum);
}

void p1(stringVector *mat)
{
    int sum = 0;
    int check_index = 0;
    for (int i = 4; i < mat->len - 4; i++)
    {
        for (int j = 4; j < mat->len - 4; j++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    sum += correct_sequece(mat, j, i, x, y, 0);
                }
            }
        }
    }

    printf("p1: %i\n", sum);
}