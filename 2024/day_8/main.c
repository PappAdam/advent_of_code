#include "../../lib/inc/aoc_helper.h"

#define MSIZE 50

bool inside_bounds(int y, int x)
{
    return y > -1 && y < MSIZE && x > -1 && x < MSIZE;
}

int main()
{
    FileReader reader = new_reader("day_8/input");

    uint64_t anode_count = 0;
    char matrix[MSIZE][MSIZE] = {0};
    char anode[MSIZE][MSIZE] = {0};
    for (int y = 0; get_next_line(&reader); y++)
    {
        for (int x = 0; x < MSIZE; x++)
        {
            if (reader.line_content[x] == '.')
            {
                matrix[y][x] = 0;
            }
            else
            {
                matrix[y][x] = reader.line_content[x];
            }
        }
    }

    for (int y = 0; y < MSIZE; y++)
    {
        for (int x = 0; x < MSIZE; x++)
        {
            char val = matrix[y][x];
            if (val != 0)
            {
                for (int sy = y; sy < MSIZE; sy++)
                {
                    int sx = 0;
                    if (sy == y)
                    {
                        sx = x + 1;
                    }
                    for (; sx < MSIZE; sx++)
                    {
                        if (matrix[sy][sx] != 0 && matrix[sy][sx] != '#' && matrix[sy][sx] == matrix[y][x])
                        {
                            int dy = sy - y;
                            int dx = sx - x;

                            int step_to_zero_y = y / dy;
                            int step_to_zero_x = x / dx;
                        }
                    }
                }
            }
        }
    }

    for (int y = 0; y < MSIZE; y++)
    {
        for (int x = 0; x < MSIZE; x++)
        {
            if (anode[y][x] == 0)
            {
                printf(".");
            }
            else
            {
                printf("%c", anode[y][x]);
            }
        }
        printf("\n");
    }

    printf("%i\n", anode_count);
}