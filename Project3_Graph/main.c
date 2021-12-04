//
//  main.c
//  Project3_Graph
//
//  Created by Mohamed Yousif on 11/22/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void test_addvertex(Graph * graph,int v1);
void test_containvertex(Graph * graph,int v1);
void test_removevertex(Graph * graph,int v1);
void test_addedge(Graph * graph,int v1,int v2,int wt);
void test_containedge(Graph * graph,int v1,int v2);
void test_removeedge(Graph * graph,int v1,int v2);
void test_graph_num_vertex(Graph * graph);
void test_graph_num_edges(Graph * graph);
void test_graph_total_weight(Graph *graph);
void test_graph_get_degree(Graph *graph, int v1);
void test_graph_get_edge_weight(Graph *graph, int v1, int v2);
void test_graph_is_neighbor(Graph *graph, int v1, int v2);
void test_graph_get_predecessors(Graph *graph, int v1);
void test_graph_get_successors(Graph *graph, int v1);
void test_graph_has_path(Graph *graph, int v1, int v2);

void test_graph1();
void test_graph2();

int main(int argc, const char * argv[]) {
    // insert code here...
    test_graph2(argv);
    
    return 0;
}

void test_addvertex(Graph * graph,int v1)
{
    printf("Add vertics [%d] %d\n",v1,graph_add_vertex(graph,v1));
}

void test_containvertex(Graph * graph,int v1)
{
    printf("is vertics exist %d\n",graph_contains_vertex(graph,v1));
}

void test_removevertex(Graph * graph,int v1)
{
    printf("Remove vertics [%d] %d\n",v1,graph_remove_vertex(graph,v1));
}

void test_addedge(Graph * graph,int v1,int v2,int wt)
{
    printf("Add Edge [%d,%d] %d\n",1,0,graph_add_edge(graph, v1,v2,wt));
}

void test_containedge(Graph * graph,int v1,int v2)
{
    printf("is edge exist %d\n",graph_contains_edge(graph, v1, v2));
}
void test_removeedge(Graph * graph,int v1,int v2)
{
    printf("Remove Edge [%d,%d], %d\n",1,10,graph_remove_edge(graph, v1, v2));
}

void test_graph_num_vertex(Graph * graph)
{
    printf("Num Vertics : %d \n",graph_num_vertices(graph));
}

void test_graph_num_edges(Graph * graph)
{
    printf("Numb Edges: %d \n",graph_num_edges(graph));
}

void test_graph_total_weight(Graph *graph)
{
    printf("Total weight of graph %d \n",graph_total_weight(graph));
}

void test_graph_get_degree(Graph *graph, int v1)
{
    printf("Degree of Vertex [%d] : %d \n",v1,graph_get_degree(graph,v1));
}

void test_graph_get_edge_weight(Graph *graph, int v1, int v2)
{
    printf("Edge weight of %d->%d is %d\n",v1,v2,graph_get_edge_weight(graph,v1,v2));
}

void test_graph_is_neighbor(Graph *graph, int v1, int v2)
{
    printf("is a [%d] a neighbor of [%d]: %d\n",v1,v2,graph_is_neighbor(graph,v1,v2));
}

void test_graph_get_predecessors(Graph *graph, int v1)
{
    int i = 0;
    int* array  = graph_get_predecessors(graph, v1);
    printf("Predecessors of vertix %d:[",v1);
    for(;i<graph->max_vertex;i++)
    {
        if(array != NULL)
        {
        if(array[i] > 1000 || array[i] < -1)
            continue;
        int number =array[i];
        printf("%d ",number);
        }
    }
    free(array);
    array = NULL;
    printf("]\n");
}

void test_graph_get_successors(Graph *graph, int v1)
{
    int i = 0;
    int* array  = graph_get_successors(graph, v1);
    printf("Succecessors of vertix %d:[",v1);
    for(;i<graph->max_vertex;i++)
    {
        if(array != NULL)
        {
        if(array[i] > 1000 || array[i] < -1)
            continue;
        printf("%d\t",array[i]);
        }
    }
    free(array);
    array = NULL;
    printf("]\n");
}

void test_graph_has_path(Graph *graph, int v1, int v2)
{
    printf("Has path between %d and %d :%d\n",v1,v2,graph_has_path(graph,v1,v2));
}

void test_graph1()
{
    printf("Graph #1 :\n");
    Graph * graph = NULL;
    graph = graph_initialize();
    printf("Testing Add Vertex:\n");
    test_addvertex(graph,0);
    test_addvertex(graph,1);
    test_addvertex(graph,2);
    test_addvertex(graph,4);
    test_graph_num_vertex(graph);
    printf("\n");
    
    printf("Testing Contain Vertex:\n");
    test_containvertex(graph,0);
    test_containvertex(graph,1);
    test_containvertex(graph,2);
    test_containvertex(graph,4);
    test_containvertex(graph,40);
    test_containvertex(graph,'d');
    printf("\n");
    
    printf("Testing Add Edge:\n");
    test_addedge(graph,2,2,3);
    test_addedge(graph,2,1,3);
    test_addedge(graph,1,0,2);
    test_addedge(graph,0,2,1);
    test_graph_num_edges(graph);printf("\n");
    test_graph_total_weight(graph);
    printf("\n");
    
    printf("Testing Contain Edges:\n");
    test_containedge(graph,2,2);
    test_containedge(graph,2,1);
    test_containedge(graph,1,0);
    test_containedge(graph,0,2);
    test_containedge(graph,0,5);
    printf("\n");
    
    graph_print(graph);
    graph_output_dot(graph, NULL);
    
    printf("Graph Metrics Operations:\n");
    test_graph_get_degree(graph,0);
    test_graph_get_degree(graph,1);
    test_graph_get_degree(graph,2);
    test_graph_get_degree(graph,4);
    test_graph_get_edge_weight(graph, 2,2);
    test_graph_get_edge_weight(graph, 2,1);
    test_graph_get_edge_weight(graph, 0,2);
    test_graph_get_edge_weight(graph, 1,0);
    test_graph_get_edge_weight(graph, 4,0);
    test_graph_get_edge_weight(graph, 4,2);
    test_graph_get_edge_weight(graph, 40,2);
    test_graph_is_neighbor(graph,2,1);
    test_graph_is_neighbor(graph,2,2);
    test_graph_is_neighbor(graph,1,0);
    test_graph_is_neighbor(graph,0,2);
    test_graph_is_neighbor(graph,1,2);
    test_graph_is_neighbor(graph,0,1);
    test_graph_is_neighbor(graph,2,0);
    printf("\n");
    
    printf("Get Predecessors:\n");
    test_graph_get_predecessors(graph, 0);
    test_graph_get_predecessors(graph, 1);
    test_graph_get_predecessors(graph, 2);
    test_graph_get_predecessors(graph, 4);
    printf("\n");
    
    printf("Get successors:\n");
    test_graph_get_successors(graph, 0);
    test_graph_get_successors(graph, 1);
    test_graph_get_successors(graph, 2);
    test_graph_get_successors(graph, 4);
    printf("\n");
    
    printf("Testing Remove Edge:\n");
    test_removeedge(graph,1,0);
    test_containedge(graph,1,0);
    test_graph_num_edges(graph);
    printf("\n");
    
    printf("Testing Remove Vertex:\n");
    test_removevertex(graph,2);
    test_containvertex(graph,2);
    test_containedge(graph,2,2);
    test_containedge(graph,2,1);
    test_graph_num_vertex(graph);printf("\n");
    test_graph_num_edges(graph);
    
    printf("\n");
    printf("******\n");
    
}

void test_graph2(char * argv[])
{
    Graph * graph = NULL;
    graph = graph_initialize();
    if(graph_load_file(graph,argv[2]) == 0)
    {
    printf("Metrics:\n");
    test_graph_num_vertex(graph);
    test_graph_num_edges(graph);
    test_graph_total_weight(graph);
    test_graph_has_path(graph, 4, 5);
    test_graph_has_path(graph, 4, 6);
    test_graph_get_degree(graph, 3);
    test_graph_get_successors(graph, 3);
    test_graph_get_predecessors(graph, 3);
    test_graph_is_neighbor(graph, 2, 0);
    test_graph_is_neighbor(graph, 0, 2);
    test_graph_get_edge_weight(graph, 3, 2);
    printf("\n");
    graph_print(graph);
    graph_output_dot(graph,"GraphViz.txt");

    graph_save_file(graph,"output_graph.txt");
        free(graph);
    graph = NULL;
    }
    
}
