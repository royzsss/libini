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
    char *end = buf + strlen(buf) - 1;

    while (end > buf && ((unsigned char)*end == 0x0a || (unsigned char)*end == 0x0d))
        *end-- = '\0';
}

void process_blank(char buf[])
{
    char *start = buf;
    char *end = buf + strlen(buf) - 1;

    while (isspace((unsigned char)*start))
        start++;
    while (end > buf && isspace((unsigned char)*end))
        *end-- = '\0';

    if (start != buf)
        memmove(buf, start, (end - start + 2)); // +2为了将同时移动末尾的'\0'
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
