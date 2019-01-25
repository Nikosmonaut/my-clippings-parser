#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "config_parser.h"
#include "annotations_parser.h"

char *readLine(FILE *file)
{
    int character;
    int pos = 0;
    int lineSize = DEFAULT_LINE_SIZE;
    char *line = malloc(DEFAULT_LINE_SIZE + 1);

    character = fgetc(file);
    while (character != EOF && character != '\n')
    {
        if (character == '\r')
        {
            fgetc(file);
            break;
        }
        if (pos >= lineSize - 1)
        {
            line = realloc(line, lineSize + DEFAULT_LINE_SIZE + 1);
            if (line == NULL)
            {
                printf("Memory allocation failed");
                exit(1);
            }

            lineSize = lineSize + DEFAULT_LINE_SIZE;
        }

        printf("Char %c\n", character);
        line[pos] = character;
        pos++;
        character = fgetc(file);
    }

    line[pos] = '\0';

    return line;
}

char *readAnnotation(FILE *file, char *separator)
{
    char *annotation = NULL;
    char *line = NULL;
    int lineLength;
    int annotationLength;

    line = readLine(file);
    printf("La ligne: %s\n", line);

    while (EOF && line != NULL && strcmp(line, separator) != 0)
    {
        lineLength = (line != NULL) ? strlen(line) + 1 : 1;
        annotationLength += lineLength;

        annotation = realloc(annotation, annotationLength);
        strncat(annotation, line, lineLength);
        printf("Annotation : %s\n", annotation);
        free(line);
        line = NULL;
        line = readLine(file);
        printf("La ligne : %s\n", line);
    }

    return annotation;
}

int annotations_parse(char *fileName, Configuration *config)
{
    FILE *file;
    char *annotation = NULL;

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        perror("Could not open file");
        return 1;
    }

    annotation = readAnnotation(file, config->separator);

    printf("Annotation : %s\n", annotation);

    if (annotation != NULL)
    {
        free(annotation);
        annotation = NULL;
    }

    // fclose(file);
    // file = NULL;

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
