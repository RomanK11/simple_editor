#ifndef FUNCS_H
#define FUNCS_H

#include <stddef.h>

int add_line(char ***buffer, size_t *line_count, const char *line);
void free_buffer(char **buffer, size_t line_count);

#endif