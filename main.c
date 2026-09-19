#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcs.h"

#define MAX_LEN 1024

#define DEFAULT "r+"
#define CREATE "w+"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char **buffer = NULL;
    char temp[MAX_LEN];
    size_t line_count = 0;

    FILE *f = fopen(argv[1], DEFAULT);
    
    if (f == NULL)
    {
        f = fopen(argv[1], CREATE);
    }
    
    if (f == NULL)
    {
        perror("fopen");
        return 1;
    }
    
    while (1)
    {
        char *t = fgets(temp, MAX_LEN, stdin);

        if (t == NULL)
        {
            break;
        }

        temp[strcspn(temp, "\n")] = '\0';

        int res = add_line(&buffer, &line_count, temp);
        if (res == 1)
        {
            return 1;
        }
        
        
        if (strcmp(buffer[line_count - 1], ":save") == 0)
        {
            for (size_t i = 0; i < line_count - 1; i++)
            {
                fputs(buffer[i], f);
                fputc('\n', f);
            }
            free_buffer(buffer, line_count);
            buffer = NULL;
            line_count = 0;

            printf("saved\n");

            continue;
        }
        if (strcmp(buffer[line_count - 1], ":quit") == 0)
        {
            free_buffer(buffer, line_count);
            break;
        }
    }
    
    fclose(f);
    return 0;
}

