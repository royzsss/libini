#include <string.h>
#include "parse.h"

void process_comment(char buf[])
{
    char *comment = strchr(buf, '#');
    if (comment)
        memset(comment, 0x0, strlen(comment));
}

void process_special_char(char buf[])
{
    int buflen = strlen(buf);

    char *tmp = (char *)malloc(buflen + 1);
    memset(tmp, 0x0, buflen + 1);

    strcpy(tmp, buf);
    memset(buf, 0x0, buflen);

    for (int i = 0, j = 0; i < buflen; i++)
        if (tmp[i] != 0x0a || tmp[i] != 0x0d || tmp[i] != 0x20)
            buf[j++] = tmp[i];

    free(tmp);
}

int check_line_content(char buf[], char category[], char key[], char value[])
{
    char start = buf[0], end = buf[strlen(buf) - 1];

    if (start == '[' && end == ']') { // category
        memset(category, 0x0, strlen(category));
        strncpy(category, buf + 1, strlen(buf + 1) - 1);
        return TYPE_CATEGORY;
    } else if (start != '=' && end != '=' && strchr(buf, '=')) { // key=value
        char *equal = strchr(buf, '=');
        strncpy(key, buf, equal - buf);
        strcpy(value, equal + 1);
        return TYPE_KEY_VALUE;
    } else
        return TYPE_ERROR;
}
