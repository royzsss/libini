#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"
#include "ini-def.h"

ini_t *ini_init(const char filename[])
{
    if (access(filename, F_OK))
        return NULL;

    ini_t *it = (ini_t *)malloc(sizeof(ini_t));
    memset(it, 0x0, sizeof(ini_t));

    strncpy(it->filename, filename, sizeof(it->filename) - 1);

    return it;
}

int parse_ini(ini_t *it)
{
    int ret = 0;
    char lineBuf[256] = {0};
    FILE *fp = NULL;

    fp = fopen(it->filename, "r");
    if (fp == NULL) {
        ret = -1;
        goto finish;
    }

    while (fgets(lineBuf, sizeof(lineBuf) - 1, fp)) {
    }

    ret = 0;
finish:
    if (fp)
        fclose(fp);
    return ret;
}

void ini_free(ini_t *it)
{
    if (it)
        free(it);

    return;
}
