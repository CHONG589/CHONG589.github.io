#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE    32

typedef struct score_st {

    int id;
    char name[NAMESIZE];
    int math;
    int chinese;

} score_st;

static void print_s (const void *record) {

    const score_st *r = record;
    printf ("%d %s %d %d\n", r -> id, r -> name, r -> math, r -> chinese);

}

static int id_cmp (const void *key, const void *record) {

    const int *k = key;
    const score_st *r = record;
    
    return ((*k) - (r -> id));      // 相减等于 0 为成功

}

static int name_cmp (const void *key, const void *record) {

    const char *k = key;
    const score_st *r = record;

    // 返回 0 说明成功
    return strcmp (k, r -> name);

}

int main () {

    LLIST *handler;
    score_st tmp;
    int i, ret;

    // create 的形参 score_st 的大小就为 size, size 记录的是
    // *data 的大小，因为在后面创建一个节点时不仅要为节点分配
    // 内存,还需要分配内存给 data, 大小由 main 中传过去。
    handler = llist_create (sizeof (score_st));
    if (handler == NULL) {
        exit (1);
    }

    for (i = 0; i < 7; i++) {
        tmp.id = i;
        snprintf (tmp.name, NAMESIZE, "std%d", i);
        tmp.math = rand () % 100;
        tmp.chinese = rand () % 100;

        ret = llist_insert (handler, &tmp, LLIST_BACKWARD);
        if (ret){
            exit (1);
        }
    }

    llist_travel (handler, print_s);

    printf ("\n");

    // int id = 30;
    // score_st *data;
    // data = llist_find (handler, &id, id_cmp);
    // if (data == NULL) {
    //     printf ("Can not find!\n");
    // } else {
    //     print_s (data);
    // }

    char *del_name = "std10";
    ret = llist_delete (handler, del_name, name_cmp);
    if (ret) {
        printf ("llist_delete failed!\n");
    } else {
        llist_travel (handler, print_s);
    }

    llist_destroy (handler);

    exit (0);
}