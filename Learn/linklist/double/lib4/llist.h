#ifndef LLIST_H__
#define LLIST_H__

#define LLIST_FORWARD       1
#define LLIST_BACKWARD      2

// typedef struct llist_head_st LLIST; 用 void 来代替 struct llist_head_st ，因为 llist.c 你是不给
// 其他人看的，所以你在实现函数的里面，将用到 LLIST(即 void) 再强转回 struct llist_head_st 来，这样就
// 不影响了。
typedef void LLIST;

LLIST *llist_create (int initsize);

int llist_insert (LLIST *, const void *, int mode);

void *llist_find (LLIST *, const void *, int (*) (const void *, const void *));

int llist_delete (LLIST *, const void *, int (*) (const void *, const void *));

int llist_fetch (LLIST *, const void *, int (*) (const void *, const void *), void *data);

void llist_travel (LLIST *, const void (*) (const void *));

void llist_destroy (LLIST *);

#endif