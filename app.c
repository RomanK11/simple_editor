#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN   1024

#define DEFAULT "w+"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[1]);
        return 1;
    }

    static char buffer[MAX_LINES][MAX_LEN];
    int line_count = 0;

    FILE *f = fopen(argv[1], DEFAULT);
    
    if (f == NULL)
    {
        return 1;
    }
    
    while (1)
    {
        if (line_count >= MAX_LINES)
        {
            return -1;
        }
        char *b = fgets(buffer[line_count], MAX_LEN, stdin);

        if (b == NULL)
        {
            break;
        }

        size_t len = strlen(b);
        for (size_t i = 0; i < len; i++)
        {
            if (b[i] == '\n')
            {
                b[i] = '\0';
                break;
            }
        }
        
        if (strcmp(buffer[line_count], ":save") == 0)
        {
            for (int i = 0; i < line_count; i++)
            {
                fputs(buffer[i], f);
                fputc('\n', f);
            }
            memset(buffer, 0, line_count * sizeof(buffer[0]));
            line_count = 0;

            printf("saved\n");

            continue;
        }
        if (strcmp(buffer[line_count], ":quit") == 0)
        {
            break;
        }
        
        line_count++;
        // printf("%d\n", line_count); 
    }
    
    fclose(f);
    return 0;
}