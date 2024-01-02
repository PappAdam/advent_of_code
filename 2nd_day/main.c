#include "../readfile.h"
#include "../vector.h"
#include <stdbool.h>

typedef struct _cubes
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Cubes;

typedef struct _result
{
    uint8_t game_index;
    bool possible;
    size_t least_multiplied;
} Result;

Result parse_line(char *line)
{
    size_t len = strlen(line);

    Cubes cubes = {0, 0, 0};
    Cubes fewest_cubes = {0, 0, 0};

    bool found_game_index = false;
    bool cube_count_digit = false;
    uint32_t cube_count = 0;
    uint8_t game_index = 0;
    Result res = (Result){
        .game_index = game_index,
        .possible = true,
        .least_multiplied = 0};
    for (size_t i = 5; i < len; i++)
    {
        if (cubes.r > fewest_cubes.r)
        {
            fewest_cubes.r = cubes.r;
        }
        if (cubes.g > fewest_cubes.g)
        {
            fewest_cubes.g = cubes.g;
        }
        if (cubes.b > fewest_cubes.b)
        {
            fewest_cubes.b = cubes.b;
        }
        if (cubes.r > 12 || cubes.g > 13 || cubes.b > 14)
        {
            res.possible = false;
        }

        if (line[i] >= '0' && line[i] <= '9')
        {
            cube_count *= 10;
            cube_count += line[i] - 48;
        }

        if (line[i - 1] == ' ')
        {
            switch (line[i])
            {
            case 'r':
                cubes.r = cube_count;

                break;
            case 'b':
                cubes.b = cube_count;

                break;
            case 'g':
                cubes.g = cube_count;
                break;
            default:
                break;
            }
        }

        if (line[i] == ',' || line[i] == ';' || line[i] == ':')
        {
            cube_count = 0;
        }

        if (!found_game_index)
        {
            if (line[i] == ':')
            {
                found_game_index = true;
                continue;
            }

            game_index *= 10;
            game_index += line[i] - 48;
        }
    }

    res.game_index = game_index;
    res.least_multiplied = fewest_cubes.r * fewest_cubes.b * fewest_cubes.g;
    return res;
}

int main()
{
    FileReader reader = new_reader("input");
    char *line;
    size_t t1sum = 0;
    size_t t2sum = 0;
    while (line = get_next_line(&reader))
    {
        Result parsed_line = parse_line(line);
        if (parsed_line.possible)
        {
            t1sum += parsed_line.game_index;
        }
        t2sum += parsed_line.least_multiplied;
    }

    printf("task1: %i\n", t1sum);
    printf("task2: %i\n", t2sum);

    drop_file(&reader);
}