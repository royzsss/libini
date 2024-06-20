#pragma once

enum {
    TYPE_ERROR,
    TYPE_CATEGORY,
    TYPE_KEY_VALUE
};

void process_comment(char buf[]);
void process_special_char(char buf[]);
