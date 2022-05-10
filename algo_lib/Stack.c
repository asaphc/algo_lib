#include <stdlib.h>
#include "Stack.h"

typedef struct STACK_NODE {
    void* val;
    struct STACK_NODE* prev;
}StackNode;

typedef struct STACK
{
    StackNode* top;
}Stack;

Stack* new_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
}

char push_stack(Stack_pt s, void* val)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->val = val;
    node->prev = s->top;
    s->top = node;
    return 1;
}

void* pop_stack(Stack_pt s)
{
    StackNode* node = s->top;
    if (node == NULL)
        return NULL;
    s->top = node->prev;
    void* val = node->val;
    free(node);
    return val;
}

void delete_stack(Stack_pt s)
{
    while (s->top != NULL)
    {
        pop_stack(s);
    }
    free(s);
}
