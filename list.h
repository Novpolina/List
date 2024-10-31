#include <stdio.h>

struct list_node{
    int data;
    int next;
    int prev;
};


struct List {
    list_node* node;
    int free;
    int length;
    int head;
    int tail;

};


List ListConstructor(size_t length);
void PushAfter(int index, int elem, List* list);
void PushBefore(int index, int elem, List* list);
int DeleteElem(int index, List* list);
void ListDump(List list);