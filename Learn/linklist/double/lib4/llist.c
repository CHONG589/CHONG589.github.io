#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

typedef struct llist_node_st {

    struct llist_node_st *prev;
    struct llist_node_st *next;
    char data[0];               // 为数据占位,引用时方便，直接 head.data

} llist_node_st;

struct llist_head_st {

    int size;
    llist_node_st head;

};

LLIST *llist_create (int initsize) {

    struct llist_head_st *new;
    new = malloc (sizeof (*new));
    if (new == NULL) {
        return NULL;
    }

    new -> size = initsize;
    new -> head.next = &new -> head;
    new -> head.prev = &new -> head;

    return new;
}

int llist_insert (LLIST *p, const void *data, int mode) {

    llist_node_st *newnode;
    struct llist_head_st *ptr = p;

    // 因为 data 域不是自己另外 malloc 了，而是在分配节点大小时一次性
    // 分配了，所以在分配节点时在 llist_node_st 节点大小的前提下，再加
    // 上数据域的大小。
    newnode = malloc (sizeof (*newnode) + ptr -> size);
    if (newnode == NULL) {
        return -1;
    }
    
    memcpy (newnode -> data, data, ptr -> size);

    if (mode == LLIST_FORWARD) {

        newnode -> next = ptr -> head.next;
        newnode -> prev  = &ptr -> head;

    } else if (mode == LLIST_BACKWARD) {

        newnode -> next = &ptr -> head;
        newnode -> prev = ptr -> head.prev;

    } else {
        return -3;
    }
    newnode -> next -> prev = newnode;
    newnode -> prev -> next = newnode;

    return 0;
}

static llist_node_st *find_ (struct llist_head_st *ptr, const void *key, int (*cmp) (const void *, const void *)) {

    llist_node_st *cur;
    for (cur = ptr -> head.next; cur != &ptr -> head; cur = cur -> next) {
        if (cmp (key, cur -> data) == 0) {
            break;
        }
    }
    return cur;

}

void *llist_find (LLIST *p, const void *key, int (*cmp) (const void *, const void *)) {

    llist_node_st *node;
    struct llist_head_st *ptr = p;
    node = find_ (ptr, key, cmp);
    if (node == &ptr -> head) {
        return NULL;
    }
    return node -> data;

}

int llist_delete (LLIST *p, const void *key, int (*cmp) (const void *, const void *)) {

    llist_node_st *node;
    struct llist_head_st *ptr = p;
    node = find_ (ptr, key, cmp);
    if (node == &ptr -> head) {
        return -1;
    }

    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    free (node);

    return 0;
}

int llist_fetch (LLIST *p, const void *key, int (*cmp) (const void *, const void *), void *data) {

    llist_node_st *node;
    struct llist_head_st *ptr = p;
    node = find_ (ptr, key, cmp);
    if (node == &ptr -> head) {
        return -1;
    }
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;

    if (data != NULL) {
        memcpy (data, node -> data, ptr -> size);
    }
    free (node);
    return 0;

}

void llist_travel (LLIST *p, const void (*op) (const void *)) {

    llist_node_st *cur;
    struct llist_head_st *ptr = p;
    for (cur = ptr -> head.next; cur != &ptr -> head; cur = cur -> next) {
        op (cur -> data);
    }

}

void llist_destroy (LLIST *p) {

    llist_node_st *cur, *next;
    struct llist_head_st *ptr = p;
    for (cur = ptr -> head.next; cur != &ptr -> head; cur = next) {
        next = cur -> next;
        free (cur);

    }
    free (ptr);
}