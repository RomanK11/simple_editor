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

int edit_line(char **buffer, size_t line_count, size_t indx, const char *new_text)
{
    if (indx >= line_count)
    {
        return 1;
    }
    
    char *new_line = malloc(strlen(new_text) + 1);

    if (new_line == NULL)
    {
        return 1;
    }
    
    strcpy(new_line, new_text);
    free(buffer[indx]);
    buffer[indx] = new_line;

    return 0;
}

int insert_line(char ***buffer, size_t *line_count, size_t indx, const char *new_text)
{
    if (indx > *line_count)
    {
        return 1;
    }

    char *new_line = malloc(strlen(new_text) + 1);

    if (new_line == NULL)
    {
        return 1;
    }

    strcpy(new_line, new_text);

    char **new_buffer = realloc(
        *buffer,
        (*line_count + 1) * sizeof(*new_buffer)
    );

    if (new_buffer == NULL)
    {
        free(new_line);
        return 1;
    }

    *buffer = new_buffer;

    for (size_t i = *line_count; i > indx; i--)
    {
        (*buffer)[i] = (*buffer)[i - 1];
    }

    (*buffer)[indx] = new_line;
    (*line_count)++;

    return 0;
}

int delete_line(char **buffer, size_t *line_count, size_t indx)
{
    if (indx >= *line_count)
    {
        return 1;
    }

    char *to_free = buffer[indx];

    for (size_t i = indx; i < *line_count - 1; i++)
    {
        buffer[i] = buffer[i + 1];
    }
    
    free(to_free);
    (*line_count)--;

    buffer[*line_count] = NULL;

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