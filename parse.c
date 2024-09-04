#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "list.h"

static void process_comment(char buf[]);
static void process_special_char(char buf[]);
static void process_blank(char buf[]);

void process_line_buf(char buf[])
{
    process_comment(buf);
    process_special_char(buf);
    process_blank(buf);
}

void process_comment(char buf[])
{
    char comments[] = "#;";
    for (int i = 0; i < sizeof(comments); i++) {
        char *comment = strchr(buf, comments[i]);
        if (comment)
            memset(comment, 0x0, strlen(comment));
    }
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
    while (end > start && isspace((unsigned char)*end))
        *end-- = '\0';

    if (start != buf)
        memmove(buf, start, (end - start + 2)); // +2为了将同时移动末尾的'\0'
}

int check_line_content(char buf[], char category[], char key[], char value[])
{
    char start = buf[0], end = buf[strlen(buf) - 1];

    if (start == '[' && end == ']') { // category
        strncpy(category, buf + 1, strlen(buf + 1) - 1);
        category[strlen(category)] = '\0';
        return TYPE_CATEGORY;
    } else if (start != '=' && strchr(buf, '=')) { // key=value
        char *equal = strchr(buf, '=');
        strncpy(key, buf, equal - buf);
        key[strlen(key)] = '\0';
        process_blank(key);

        strncpy(value, equal + 1, VALUE_LEN - 1);
        value[strlen(value)] = '\0';
        process_blank(value);
        return TYPE_KEY_VALUE;
    } else
        return TYPE_ERROR;
}
