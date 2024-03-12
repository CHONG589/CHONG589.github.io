#ifndef LLIST_H__
#define LLIST_H__

#define LLIST_FORWARD       1
#define LLIST_BACKWARD      2

typedef struct llist_node_st {

    struct llist_node_st *prev;
    struct llist_node_st *next;
    char data[0];               // 为数据占位,引用时方便，直接 head.data

} llist_node_st;

typedef struct {

    int size;
    llist_node_st head;

} LLIST;

LLIST *llist_create (int initsize);

int llist_insert (LLIST *, const void *, int mode);

void *llist_find (LLIST *, const void *, int (*) (const void *, const void *));

int llist_delete (LLIST *, const void *, int (*) (const void *, const void *));

int llist_fetch (LLIST *, const void *, int (*) (const void *, const void *), void *data);

void llist_travel (LLIST *, const void (*) (const void *));

void llist_destroy (LLIST *);

#endif