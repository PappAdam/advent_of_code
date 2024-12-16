#include "../../lib/inc/aoc_helper.h"

#define MSIZE 50

bool inside_bounds(int y, int x)
{
    return y >= 0 && y < MSIZE && x >= 0 && x < MSIZE;
}

char matrix[MSIZE][MSIZE] = {0};
char anode[MSIZE][MSIZE] = {0};

int main()
{
    FileReader reader = new_reader("day_8/input");

    uint64_t anode_count = 0;
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

                            int ay = y - dy;
                            int ax = x - dx;
                            printf("%i, %i\n", dy, dx);
                            while (inside_bounds(ay, ax))
                            {
                                if (anode[ay][ax] == 0)
                                {
                                    anode[ay][ax] = '#';
                                    anode_count++;
                                }

                                ay -= dy;
                                ax -= dx;
                            }

                            ay = y;
                            ax = x;
                            while (inside_bounds(ay, ax))
                            {
                                if (anode[ay][ax] == 0)
                                {
                                    anode[ay][ax] = '#';
                                    anode_count++;
                                }

                                ay += dy;
                                ax += dx;
                            }
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
            if (matrix[y][x] == 0 && anode[y][x] == 0)
            {
                printf(".");
            }
            else if (matrix[y][x])
            {
                printf("%c", matrix[y][x]);
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