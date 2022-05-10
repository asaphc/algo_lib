#include "graphs.h"
#include "basic_utils.h"

typedef struct FLOW_EDGE {
	int target;
	int capacity;
	int flow;
	struct FLOW_EDGE* reverse;
}FlowEdge;

typedef struct FLOW_GRAPH {
	LinkedList_pt* edges;
	int v_num;
}FlowGraph;

typedef struct FLOW_GRAPH* FlowGraph_pt;

FlowGraph_pt create_flow_graph(DWGraph_pt graph)
{
	FlowGraph_pt flow_g = (FlowGraph_pt)malloc(sizeof(FlowGraph));
	flow_g->v_num = get_size_graph(graph);
	flow_g->edges = (LinkedList_pt*)malloc(flow_g->v_num * sizeof(LinkedList_pt));
	for (int i = 0; i < flow_g->v_num; i++)
	{
		flow_g->edges[i] = new_linked_list();
	}
	for (int i = 0; i < flow_g->v_num; i++)
	{
		LinkedList_pt edges = expand(graph, i);
		reset_list(edges);
		int* edge;
		while ((edge = get_current(edges)) != NULL)
		{
			FlowEdge* fedge = (FlowEdge*)malloc(sizeof(FlowEdge));
			FlowEdge* redge = (FlowEdge*)malloc(sizeof(FlowEdge));
			fedge->target = edge[0];
			fedge->capacity = edge[1];
			fedge->flow = 0;
			fedge->reverse = redge;
			
			redge->target = i;
			redge->capacity = edge[1];
			redge->flow = edge[1];
			redge->reverse = fedge;

			add_to_end_list(flow_g->edges[i], fedge);
			add_to_end_list(flow_g->edges[edge[0]], redge);
			free(edge);
			l_next(edges);
		}
		delete_list(edges);
	}
	
	return flow_g;
}

void delete_flow_graph(FlowGraph_pt graph)
{
	for (int i = 0; i < graph->v_num; i++)
	{
		LinkedList_pt list = graph->edges[i];
		reset_list(list);
		FlowEdge* val;
		while ((val = (FlowEdge*)get_current(list)) != NULL)
		{
			free(val);
			l_next(list);
		}
		delete_list(list);
		
	}
	free(graph->edges);
	free(graph);
}

int edmond_karps(DWGraph_pt graph,int s,int t)
{
	FlowGraph_pt f_graph = create_flow_graph(graph);
	Queue_pt queue;
	int* v = (int*)malloc(get_size_graph(graph) * sizeof(int));
	FlowEdge** path = (FlowEdge**)malloc(get_size_graph(graph) * sizeof(FlowEdge*));
	

	for (int i = 0; i < get_size_graph(graph); i++)
		v[i] = i;
	int flow = 0;
	while (1)
	{	
		for (int i = 0; i < get_size_graph(graph); i++)
		{
				path[i] = NULL;	
		}
		queue = new_queue();
		queue_push(queue,&v[s]);
		int* val;
		while ((val = queue_pop(queue)) != NULL)
		{
			LinkedList_pt list = f_graph->edges[*val];
			reset_list(list);
			FlowEdge* edge;
			while ((edge = get_current(list)) != NULL)
			{
				if (edge->target!= s && edge->flow < edge->capacity && path[edge->target] == NULL)
				{
					path[edge->target] = edge;
					queue_push(queue, &v[edge->target]);
				}
				l_next(list);
			}
		}
		delete_queue(queue);
		
		if (path[t] == NULL)
		{
			delete_flow_graph(f_graph);
			free(v);
			free(path);
			return flow;
		}

		int df = -1;
		FlowEdge* e = path[t];
		while (e != NULL)
		{
			if (df == -1 || df > e->capacity - e->flow)
				df = e->capacity - e->flow;
			e = path[e->reverse->target];
		}

		e = path[t];
		while (e != NULL)
		{
			e->flow += df;
			e->reverse->flow -= df;
			e = path[e->reverse->target];
		}
		flow += df;
	}
	return -1;
}