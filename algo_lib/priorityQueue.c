#include <stdlib.h>
#include "priorityQueue.h"
/*
typedef void* (*set_general_val)(void* param);
typedef void (*delete_general_val)(void* param);
typedef void* (*protect_general_val)(void* val);
*/
typedef struct NODE {
	void* val;
	int key;
}Node;

typedef struct P_QUEUE {
	Node* nodes;
	int size;
	int mem_size;
	/*
	set_general_val set_val;
	delete_general_val delete_val;
	protect_general_val protect_val;
	*/
}PQueue;



int perant(int i)
{
	return (i - 1) / 2;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

PQueue_pt new_p_queue(int int_size)
{
	PQueue_pt queue = (PQueue_pt)malloc(sizeof(PQueue));
	queue->nodes = (Node*)malloc(int_size * sizeof(Node));
	queue->size = 0;
	queue->mem_size = int_size;
	return queue;
}

void pq_resize(PQueue_pt queue)
{
	queue->nodes = (Node*)realloc((queue->mem_size + 100), sizeof(Node));
	queue->mem_size += 100;
}

void delete_pq(PQueue_pt queue)
{
	free(queue->nodes);
	free(queue);
}

void swap(PQueue_pt queue, int i, int j)
{
	void* temp = queue->nodes[i].val;
	int t_k = queue->nodes[i].key;
	queue->nodes[i].val = queue->nodes[j].val;
	queue->nodes[i].key = queue->nodes[j].key;

	queue->nodes[j].val = temp;
	queue->nodes[j].key = t_k;
}
void pq_push(PQueue_pt queue, void* val, int key)
{
	if (queue->size >= queue->mem_size)
		pq_resize(queue);
	int i = queue->size;
	queue->size++;
	queue->nodes[i].val = val;
	queue->nodes[i].key = key;
	while (i != 0 && queue->nodes[perant(i)].key > queue->nodes[i].key)
	{
		swap(queue, i, perant(i));
		i = perant(i);
	}
}
void heapify(PQueue_pt queue, int i)
{
	if (i >= queue->size)
		return;
	int smallest = i;
	if (left(i) < queue->size && queue->nodes[left(i)].key < queue->nodes[smallest].key)
		smallest = left(i);
	if (right(i) < queue->size && queue->nodes[right(i)].key < queue->nodes[smallest].key)
		smallest = right(i);
	if (smallest == i)
		return;
	swap(queue, i, smallest);
	heapify(queue, smallest);
}

void* pq_pop(PQueue_pt queue)
{
	if (queue->size <= 0)
		return NULL;
	void* val = queue->nodes[0].val;
	swap(queue, 0, queue->size - 1);
	queue->size--;
	heapify(queue, 0);
	return val;
}

void decrease_key(PQueue_pt queue, void* val, int new_key, char (*comp)(void*, void*))
{
	int i = 0;
	int test = *((int*)val);
	for (i = 0; i < queue->size && !(*comp)(queue->nodes[i].val, val); i++)
	{
		int test2 = *((int*)(queue->nodes[i].val));
	}
	if (i == queue->size)
	{
		pq_push(queue, val, new_key);
		return;
	}
	if (queue->nodes[i].key > new_key)
	{
		queue->nodes[i].key = new_key;
		while (i != 0 && queue->nodes[perant(i)].key > queue->nodes[i].key)
		{
			swap(queue, i, perant(i));
			i = perant(i);
		}
	}
	return;
}

char pq_isEmpty(PQueue_pt queue) {
	return (queue->size == 0) ? 1 : 0;
}