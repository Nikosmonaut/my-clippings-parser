#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "config_parser.h"
#include "ini.h"

static char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if (dup)
    {
        strcpy(dup, str);
    }

    return dup;
}

int iniHandler(void *user, const char *section, const char *name, const char *value)
{
    Configuration *pconfig = (Configuration *)user;

    if (strcmp(name, "parser_pattern") == 0)
    {
        pconfig->parser_pattern = strdup(value);
    }
    else if (strcmp(name, "separator") == 0)
    {
        pconfig->separator = strdup(value);
    }
    else if (strcmp(name, "title") == 0)
    {
        pconfig->title = strdup(value);
    }
    else if (strcmp(name, "author") == 0)
    {
        pconfig->author = strdup(value);
    }
    else if (strcmp(name, "position") == 0)
    {
        pconfig->position = strdup(value);
    }
    else if (strcmp(name, "date") == 0)
    {
        pconfig->date = strdup(value);
    }
    else if (strcmp(name, "comment") == 0)
    {
        pconfig->comment = strdup(value);
    }
    else
    {
        return 0; /* unknown section/name, error */
    }
    return 1;
}

// int configParse(Config *config, FILE *file)
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