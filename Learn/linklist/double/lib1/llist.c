#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

LLIST *llist_create (int initsize) {

    LLIST *new;

    new = malloc (sizeof (*new));
    if (new == NULL) {
        return NULL;
    }

    new -> size = initsize;
    new -> head.data = NULL;

    // new 为头节点的结构，包含了 size 的结构，而后面的有效节点的结构是采用 head 的结构
    //（即 llist_node_st）,在循环链表中，尾节点指向头节点时，不是直接指向 new, 因为后面的节点
    // 的结构和头节点的结构不一样（head -> next 也不能指向 new , 类型不一样），所以为采取同一
    // 结构, 再用地址指向时采用 &(new -> head);
    // new -> hean 是一个变量，所以要指向 new -> head，在前面要取地址符号，这里可以从结构定义
    // 那里可以看出定义 head 是变量，而采用指针形式才是地址，才可以直接赋值给地址，如
    // new -> head.next = &(new -> head) 中，new -> head.next 中的 next 定义时是采用的指针
    // 形式
    new -> head.prev = &(new -> head);      // new -> head 为变量，所以要加地址符号
    new -> head.next = &(new -> head);

    return new;
}

int llist_insert (LLIST *ptr, const void *data, int mode) {

    llist_node_st *newnode;

    newnode = malloc (sizeof (*newnode));
    if (newnode == NULL) {
        return -1;
    }

    newnode -> data = malloc (ptr -> size);
    if (newnode -> data == NULL) {
        return -2;
    }

    memcpy (newnode -> data, data, ptr -> size);

    if (mode == LLIST_FORWARD) {

        newnode -> prev = &(ptr -> head);
        newnode -> next = ptr -> head.next;
        newnode -> prev -> next = newnode;
        newnode -> next -> prev = newnode;

    } else if (mode == LLIST_BACKWARD) {

        newnode -> next = &(ptr -> head);
        newnode -> prev = ptr -> head.prev;
        newnode -> next -> prev = newnode;
        newnode -> prev -> next = newnode;

    } else {
        return -3;
    }
    // 上面的两个操作中后两句是一样的为防止冗余，可以把一样的
    // 代码提到这里。
    // newnode -> next -> prev = newnode;
    // newnode -> prev -> next = newnode;
    return 0;

}

// 至于用 id 还是 name 等方式来查找，让用户来实现，你想要用 id 查找，那你就把 id 查找的函数传过来，与 key 比较是否一致。
static llist_node_st *find_ (LLIST *ptr, const void *key, llist_cmp *cmp) {

    llist_node_st *cur;
   
    for (cur = ptr -> head.next; cur != &ptr -> head; cur = cur -> next) {
        
        if (cmp (key, cur -> data) == 0) {
            break;
        }

    }

    return cur;     
    // 将查找到的数据返回给用户,如果查找失败，即全部查完了，
    // 都没有找到，回到了头节点，此时返回的是头节点,当用户使用头节点的 data 时
    // 是 NULL(在 create 时给的值)，自然就知道查找失败了

}

// 在这个函数里面再用一个函数 find_ 来查找，查找的过程就在 find_, 而 llist_find 是判断查找是否成功，然后交给用户。
// 为什么不直接写到 llist_find 里面，因为查找的过程在 delete 和 fetch 中也要用到，在 delete 和 fetch 中查找是否
// 成功且要做什么操作，它们会在各自的函数中实现，它们只需 find_ 这个操作。
void *llist_find (LLIST *ptr, const void *key, llist_cmp *cmp) {

    return find_(ptr, key, cmp) -> data;

}

// 这里就体现出来了 find_ 的好用了，如果这里用 llist_find ，返回值则为 void *, 又要转换类型才能用当前的 node,而
// find_ 的返回值为 llist_node_st * ,返回来的直接就可以用。
int llist_delete (LLIST *ptr, const void *key, llist_cmp *cmp) {

    llist_node_st *node;
    node = find_ (ptr, key, cmp);
    if (node == &ptr -> head) {
        return -1;
    } 
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    free (node -> data);
    free (node);
    return 0;

}

int llist_fetch (LLIST *ptr, const void *key, llist_cmp *cmp, void *data) {

    llist_node_st *node;
    node = find_ (ptr, key, cmp);
    if (node == &ptr -> head) {
        return -1;
    }
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    // 如果 data 为空，就不写给 data返回给用户，因为 data 为空说明没为它分配空间，
    // 不然写了会报段错误
    if (data != NULL) {
        memcpy (data, node -> data, ptr -> size);
    }
    free (node -> data);
    free (node);
    return 0;

}

void llist_travel (LLIST *ptr, llist_op *op) {          // llist_op *op 相当于 void (*op) (void const *);

    llist_node_st *cur;

    for (cur = ptr -> head.next; cur != &(ptr -> head); cur = cur -> next) {
        op (cur -> data);
    }

}

void llist_destroy (LLIST *ptr) {

    llist_node_st *cur, *next;

    // for 循环时只删除有效节点，头节点还不删除，for 完后再 free () ptr,因为
    // 在头节点中还有 size 的空间，在 for 里面只是释放了 llist_node_st。所以头节点要单
    // 独释放。另外 llist_node_st 中还有 *data 也还要释放，因为创建时也分配了内存的。
    for (cur = ptr -> head.next; cur != &(ptr -> head); cur = next) {
        
        next = cur -> next;
        free (cur -> data);
        free (cur);
    }
    free (ptr);
}