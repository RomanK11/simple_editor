#ifndef FUNCS_H
#define FUNCS_H

#include <stddef.h>

int add_line(char ***buffer, size_t *line_count, const char *line);
int edit_line(char **buffer, size_t line_count, size_t indx, const char *new_text);
int insert_line(char ***buffer, size_t *line_count, size_t indx, const char *new_text);
int delete_line(char **buffer, size_t *line_count, size_t indx);
void free_buffer(char **buffer, size_t line_count);

#endif