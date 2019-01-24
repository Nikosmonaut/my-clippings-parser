#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "config_parser.h"

#define CONFIG_LINE_LENGTH 100
#define MAX_ERROR_MESSAGE 0x1000

static int compile_regex(regex_t *r, const char *regex_text)
{
}

int configParse(Config *config, FILE *file)
{
    char ch;
    char configLine[CONFIG_LINE_LENGTH];
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char

        reti = regcomp(&regex, "(.*)=\"(.*)\"", 0);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (fgets(configLine, CONFIG_LINE_LENGTH, file) != NULL)
    {
        printf("Read line %s\n", configLine);
        reti = regexec(&regex, configLine, 0, NULL, 0);
        printf("reti : %d", reti);
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
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    regfree(&regex);

    return 0;
}