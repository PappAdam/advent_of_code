#ifndef FILEHANDLER
#define FILEHANDLER

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct _FileReader
{
    FILE *file;
    size_t file_size;
    char *line_content;
    size_t line_max_lenght;
} FileReader;

FileReader new_reader(const char *FILE_NAME);
char *get_next_line(FileReader *file_handler);
void drop_file(FileReader *file_handler);

#endif
