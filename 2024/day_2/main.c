#include "../../lib/inc/aoc_helper.h"

bool correnct_sequence(int elem, int last_element, int inc)
{
    return ((elem - last_element) * inc > 0 && abs(last_element - elem) < 4 && last_element != elem);
}

int main()
{
    FileReader reader = new_reader("day_2/input");

    int safe_count = 0;
    while (
        get_next_line(&reader))
    {
        stringVector line = split_string_by(reader.line_content, ";");
        int last_element = to_int(line.ptr[0]);
        int inc = to_int(line.ptr[1]) - last_element;
        uint8_t safe = 1;
        for (int i = 1; i < line.len; i++)
        {
            int elem = to_int(line.ptr[i]);
            if (!correnct_sequence(elem, last_element, inc))
            {
                if ((i > 2 && !correnct_sequence(elem, to_int(line.ptr[i - 2]), inc)))
                {
                    safe = 0;
                    break;
                }
            }

            last_element = elem;
        }
        safe_count += safe;
        for (int i = 1; i < line.len; i++)
        {
            free(line.ptr[i]);
        }

        free(line.ptr);
    }

    printf("%i\n", safe_count);

    drop_file(&reader);
}
