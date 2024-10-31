#include <stdio.h>
#include "list.h"
#include "stdlib.h"


size_t LENGTH = 10;

int main(){

    List list;
    int elem = 0;
    list = ListConstructor(LENGTH);
    PushAfter(0, 23, &list);
    PushAfter(1, 56, &list);
    PushAfter(1, 34, &list);
    PushBefore(2, 28, &list);
    elem = DeleteElem(2, &list);
    PushAfter(3, 27, &list);
    ListDump(list);

}