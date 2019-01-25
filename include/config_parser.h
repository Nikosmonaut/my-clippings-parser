#ifndef CONFIG_PARSER_H_INCLUDED
#define CONFIG_PARSER_H_INCLUDED
#include "stdio.h"

typedef struct
{
    char *parser_pattern;
    char *separator;
    char *title;
    char *author;
    char *position;
    char *date;
    char *comment;
} Configuration;

/**
 *  Configuration struct hydrator according to inih
 */
int iniHandler(void *user, const char *section, const char *name, const char *value);

#endif