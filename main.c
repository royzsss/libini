#include <stdio.h>
#include "ini.h"

int main()
{
    ini_t *it = NULL;

    it = ini_init("test.ini");
    ini_free(it);

    return 0;
}
