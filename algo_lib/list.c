#include <stdlib.h>
#include "list.h"
typedef struct LINKED_NODE {
    void* val;
    struct LINKED_NODE* prev;
    struct LINKED_NODE* next;
}LinkedNode;

typedef struct LINKED_LIST {
    LinkedNode* start;
    LinkedNode* current;
    LinkedNode* end;
}LinkedList;

LinkedList* new_linked_list()
{
    LinkedList* ret = (LinkedList*)malloc(sizeof(LinkedList));
    ret->start = NULL;
    ret->current = NULL;
    ret->end = NULL;
    return ret;
}
void add_linked(LinkedList_pt list, void* val)
{
    LinkedNode* node = (LinkedNode*)malloc(sizeof(LinkedNode));
    node->val = val;
    if (list->start == NULL)
    {
        node->next = NULL;
        node->prev = NULL;
        list->start = node;
        list->end = node;
        return;
    }

    if (list->current == NULL)
    {
        node->prev = NULL;
        node->next = list->start;
        list->start->prev = node;
        list->start = node;
        return;
    }
    node->prev = list->current;
    node->next = list->current->next;
    if (list->current->next != NULL)
        list->current->next->prev = node;
    list->current->next = node;
    return;
}

void* get_current(LinkedList_pt list)
{
    if (list->current == NULL)
        return NULL;
    return list->current->val;
}

void l_next(LinkedList_pt list)
{
    if (list->current == NULL)
    {
        list->current = list->start;
        return;
    }
    list->current = list->current->next;
    return;
}

void l_prev(LinkedList_pt list)
{
    if (list->current == NULL)
    {
        list->current = list->end;
        return;
    }
    list->current = list->current->prev;
    return;
}

void reset_list(LinkedList_pt list)
{
    list->current = list->start;
    return;
}

char is_empty_list(LinkedList_pt list)
{
    if (list->start == NULL)
        return 1;
    return 0;
}

void* remove_current(LinkedList_pt list)
{
    LinkedNode* node = list->current;
    if (node == NULL)
        return NULL;
    if (list->current->next != NULL)
    {
        list->current->next->prev = list->current->prev;
    }
    else {
        list->end = list->current->prev;
    }
    if (list->current->prev == NULL)
    {
        list->start = list->current->next;
        list->current = NULL;
    }
    else {
        list->current->prev->next = list->current->next;
        list->current = list->current->prev;
    }
    void* val = node->val;
    free(node);
    return val;

}

void add_to_end_list(LinkedList_pt list, void* val)
{
    LinkedNode* node = (LinkedNode*)malloc(sizeof(LinkedNode));
    node->val = val;
    if (list->end == NULL)
    {
        list->start = node;
        list->end = node;
        node->next = NULL;
        node->prev = NULL;
        return;
    }
    list->end->next = node;
    node->prev = list->end;
    node->next = NULL;
    if (list->end->prev != NULL)
        list->end->prev->next = node;
    list->end = node;
}

void delete_list(LinkedList_pt list)
{
    reset_list(list);
    while (list->current != NULL)
        remove_current(list);
    free(list);
    return;
}