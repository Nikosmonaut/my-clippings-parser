#include <stdlib.h>
#include <stdio.h>
#include "config_parser.h"

int main()
{
    FILE *configFile;
    Config *config = NULL;

    configFile = fopen("config", "r");
    if (configFile == NULL)
    {
        perror("config");
        exit(EXIT_FAILURE);
    }

    configParse(config, configFile);

    fclose(configFile);
    //readFile of clippings or get them from stdin
    //parseFile
    return 0;
}
