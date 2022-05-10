#include <stdlib.h>


#ifndef LINKED_LIST_H
#define LINKED_LIST_H
typedef struct LINKED_LIST* LinkedList_pt;

LinkedList_pt new_linked_list();

void add_linked(LinkedList_pt list, void* val);

void* get_current(LinkedList_pt list);

void l_next(LinkedList_pt list);

void l_prev(LinkedList_pt list);

void reset_list(LinkedList_pt list);

char is_empty_list(LinkedList_pt list);

void* remove_current(LinkedList_pt list);

void add_to_end_list(LinkedList_pt list, void* val);

void delete_list(LinkedList_pt list);

#endif