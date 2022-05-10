#include <stdlib.h>
#include "Queue.h"

typedef struct QUEUE_NODE {
    void* val;
    struct QUEUE_NODE* next;
}QueueNode;

typedef struct QUEUE {
    QueueNode* start;
    QueueNode* end;
}Queue;

Queue_pt new_queue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->start = NULL;
    queue->end = NULL;
    return queue;
}

void queue_push(Queue_pt queue, void* val)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->val = val;
    node->next = NULL;
    if (queue->end == NULL)
    {
        queue->start = node;
        queue->end = node;
        return 1;
    }
    queue->end->next = node;
    queue->end = node;
    return 1;
}

void* queue_pop(Queue_pt queue)
{
    QueueNode* node = queue->start;
    if (node == NULL)
        return NULL;
    if (queue->start == queue->end)
    {
        queue->start = NULL;
        queue->end = NULL;
    }
    else {
        queue->start = queue->start->next;
    }
    void* val = node->val;
    free(node);
    return val;
}

void delete_queue(Queue_pt queue)
{
    while (queue->start != NULL)
        queue_pop(queue);
    free(queue);
    return 1;
}
