#ifndef QUEUE_H
#define QUEUE_H

typedef struct QUEUE* Queue_pt;

Queue_pt new_queue();

void queue_push(Queue_pt queue, void* val);

void* queue_pop(Queue_pt queue);

void delete_queue(Queue_pt queue);

#endif
