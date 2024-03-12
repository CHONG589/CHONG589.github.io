#ifndef LLIST_H__
#define LLIST_H__

#define LLIST_FORWARD       1
#define LLIST_BACKWARD      2

typedef void llist_op (const void *);

typedef int llist_cmp (const void *, const void *);      // 这个比较函数会把比较的结果：如不匹配等结果返回来，所以用返回值 int

// 用 void * ，不论用户存什么类型都可以百搭
typedef struct llist_node_st {
    
    void *data;
    struct llist_node_st *prev;
    struct llist_node_st *next;

} llist_node_st;

typedef struct {

    int size;
    struct llist_node_st head;

} LLIST;
// 这个结构相当于
// typedef struct {

//     int size;
//     llist_node_st head;

// } LLIST;

LLIST *llist_create (int initsize);

// mode 表示插入的形式
int llist_insert (LLIST *, const void *data, int mode);

// 最好是把找到的数据交给用户，而不是用 int 返回值判断错误，把返回的数据给用户，让他自己判断找没找到
void *llist_find (LLIST *, const void *key, llist_cmp *);            

int llist_delete (LLIST *, const void *key, llist_cmp *);

// 抓取，与 delete 的区别为只是拿信息，不从表中删掉。
int llist_fetch (LLIST *, const void *key, llist_cmp *, void *data);         

// llist_op * 相当于 void (*) (const void *);
void llist_travel (LLIST *, llist_op *);            

void llist_destroy (LLIST *);

#endif