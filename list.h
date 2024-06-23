#pragma once

#define CATE_LEN    64
#define KEY_LEN     128
#define VALUE_LEN   128

typedef struct _ini_t ini_t;

typedef struct _kvlist {
    char key[KEY_LEN];
    char value[VALUE_LEN];
    struct _kvlist *next;
} kvlist;

typedef struct _catelist {
    char category[CATE_LEN];
    kvlist *kvList;
    struct _catelist *next;
} catelist;

void insert_catelist(ini_t *it, const char category[]);
void insert_key_value(ini_t *it, const char category[], const char key[], const char value[]);
catelist *find_category(ini_t *it, const char category[]);
