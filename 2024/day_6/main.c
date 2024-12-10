#include "../../lib/inc/aoc_helper.h"

#define MSIZE 130

DEFINE_VEC_HEADER(uint8_t);
DEFINE_VEC(uint8_t);

typedef enum _dir
{
    left = 0b0001,
    right = 0b0010,
    up = 0b1000,
    down = 0b0100
} Dir;

Dir arr_to_enum(int *dir)
{

    int a = abs(dir[0]) << (2 + ((dir[0] + 1) / 2));
    int b = abs(dir[1]) << ((dir[1] + 1) / 2);

    return a | b;
}

bool inside_bounds(int y, int x)
{
    return y > -1 && y < MSIZE && x > -1 && x < MSIZE;
}

int main()
{
    FileReader reader = new_reader("day_6/input");
    string lines[MSIZE];
    int pos[] = {-1, -1};
    for (int i = 0; get_next_line(&reader); i++)
    {
        string line = malloc(MSIZE + 1);
        memcpy(line, reader.line_content, MSIZE);
        line[MSIZE] = '\0';
        for (int j = 0; j < MSIZE; j++)
        {
            if (line[j] == '^')
            {
                pos[0] = i;
                pos[1] = j;
            }
            if (line[j] == '.')
            {
                line[j] = 0;
            }
        }
        lines[i] = line;
    }

    int dir[] = {1, 0};
    int distinct = 1;
    lines[pos[0]][pos[1]] |= arr_to_enum(&dir);
    int sum = 0;
    while (inside_bounds(pos[0], pos[1]))
    {
        int y = pos[0] - dir[0];
        int x = pos[1] + dir[1];

        if (!inside_bounds(y, x))
        {
            break;
        }

        if (lines[y][x] == '#')
        {
            int sw = dir[1];
            dir[1] = dir[0];
            dir[0] = sw * -1;
        }
        else
        {
            bool circular = false;
            int sw = lines[y][x];
            lines[y][x] = '#';
            int tempdir[] = {dir[0], dir[1]};
            int tempmatrix[MSIZE][MSIZE] = {0};
            tempmatrix[pos[0]][pos[1]] |= arr_to_enum(&dir);
            while (pos[0] > -1 && pos[0] < MSIZE && pos[1] > -1 && pos[1] < MSIZE)
            {
                int ny = pos[0] - dir[0];
                int nx = pos[1] + dir[1];

                if (!inside_bounds(ny, nx))
                {
                    break;
                }
                int edir = arr_to_enum(&dir);

                if (lines[ny][nx] == '#')
                {
                    int sw = dir[1];
                    dir[1] = dir[0];
                    dir[0] = sw * -1;
                    int edir = arr_to_enum(&dir);

                    if ((tempmatrix[pos[0] - dir[0]][pos[1] + dir[1]] & edir) == edir)
                    {
                        circular = true;
                        break;
                    }
                }
                else
                {
                    pos[0] = ny;
                    pos[1] = nx;
                    tempmatrix[ny][nx] |= edir;
                }
            }

            if (circular)
            {
                // printf("%i: %i;%i\n", tempmatrix[pos[0] + dir[0]][pos[1] + dir[1]], pos[0] + dir[0], pos[1] + dir[1]);
                // for (int i = 0; i < MSIZE; i++)
                // {
                //     for (int j = 0; j < MSIZE; j++)
                //     {
                //         if (lines[i][j] == '#')
                //         {
                //             printf("# ");
                //         }
                //         else if (tempmatrix[i][j] == 0 && lines[i][j] == 0)
                //         {
                //             printf(". ");
                //         }
                //         else
                //         {
                //             printf("%i ", tempmatrix[i][j]);
                //         }
                //     }
                //     printf("\n");
                // }
                // printf("\n\n");
                // char a;
                sum += 1;
            }
            dir[0] = tempdir[0];
            dir[1] = tempdir[1];
            lines[y][x] = sw;
            if (sw == 0)
            {
                distinct++;
            }
            lines[y][x] |= arr_to_enum(&dir);
            pos[0] = y;
            pos[1] = x;
        }
    }

    printf("%i\n", sum);

    for (int i = 0; i < MSIZE; i++)
    {
        free(lines[i]);
    }

    drop_file(&reader);
}
