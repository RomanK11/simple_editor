#include "funcs.h"

#include <stdlib.h>
#include <string.h>

int add_line(char ***buffer, size_t *line_count, const char *line)
{
    char **new_buffer = realloc(*buffer, (*line_count + 1) * sizeof(*new_buffer));
    if (new_buffer == NULL)
    {
        return 1;
    }

    *buffer = new_buffer;

    (*buffer)[*line_count] = malloc(strlen(line) + 1);

    if ((*buffer)[*line_count] == NULL)
    {
        return 1;
    }

    strcpy((*buffer)[*line_count], line);
    (*line_count)++;

    return 0;
}
void free_buffer(char **buffer, size_t line_count)
{
    for (size_t i = 0; i < line_count; i++)
    {
        free(buffer[i]);
    }

    free(buffer);
}