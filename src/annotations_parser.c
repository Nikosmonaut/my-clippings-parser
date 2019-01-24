#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "config_parser.h"
#include "annotations_parser.h"

static int readLine(char *line, FILE *file)
{
    int character;
    int pos = 0;
    int lineSize = DEFAULT_LINE_SIZE;
    line = (char *)malloc(DEFAULT_LINE_SIZE);

    character = fgetc(file);
    while (character != EOF && character != '\n')
    {
        if (pos >= lineSize - 1)
        {
            break;
            line = (char *)realloc(line, lineSize + DEFAULT_LINE_SIZE);
            if (line == NULL)
            {
                printf("Memory allocation failed");
                exit(1);
            }

            lineSize = lineSize + DEFAULT_LINE_SIZE;
        }

        line[pos] = character;
        pos++;
        character = fgetc(file);
    }

    printf("Good first line is :\n%s", line);
    return 0;
}

int annotations_parse(char *fileName, Configuration config)
{
    FILE *file;
    char *line = NULL;

    file = fopen(fileName, "r");

    if (!file)
    {
        perror("Could not open file");
    }

    readLine(line, file);

    free(line);
    fclose(file);

    return 0;
}
// int annotations_parse(char *fileName, Configuration config)
// {
//     char configLine[CONFIG_LINE_LENGTH];
//     regex_t regex;
//     int reti;
//     char msgbuf[100];

//     reti = regcomp(&regex, "(.*)=\"(.*)\"", 0);
//     if (reti)
//     {
//         fprintf(stderr, "Could not compile regex\n");
//         exit(1);
//     }

//     while (fgets(configLine, CONFIG_LINE_LENGTH, file) != NULL)
//     {
//         printf("Read line %s\n", configLine);
//         reti = regexec(&regex, configLine, 0, NULL, 0);
//         printf("reti : %d", reti);
//         if (!reti)
//         {
//             puts("Match");
//         }
//         else if (reti == REG_NOMATCH)
//         {
//             puts("No match");
//         }
//         else
//         {
//             regerror(reti, &regex, msgbuf, sizeof(msgbuf));
//             fprintf(stderr, "Regex match failed: %s\n", msgbuf);
//             exit(1);
//         }
//     }

//     regfree(&regex);

//     return 0;
// }
