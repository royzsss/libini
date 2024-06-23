#pragma once

#include "list.h"

typedef struct _ini_t {
    char filename[256];
    catelist *cateList;
} ini_t;
