#include <stdlib.h>
#include <stdio.h>
#include "config_parser.h"
#include "ini.h"

int main()
{
    Configuration config;

    if (ini_parse("config.ini", iniHandler, &config) < 0)
    {
        printf("Can't load 'config.ini'\n");

        return 1;
    }

    

    printf("Ok config parsed with\ntitle : %s", config.title);

    return 0;
}
