#include "readfile.h"

FileReader new_reader(const char *FILE_NAME)
{
    FILE *file = fopen(FILE_NAME, "r");

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    size_t line_max_lenght = 256;
    char *line_content = malloc(line_max_lenght);

    return (FileReader){
        .file = file,
        .file_size = file_size,
        .line_content = line_content,
        .line_max_lenght = line_max_lenght,
    };
}

char *get_next_line(FileReader *reader)
{
    reader->line_content = fgets(reader->line_content, reader->line_max_lenght, reader->file);
    if (!reader->line_content)
    {
        return NULL;
    }
    size_t len = strlen(reader->line_content);
    while (reader->line_content[len - 1] != '\n')
    {
        reader->line_max_lenght *= 2;
        reader->line_content = realloc(reader->line_content, reader->line_max_lenght);
        fseek(reader->file, -len, SEEK_CUR);
        reader->line_content = fgets(reader->line_content, reader->line_max_lenght, reader->file);
        len = strlen(reader->line_content);
    }

    return reader->line_content;
}

void drop_file(FileReader *reader)
{
    if (reader->file)
    {
        fclose(reader->file);
    }

    if (reader->line_content)
    {
        free(reader->line_content);
    }
}