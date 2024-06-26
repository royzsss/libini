#pragma once

typedef struct _ini_t ini_t;

ini_t *ini_init(const char filename[]);
int ini_parse(ini_t *it);
int ini_rewrite(ini_t *it);
int ini_get_value_int(ini_t *it, const char cate[], const char key[], int *value);
int ini_get_value_str(ini_t *it, const char cate[], const char key[], char value[]);
int ini_set_value(ini_t *it, const char cate[], const char key[], const char value[]);
void ini_free(ini_t *it);
