#ifndef GRAPHS_H
#define GRAPHS_H

#include "basic_utils.h"
#include <stdlib.h>
typedef struct Directed_wheighted_GRAPH* DWGraph_pt;
DWGraph_pt create_graph(int v, int edges[][3], int e_size);

int get_size_graph(DWGraph_pt graph);

LinkedList_pt expand(DWGraph_pt graph, int v);

void delete_graph(DWGraph_pt graph);

void add_data(DWGraph_pt graph, int v, void* data);

LinkedList_pt get_data(DWGraph_pt graph, int v);

#endif