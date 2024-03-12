#ifndef LLIST_H__
#define LLIST_H__

#define LLIST_FORWARD       1
#define LLIST_BACKWARD      2

typedef struct llist_node_st {

    struct llist_node_st *prev;
    struct llist_node_st *next;
    char data[0];               // 为数据占位,引用时方便，直接 head.data

} llist_node_st;

// 采用面向对象的方法封装函数，对于结构体里面的函数指针的形参为什么采用 llist_head 定义，
// 因为 LLIST 是整个结构体的名字，机器还没识别，这时你用 LLIST 会不认识这个东西。
// create 就不能放进去，因为 create 会为其他函数赋值，但没人可以给 create 赋值，只能
// 像原来一样调用。
typedef struct llist_head {

    int size;
    llist_node_st head;
    int (*insert) (struct llist_head *, const void *, int);
    void *(*find) (struct llist_head *, const void *, int (*) (const void *, const void *));
    int (*delete) (struct llist_head *, const void *, int (*) (const void *, const void *));
    int (*fetch) (struct llist_head *, const void *, int (*) (const void *, const void *), void *data);
    void (*travel) (struct llist_head *, const void (*) (const void *));
    void (*destroy) (struct llist_head *);

} LLIST;

LLIST *llist_create (int initsize);

#endif