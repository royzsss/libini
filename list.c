#include <stdlib.h>
#include <string.h>
#include "ini-def.h"
#include "list.h"

void insert_catelist(ini_t *it, const char category[])
{
    if (it->cateList == NULL) {
        it->cateList = (catelist *)malloc(sizeof(catelist));
        memset(it->cateList, 0x0, sizeof(catelist));
        strncpy(it->cateList->category, category, CATE_LEN - 1);
        return;
    }

    catelist *tlist = it->cateList;
    while (tlist->next != NULL)
        tlist = tlist->next;
    tlist->next = (catelist *)malloc(sizeof(catelist));
    memset(tlist->next, 0x0, sizeof(catelist));
    strncpy(tlist->next->category, category, CATE_LEN - 1);
    return;
}

void insert_key_value(ini_t *it, const char category[], const char key[], const char value[])
{
    catelist *ctlist = find_category(it, category);
    if (ctlist == NULL)
        return;

    if (ctlist->kvList == NULL) {
        ctlist->kvList = (kvlist *)malloc(sizeof(kvlist));
        memset(ctlist->kvList, 0x0, sizeof(kvlist));
        strncpy(ctlist->kvList->key, key, KEY_LEN - 1);
        strncpy(ctlist->kvList->value, value, VALUE_LEN - 1);
        return;
    }

    kvlist *kvtlist = ctlist->kvList;
    while (kvtlist->next != NULL)
        kvtlist = kvtlist->next;
    kvtlist->next = (kvlist *)malloc(sizeof(kvlist));
    memset(kvtlist->next, 0x0, sizeof(kvlist));
    strncpy(kvtlist->next->key, key, KEY_LEN - 1);
    strncpy(kvtlist->next->value, value, VALUE_LEN - 1);
    return;
}

catelist *find_category(ini_t *it, const char category[])
{
    catelist *tlist = it->cateList;
    while (tlist != NULL) {
        if (!strncmp(tlist->category, category, CATE_LEN - 1))
            return tlist;
        tlist = tlist->next;
    }

    return NULL;
}
