#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "config_parser.h"
#include "annotations_parser.h"

char *read_annotation(FILE *file, char *separator)
{
    char *annotation = '\0';
    char *line = malloc(MAX_LINE_LENGTH);
    int lineLength = 0;
    int annotationLength;
    int separatorLenght = strlen(separator);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL && strncmp(line, separator, separatorLenght) != 0)
    {
        lineLength = strlen(line) + 1;
        annotationLength += lineLength;

        annotation = realloc(annotation, annotationLength);
        if (annotation == NULL)
        {
            perror("Could not realloc space");
            exit(1);
        }
        strncat(annotation, line, lineLength);
    }

    return annotation;
}

int parse_annotation(char *annotation, Configuration *config)
{
    int status;
    char msgbuf[100];
    regex_t regex;
    size_t maxGroups = 7;
    regmatch_t groupList[7];

    printf("%s", annotation);
    printf("%s\n", config->parser_pattern);

    if (regcomp(&regex, config->parser_pattern, REG_NEWLINE | REG_EXTENDED) != 0)
    {
        perror("Could not compile regex\n");
        exit(1);
    }

    status = regexec(&regex, annotation, maxGroups, groupList, 0);
    if (!status)
    {
        for (unsigned int i = 0; i < maxGroups; i++)
        {
            if (groupList[i].rm_so == (size_t)-1)
                break; // No more groups

            char sourceCopy[strlen(annotation) + 1];
            strcpy(sourceCopy, annotation);
            sourceCopy[groupList[i].rm_eo] = 0;
            printf("Group %u: [%2u-%2u]: %s\n",
                   i, groupList[i].rm_so, groupList[i].rm_eo,
                   sourceCopy + groupList[i].rm_so);
        }
    }
    else if (status == REG_NOMATCH)
    {
        puts("No match");
    }
    else
    {
        // regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        // fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);

    return 0;
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

    annotation = read_annotation(file, config->separator);
    parse_annotation(annotation, config);

    if (annotation != NULL)
    {
        free(annotation);
        annotation = NULL;
    }

    fclose(file);
    file = NULL;

    return 0;
}
