#ifndef CONFIG_PARSER_H_INCLUDED
#define CONFIG_PARSER_H_INCLUDED
#include "stdio.h"
typedef struct Config
{
    char *parserPattern;
    char *separator;
    char title[2];
    char author[2];
    char position[2];
    char date[2];
    char comment[2];
} Config;

int configParse(Config *config, FILE *file);

#endif