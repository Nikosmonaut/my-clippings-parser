#ifndef CONFIG_PARSER_H_INCLUDED
#define CONFIG_PARSER_H_INCLUDED
#include "stdio.h"

typedef struct
{
    const char *parser_pattern;
    const char *separator;
    const char *title;
    const char *author;
    const char *position;
    const char *date;
    const char *comment;
} Configuration;

int iniHandler(void *user, const char *section, const char *name, const char *value);

#endif