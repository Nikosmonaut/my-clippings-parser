#include <stdio.h>
#include <stdlib.h>
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

