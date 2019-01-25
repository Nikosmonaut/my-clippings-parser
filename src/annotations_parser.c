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
    regex_t regex;
    int reti;
    char msgbuf[100];
    size_t nmatch = 5;
    regmatch_t pmatch[5];

    printf("%s\n", annotation);
    printf("%s\n", config->parser_pattern);

    reti = regcomp(&regex, config->parser_pattern, 0);
    if (reti)
    {
        // fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, annotation, nmatch, pmatch, 0);
    if (!reti)
    {
        puts("Match");
    }
    else if (reti == REG_NOMATCH)
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
