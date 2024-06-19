#pragma once

typedef struct _catelist {
    char category[64];
    struct _catelist *next;
} catelist;

typedef struct _kvlist {
    char key[128];
    char value[128];
    struct _kvlist *next;
} kvlist;

typedef struct _ini_t {
    char filename[256];
    catelist *cateList;
} ini_t;
