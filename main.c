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

    while (fgets(temp, MAX_LEN, f) != NULL)
    {
        temp[strcspn(temp, "\n")] = '\0';

        for (size_t i = 0; i < strlen(temp); i++)
        {
            printf("%c", temp[i]);
        }
        printf("\n");
        
        
        //add_line
        if (add_line(&buffer, &line_count, temp) != 0)
        {
            fprintf(stderr, "Failed to add line\n");
            free_buffer(buffer, line_count);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    f = NULL;
    
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
            free_buffer(buffer, line_count);
            return 1;
        }   
        
        if (strcmp(buffer[line_count - 1], ":save") == 0)
        {
            FILE *save_file = fopen(argv[1], "w");

            if (save_file == NULL)
            {
                free_buffer(buffer, line_count);
                perror("fopen");
                return 1;
            }

            for (size_t i = 0; i < line_count - 1; i++)
            {
                fputs(buffer[i], save_file);
                fputc('\n', save_file);
            }

            fclose(save_file);

            printf("saved\n");
            continue;
        }
        if (strcmp(buffer[line_count - 1], ":quit") == 0)
        {
            free_buffer(buffer, line_count);
            break;
        }
    }
    
    return 0;
}

