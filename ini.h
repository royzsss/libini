#pragma once

typedef struct _ini_t ini_t;

ini_t *ini_init(const char filename[]);
void parse_ini(ini_t *it);
void pack_ini(ini_t *it);
int find_value_int(ini_t *it, const char key[]);
char *find_value_str(ini_t *it, const char key[]);
void ini_free(ini_t *it);
