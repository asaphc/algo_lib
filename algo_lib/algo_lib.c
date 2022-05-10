// algo_lib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "basic_utils.h"
#include "graphs.h"
#include "flow_graphs.h"

int* new_int(int v)
{
    int* val = (int*)malloc(sizeof(int));
    *val = v;
    return val;
}

char int_equal(void* i, void* j)
{
    int* a = (int*)i;
    int* b = (int*)j;
    if (*a == *b)
        return 1;
    return 0;
}

int dikstra(DWGraph_pt graph, int start, int end)
{
    int size = get_size_graph(graph);
    PQueue_pt queue = new_p_queue(size);
    int* s = (int*)malloc(size * sizeof(int));
    int* d = (int*)malloc(size * sizeof(int));
    int* explored = (int*)malloc(size * sizeof(int));
    int* v = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        v[i] = i;
        if (i == start)
        {       
            s[i] = start;
            d[i] = 0;
            explored[i] = 1;
        }
        else {
            s[i] = -1;
            d[i] = -1;
            explored[i] = 0;
        }
    }

    pq_push(queue, &v[start], 0);
    while (!pq_isEmpty(queue))
    {
        int* val = (int*)pq_pop(queue);
        if (*val == end)
        {
            int dist = d[*val];
            printf("distance is: %d\n", d[*val]);
            while (*val != start)
            {
                printf(" %d <-", *val);
                *val = s[*val];
            }
            printf(" %d\n",start);
            delete_pq(queue);
            
            free(d);
            free(v);
            free(s);
            free(explored);
            return dist;
        }
        explored[*val] = 1;
        LinkedList_pt list = expand(graph, *val);
        reset_list(list);
        int* edge;
        while ((edge = (int*)get_current(list)) != NULL)
        {

            if (explored[edge[0]] == 0)
            {
                if (d[edge[0]] > d[*val] + edge[1] || d[edge[0]]==-1)
                {
                    d[edge[0]] = d[*val] + edge[1];
                    s[edge[0]] = *val;
                }
                decrease_key(queue, &v[edge[0]], d[edge[0]], &int_equal);
            }
            l_next(list);
        }
    }
    return -1;

}

int prim(DWGraph_pt graph)
{
    int size = get_size_graph(graph);
    PQueue_pt queue = new_p_queue(size);
    int* d = (int*)malloc(size * sizeof(int));
    int* explored = (int*)malloc(size * sizeof(int));
    int* v = (int*)malloc(size * sizeof(int));
    v[0] = 0;
    d[0] = 0;
    explored[0] = 1;
    
    for (int i = 1; i < size; i++)
    {
        v[i] = i;
        d[i] = -1;
        explored[i] = 0;
    }

    pq_push(queue, &v[0], 0);
    int sum = 0;
    while (!pq_isEmpty(queue))
    {
        int* val = (int*)pq_pop(queue);
        explored[*val] = 1;
        sum += d[*val];
        LinkedList_pt list = expand(graph, *val);
        reset_list(list);
        int* edge;
        while ((edge = (int*)get_current(list)) != NULL)
        {
            if (explored[edge[0]] == 0)
            {
                if (d[edge[0]] > edge[1] || d[edge[0]] == -1)
                {
                    d[edge[0]] = edge[1];
                }
                decrease_key(queue, &v[edge[0]], d[edge[0]], &int_equal);
            }
            l_next(list);
        }
    }
    free(v);
    free(d);
    free(explored);
    return sum;

}


int main()
{
    int n_edges[][3] = { {0,1,2},{1,2,2},{2,3,3} };
    DWGraph_pt graph = create_graph(4, n_edges, 3);
    int res= dikstra(graph, 1, 2);
    int mst = prim(graph);
    printf("mst: %d\n", mst);
  
    Hash_table_pt table = new_hash_table(100);
    int v[5] = { 0,1,2,3,4 };
    add_hash(table, &v[2], "test");
    int* val = get_hash(table, "test");

    printf("val: %d\n", *val);

    int flow = edmond_karps(graph, 0, 3);
    printf("max flow: %d", flow);
    delete_graph(graph);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
