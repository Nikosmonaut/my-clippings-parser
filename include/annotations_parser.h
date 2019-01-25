#ifndef ANNOTATIONS_PARSER_H_INCLUDED
#define ANNOTATIONS_PARSER_H_INCLUDED

#include "config_parser.h"

#define MAX_LINE_LENGTH 1024

typedef struct
{
    const char *title;
    const char *author;
    const char *position;
    const char *date;
    const char *comment;
} Annotation;

/**
 * Parse annotations text file
 * @param fileName file to parse
 * @params config configuration to handle parsing
 */
int annotations_parse(char *fileName, Configuration *config);

#endif