#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"
#include "ini-def.h"
#include "parse.h"
#include "list.h"

static void show_ini_list(ini_t *it);

ini_t *ini_init(const char filename[])
{
    if (access(filename, F_OK))
        return NULL;

    ini_t *it = (ini_t *)malloc(sizeof(ini_t));
    memset(it, 0x0, sizeof(ini_t));

    strncpy(it->filename, filename, sizeof(it->filename) - 1);

    return it;
}

int ini_parse(ini_t *it)
{
    int ret = 0;
    char lineBuf[256] = {0};
    FILE *fp = NULL;
    char cateCurrent[64] = {0};

    fp = fopen(it->filename, "r");
    if (fp == NULL) {
        ret = -1;
        goto finish;
    }

    while (fgets(lineBuf, sizeof(lineBuf) - 1, fp)) {
        process_line_buf(lineBuf);

        char category[64] = {0};
        char key[128] = {0}, value[128] = {0};
        int type = check_line_content(lineBuf, category, key, value);
        switch (type) {
        case TYPE_CATEGORY:
            insert_catelist(it, category);
            memset(cateCurrent, 0x0, sizeof(cateCurrent));
            strncpy(cateCurrent, category, sizeof(cateCurrent) - 1);
            break;
        case TYPE_KEY_VALUE:
            insert_key_value(it, cateCurrent, key, value);
            break;
        case TYPE_ERROR:
            break;
        }
    }

    // show_ini_list(it);

    ret = 0;
finish:
    if (fp)
        fclose(fp);
    return ret;
}

int ini_rewrite(ini_t *it)
{
    int ret = 0;
    FILE *fp = fopen(it->filename, "w");
    if (fp == NULL) {
        ret = -1;
        goto finish;
    }

    catelist *ctlist = it->cateList;
    kvlist *kvtlist = NULL;
    
    while (ctlist != NULL) {
        fprintf(fp,"[%s]\n", ctlist->category);
        kvtlist = ctlist->kvList;
        while (kvtlist != NULL) {
            fprintf(fp, "%s=%s\n", kvtlist->key, kvtlist->value);
            kvtlist = kvtlist->next;
        }
        fprintf(fp, "\n");
        ctlist = ctlist->next;
    }

    ret = 0;
finish:
    if (fp)
        fclose(fp);
    return ret;
}

int ini_get_value_int(ini_t *it, const char cate[], const char key[], int *value)
{
    catelist *cateTmpList = find_category(it, cate);
    if (cateTmpList == NULL)
        return -1;

    if (cateTmpList->kvList == NULL)
        return -1;

    kvlist *kvTmpList = cateTmpList->kvList;
    while (kvTmpList != NULL) {
        if (!strncmp(kvTmpList->key, key, KEY_LEN - 1)) {
            *value = atoi(kvTmpList->value);
            return 0;
        }
        kvTmpList = kvTmpList->next;
    }

    return -1;
}

int ini_get_value_str(ini_t *it, const char cate[], const char key[], char value[])
{
    catelist *cateTmpList = find_category(it, cate);
    if (cateTmpList == NULL)
        return -1;

    if (cateTmpList->kvList == NULL)
        return -1;

    kvlist *kvTmpList = cateTmpList->kvList;
    while (kvTmpList != NULL) {
        if (!strncmp(kvTmpList->key, key, KEY_LEN - 1)) {
            strncpy(value, kvTmpList->value, VALUE_LEN - 1);
            value[strlen(value)] = '\0';
            return 0;
        }
        kvTmpList = kvTmpList->next;
    }

    return -1;
}

int ini_set_value(ini_t *it, const char cate[], const char key[], const char value[])
{
    catelist *cateTmpList = find_category(it, cate);
    if (cateTmpList == NULL)
        return -1;

    if (cateTmpList->kvList == NULL)
        return -1;

    kvlist *kvTmpList = cateTmpList->kvList;
    while (kvTmpList != NULL) {
        if (!strncmp(kvTmpList->key, key, KEY_LEN - 1)) {
            memset(kvTmpList->value, 0x0, sizeof(kvTmpList->value));
            strncpy(kvTmpList->value, value, sizeof(kvTmpList->value) - 1);
            return 0;
        }
        kvTmpList = kvTmpList->next;
    }

    return -1;
}

void ini_free(ini_t *it)
{
    if (it == NULL)
        return;

    catelist *cateTmpList = it->cateList;
    while (cateTmpList != NULL) {
        kvlist *kvTmpList = cateTmpList->kvList;
        while (kvTmpList != NULL) {
            kvlist *kvFreeList = kvTmpList;
            kvTmpList = kvTmpList->next;
            free(kvFreeList);
        }
        catelist *cateFreeList = cateTmpList;
        cateTmpList = cateTmpList->next;
        free(cateFreeList);
    }

    free(it);
    return;
}

void show_ini_list(ini_t *it)
{
    catelist *ctlist = it->cateList;
    kvlist *kvtlist = NULL;
    
    while (ctlist != NULL) {
        printf("[%s]\n", ctlist->category);
        kvtlist = ctlist->kvList;
        while (kvtlist != NULL) {
            printf("%s=%s\n", kvtlist->key, kvtlist->value);
            kvtlist = kvtlist->next;
        }
        printf("\n");
        ctlist = ctlist->next;
    }
}
