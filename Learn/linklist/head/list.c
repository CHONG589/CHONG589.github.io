#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list *list_create () {

    list *me;

    me = malloc (sizeof (*me));
    if (me == NULL)
        return NULL;
    me -> next = NULL;

    return me;
}

// me 和 i 尽量不要动，不要改变传过来的值，还有一个好处就是 me 用来保存头节点
int list_insert_at (list *me, int i, datatype *data) {

    int j = 0;
    list *node = me, *newnode;

    if (i < 0)
        return -1;         // The Pos is wrong!

    // node != NULL 可以理解成当插入的位置为 0 时，只有头节点，若为node -> next != NULL
    //这样，就插入不了，所以应为 node != NULL
    while (j < i && node != NULL) {
        
        node = node -> next;
        j++;
    }

    if (node) {
        newnode = malloc (sizeof (*newnode));
        if (newnode == NULL) 
            return -2;      // 

        newnode -> data = *data;
        newnode -> next = node -> next;
        node -> next = newnode;

        return 0;
    } else
        return -3;  // The Pos is wrong!
}

int list_order_insert (list *me, datatype *data) {

    list *p = me, *q;

    // p -> next 是判断当只有头节点和在尾部插入时判断跳出的，
    while (p -> next && p -> next -> data < *data) {
        p = p -> next;
    }

    q = malloc (sizeof (*q));
    if (q == NULL)
        return -1;

    q -> data = *data;
    q -> next = p -> next;
    p -> next = q;

    return 0;

}

int list_delete_at (list *me, int i, datatype *data) {

    int j = 0;
    list *p = me, *q;

    if (i < 0)
        return -1;

    *data = -1;
    
    while (j < i && p) {
        
        p = p-> next;
        j++;
    }

    if (p) {

        q = p -> next;
        p -> next = q -> next;
        *data = q -> data;
        free (q);
        q = NULL;
        return 0;

    } else {

        return -2;
    }

}

int list_delete (list *me, datatype *data) {

    list *p = me, *q;

    while (p -> next && p -> next -> data != *data) {
        p = p -> next;
    }

    if (p -> next == NULL) {
        
        return -1;

    } else {

        q = p -> next;
        p -> next = q -> next;
        free (q);
        q = NULL;

    }

}

int list_isempty (list *me) {

    if (me -> next == NULL)
        return 0;
    return 1;
}

void list_display (list *me) {

    list *node = me -> next;
    if (list_isempty (me) == 0)
        return ;

    while (node != NULL) {
        
        printf ("%d ", node -> data);
        node = node -> next;
    }
    printf ("\n");

    return ;
}

void list_destroy (list *me) {

    list *node, *next;

    for (node = me -> next; node != NULL; node = next) {
        
        next = node -> next;
        free (node);
    }
    free (me);
    return ;
}