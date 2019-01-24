#ifndef ANNOTATIONS_PARSER_H_INCLUDED
#define ANNOTATIONS_PARSER_H_INCLUDED

#include "config_parser.h"

#define DEFAULT_LINE_SIZE 40

typedef struct
{
    const char *title;
    const char *author;
    const char *position;
    const char *date;
    const char *comment;
} Annotation;

int annotations_parse(char *fileName, Configuration config);

#endif