#include <stdio.h>
#include <string.h>
#include "ini.h"

int main()
{
    ini_t *it = ini_init("ddraw.ini");
    if (it == NULL) {
        printf("err: ini_init\n");
        goto finish;
    }

    if (ini_parse(it)) {
        printf("err: parse_ini\n");
        goto finish;
    }

    if (ini_set_value(it, "Armada", "nonexclusive", "true")) {
        printf("err: ini_set_value\n");
        goto finish;
    }

    char value[128] = {0};
    if (ini_get_value_str(it, "Armada", "nonexclusive", value)) {
        printf("err: ini_get_value_str\n");
        goto finish;
    }
    printf("[Armada]\n");
    printf("nonexclusive=%s\n", value);

    if (ini_set_value(it, "Armada", "nonexclusive", "false")) {
        printf("err: ini_set_value\n");
        goto finish;
    }
    memset(value, 0x0, sizeof(value));
    if (ini_get_value_str(it, "Armada", "nonexclusive", value)) {
        printf("err: ini_get_value_str\n");
        goto finish;
    }
    printf("[Armada]\n");
    printf("nonexclusive=%s\n", value);

    if (ini_rewrite(it)) {
        printf("err: rewrite_ini\n");
        goto finish;
    }

finish:
    if (it)
        ini_free(it);
    return 0;
}
