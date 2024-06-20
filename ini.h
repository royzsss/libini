#pragma once

typedef struct _ini_t ini_t;

ini_t *ini_init(const char filename[]);
void parse_ini(ini_t *it);
void rewrite_ini(ini_t *it);
int get_value_int(ini_t *it, const char cate[], const char key[], int *value);
int get_value_str(ini_t *it, const char cate[], const char key[], char *value);
void ini_free(ini_t *it);
