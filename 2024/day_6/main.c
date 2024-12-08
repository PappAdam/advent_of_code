#include "../../lib/inc/aoc_helper.h"

#define MSIZE 10

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

    int a = 1 << (3 + ((dir[0] + 1) / 2));
    int b = 1 << ((dir[1] + 1) / 2);

    return a | b;
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
        }
        lines[i] = line;
    }

    int dir[] = {1, 0};
    int distinct = 1;
    lines[pos[0]][pos[1]] |= arr_to_enum(&dir);
    int sum = 0;
    while (pos[0] > -1 && pos[0] < MSIZE && pos[1] > -1 && pos[1] < MSIZE)
    {
        int y = pos[0] - dir[0];
        int x = pos[1] + dir[1];

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
            lines[y][x] = "#";
            int tempdir[] = {dir[0], dir[1]};
            while (pos[0] > -1 && pos[0] < MSIZE && pos[1] > -1 && pos[1] < MSIZE)
            {
                int ny = pos[0] - dir[0];
                int nx = pos[1] + dir[1];

                if (lines[ny][nx] == '#')
                {
                    int sw = dir[1];
                    dir[1] = dir[0];
                    dir[0] = sw * -1;
                }
                else
                {
                    int edir = arr_to_enum(&dir);
                    if (lines[ny][nx] | edir == edir || lines[ny][nx] | (edir << 4) == edir << 4)
                    {
                        circular = true;
                        break;
                    }

                    lines[ny][nx] |= edir;
                    pos[0] = ny;
                    pos[1] = nx;
                }
                for (int i = 0; i < MSIZE; i++)
                {
                    printf("%s\n", lines[i]);
                }
            }
            if (circular)
            {
                sum += 1;
            }
            dir[0] = tempdir[0];
            dir[1] = tempdir[1];
            lines[y][x] = sw;
            if (sw == 0)
            {
                distinct++;
            }
            lines[y][x] |= arr_to_enum(&dir) << 4;
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
