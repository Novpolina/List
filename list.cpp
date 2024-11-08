#include "list.h"
#include <stdlib.h>
#include <assert.h>

int ERROR = -1;
int ALL_OKAY = 0;
int POIZON = -12;



void FillNextForFree(List* list){

    for(int i = 1; i <= list->length; i++){
        list->node[i].next = -(i+1);
    }
}

void FillPrev(List* list){

    for(int i = 1; i <= list->length; i++){
        list->node[i].prev = POIZON;
    }
}

void dump_to_dot(List* list, int num_graph)
{
    FILE* f_dot = fopen("list.dot", "w");

    assert(f_dot);
    assert(list);
    if(ferror(f_dot))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");


    fprintf(f_dot, "digraph LIST%d {\n\trankdir=LR;\n\tbgcolor = white;\n", num_graph);
    
    fprintf(f_dot, "\tsubgraph cluster0 {\n\t\tnode [style=filled,color=white];\n"
                   "\t\tstyle=filled;\n\t\tcolor=lightgrey;\n");

    for(int i = 0; i < list->length; i++)
    {
        if(list -> node[i].prev == POIZON)
        {
            fprintf(f_dot, "\t\tnode%zu [shape=record, color=white,"
                           "label=\" index=%zu | data=POIZON | next=%d \" ];\n",
                           i, i, list -> node[i].next);
            int next = -(list -> node[i].next);

            if(i != list->length - 1){
                fprintf(f_dot, "\t\tnode%zu -> node%d;\n", i, next);
            }

        }

    }
       fprintf(f_dot, "\t\tlabel = \"Empty fields\";\n\t}\n");

    fprintf(f_dot, "\tnode0 [shape=record, color=green,"
                   "label=\" NULL LIST ELEMENT | index=0 | data=POIZON | next=%d | prev=%d \" ];\n",
                   list -> node[0].next, list -> node[0].prev);

    size_t i = 0;

    while(list -> node[i].next != 0)
    {
        fprintf(f_dot, "\tnode%zu -> node%d;\n", i, list -> node[i].next);

        i = list -> node[i].next;

        fprintf(f_dot, "\tnode%zu [shape=record, color=blue,"
                       "label=\" index=%zu | data=%d | next=%d | prev=%d \" ];\n",
                       i, i, list -> node[i].data, list -> node[i].next, list -> node[i].prev);
    }

    fprintf(f_dot, "\tnode%zu -> node0;\n", i);

    fprintf(f_dot, "\t\"free = %zu\";\n", list -> free);

    fprintf(f_dot, "}\n\n");

    fclose(f_dot);

}

void FillData(List* list){

    for(int i = 0; i <= list->length; i++){
        list->node[i].data = POIZON;
    }
}

void GetHeadAndTail (List* list, int index){

    if(list->node[index].prev == 0){
        list->head = list->free;

    }

    if(list->node[index].next == 0){
        list->tail = list->free;

    }
}

List ListConstructor(size_t length){
    List list;
    list.node = (list_node*)calloc(length + 1, sizeof(list_node));
    list.length = length;
    list.free = 1;

    FillNextForFree(&list);
    FillPrev(&list);
    FillData(&list);

    list.node[0].next = 0;
    list.node[0].prev = 0;
    list.head = 0;
    list.tail = 0;

    return list;
}

void PushAfter(int index, int elem, List* list){

    if(index < 0 || index >= list->length){

        printf ("Index %i out of bound!!!\n", index);

    }


    if(list->free == 0){

        printf("List is fully filled\n");

    }

    if(list->node[index].prev == POIZON){

        printf("Element at number %i does not exists\n", index);

    }

    int new_free = -(list->node[list->free].next);

    list->node[list->free].data = elem;

    list->node[list->free].prev = index;
    list->node[list->free].next = list->node[index].next;

    list->node[list->node[index].next].prev = list->free;  
    list->node[index].next = list->free;

    GetHeadAndTail (list, list->free);



    list->free = new_free;



}
void PushBefore(int index, int elem, List* list){

    if(index <= 0 || index > list->length){
        printf ("Index %i out of bound!!!\n", index);
    }



    if(list->free == 0){
        printf("List is fully filled\n");

    }

    if(list->node[index].prev == POIZON){

        printf("Element at number %i does not exists\n", index);

    }
    int new_free = -(list->node[list->free].next);

    
    list->node[list->free].data = elem;

    list->node[list->free].next = index;
    list->node[list->free].prev = list->node[index].prev;

    list->node[list->node[index].prev].next = list->free;  
    list->node[index].prev = list->free;

    GetHeadAndTail (list, list->free);


    list->free = new_free;


}

int DeleteElem(int index, List* list){

    if(index <= 0 || index > list->length){

        printf("Index %i out of bound\n", index);

    }

    if(list->node[index].prev == POIZON){
        printf("Element %i does not exists \n", index);
    }

    int elem = 0;

    elem = list->node[index].data;
    list->node[index].data = POIZON;

    list->node[list->node[index].prev].next = list->node[index].next;
    list->node[list->node[index].next].prev = list->node[index].prev;

    list->node[index].prev = POIZON;
    list->node[index].next = - list->free;

    GetHeadAndTail (list, list->free);

    list->free = index;

    return elem;

}

void PushFirst(List* list, int elem){

    PushAfter(0, elem, list);
 
}

void PushLast(List* list, int elem){

    PushBefore(0, elem, list);

}

int* GetFirstPointer(List* list){

    int first_elem_index = list->node[0].next;

    int* first_elem_pointer = &(list->node[list->node[0].next].data);


}

int* GetLastPointer(List* list){

    int first_elem_index = list->head;

    int* first_elem_pointer = &(list->node[list->node[0].prev].data);


}
int* GetPointerToNextElement(List* list, int index){

    if(index == list->tail){
        printf("Element is the last");
    }

    int first_elem_index = list->node[index].next;

    int* first_elem_pointer = &(list->node[list->node[index].next].data);


}
int* GetPointerToPrevElement(List* list, int index){

    if(index == list->head){

    }

    int first_elem_index = list->node[index].prev;

    int* first_elem_pointer = &(list->node[list->node[index].prev].data);


}
void ListDump(List list){

    printf("\n\n                 --------------------List--------------------");

    printf("\n Data: ");

    for(int i = 0; i <= list.length; i++){
        printf("  %i  ", list.node[i].data);
    }

    printf("\n Next: ");

    for(int i = 0; i <= list.length; i++){
        printf("   %i  ", list.node[i].next);
    }

    printf("\n Prev: ");

    for(int i = 0; i <= list.length; i++){
        printf("   %i  ", list.node[i].prev);
    }

    printf("\nHead: %i.", list.head);
    printf("\nTail: %i.", list.tail);
    printf("\nFree: %i.", list.free);


}









