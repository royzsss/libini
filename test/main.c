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

    if (parse_ini(it)) {
        printf("err: parse_ini\n");
        goto finish;
    }

    char value[128] = {0};
    if (get_value_str(it, "Armada", "none", value)) {
        printf("err: get_value_str\n");
        goto finish;
    }
    printf("[Armada]\n");
    printf("nonexclusive=%s\n", value);

    if (set_value(it, "Armada", "nonexclusive", "false")) {
        printf("err: set_value\n");
        goto finish;
    }
    memset(value, 0x0, sizeof(value));
    if (get_value_str(it, "Armada", "nonexclusive", value)) {
        printf("err: get_value_str\n");
        goto finish;
    }
    printf("[Armada]\n");
    printf("nonexclusive=%s\n", value);

    if (rewrite_ini(it)) {
        printf("err: rewrite_ini\n");
        goto finish;
    }

finish:
    if (it)
        ini_free(it);
    return 0;
}
