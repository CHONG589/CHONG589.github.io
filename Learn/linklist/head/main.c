#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main () {

    list *l;
    int i, err;
    datatype arr[] = {12, 4, 23, 1, 34, 45, 56};

    l = list_create ();
    if (l == NULL)
        exit (1);

    for (i = 0; i < (sizeof (arr) /sizeof (*arr)); i++){
        // 整型数组没有尾 0 这一说法，字符数组才有
        if (list_order_insert (l, &arr[i])){
            exit (1);
        }
    }

    list_display (l);

    // list_delete (l, &arr[0]);

    // list_display (l);

    datatype value;
    err = list_delete_at (l, 2, &value);
    // err 为 0 时，说明成功了，0 为假
    if (err) {
        exit (1);
    }
    list_display (l);
    printf ("delete:%d\n", value);

    list_destroy (l);

    exit (0);
}