#include "basic_utils.h"
#include "graphs.h"
#include <stdlib.h>

typedef struct Directed_wheighted_GRAPH {
	LinkedList_pt* edges;
	int v_num;
	LinkedList_pt* data;
}DWGraph;

DWGraph* create_graph(int v_num, int edges[][3],int e_size)
{
	DWGraph* graph = (DWGraph*)malloc(sizeof(DWGraph));
	graph->v_num = v_num;
	graph->edges = (LinkedList_pt*)malloc(v_num * sizeof(LinkedList_pt));
	graph->data = (LinkedList_pt*)malloc(v_num * sizeof(LinkedList_pt));
	for (int i = 0; i < v_num; i++)
	{
		graph->edges[i] = new_linked_list();
		graph->data[i] = new_linked_list();
	}
	for (int i = 0; i < e_size; i++)
	{
		int* edge = (int*)malloc(2 * sizeof(int));
		edge[0] = edges[i][1];
		edge[1] = edges[i][2];
		add_linked(graph->edges[edges[i][0]], edge);
	}
	return graph;

}

int get_size_graph(DWGraph* graph)
{
	return graph->v_num;
}

LinkedList_pt expand(DWGraph* graph, int v)
{
	LinkedList_pt list = graph->edges[v];
	LinkedList_pt new_list = new_linked_list();
	int* edge;
	int* new_edge;
	reset_list(list);
	while ((edge = get_current(list))!=NULL)
	{
		new_edge = (int*)malloc(2 * sizeof(int));
		new_edge[0] = edge[0];
		new_edge[1] = edge[1];
		add_linked(new_list, new_edge);
		l_next(list);
	}
	return new_list;
}

void delete_graph(DWGraph_pt graph) {
	for (int i = 0; i < graph->v_num; i++)
	{
		LinkedList_pt list = graph->edges[i];
		reset_list(list);
		int* val;
		while ((val = (int*)get_current(list)) != NULL)
		{
			free(val);
			l_next(list);
		}
		delete_list(list);
		delete_list(graph->data[i]);
	}
	free(graph->edges);
	free(graph->data);
	free(graph);
}

void add_data(DWGraph_pt graph, int v, void* data)
{
	add_to_end_list(graph->data[v], data);
}

LinkedList_pt get_data(DWGraph_pt graph, int v)
{
	return graph->data[v];
}

