#include <stdlib.h>
#include <stdio.h>
#include "ini.h"
#include "config_parser.h"
#include "annotations_parser.h"

int main()
{
    Configuration config;

    if (ini_parse("config.ini", iniHandler, &config) < 0)
    {
        printf("Can't load 'config.ini'\n");

        return 1;
    }
    printf("Test\n");

    annotations_parse("../../../MyClippings.txt", &config);

    return 0;
}
