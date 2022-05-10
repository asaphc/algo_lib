#ifndef PRIORITIYQ_H
#define PRIORITIYQ_H

 

typedef struct P_QUEUE* PQueue_pt;

PQueue_pt new_p_queue(int int_size);

void delete_pq(PQueue_pt queue);
void pq_push(PQueue_pt queue, void* val, int key);
void* pq_pop(PQueue_pt queue);
void decrease_key(PQueue_pt queue, void* val, int new_key, char (*comp)(void*, void*));
char pq_isEmpty(PQueue_pt queue);
#endif