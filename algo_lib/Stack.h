#include <stdlib.h>

#ifndef STACK_H
#define STACK_H

typedef struct STACK* Stack_pt;

Stack_pt new_stack();

void push_stack(Stack_pt s, void* val);

void* pop_stack(Stack_pt s);

void delete_stack(Stack_pt s);

#endif