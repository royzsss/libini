#pragma once

enum {
    TYPE_ERROR,
    TYPE_CATEGORY,
    TYPE_KEY_VALUE
};

void process_line_buf(char buf[]);
int check_line_content(char buf[], char category[], char key[], char value[]);
