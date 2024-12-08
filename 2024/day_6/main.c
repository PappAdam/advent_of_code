#include "../../lib/inc/aoc_helper.h"

#define MSIZE 130

int main()
{
    FileReader reader = new_reader("day_6/input");
    string lines[MSIZE];
    int pos[] = {-1, -1};
    for (int i = 0; get_next_line(&reader); i++)
    {
        string line = malloc(MSIZE);
        memcpy(line, reader.line_content, MSIZE);
        for (int j = 0; pos[0] == -1 && j < MSIZE; j++)
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
    lines[pos[0]][pos[1]] = 'X';
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
            if (lines[y][x] != 'X')
            {
                distinct++;
                lines[y][x] = 'X';
            }
            pos[0] = y;
            pos[1] = x;
        }
    }

    printf("%i\n", distinct - 1);

    for (int i = 0; i < MSIZE; i++)
    {
        free(lines[i]);
    }

    drop_file(&reader);
}