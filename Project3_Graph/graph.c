/* Fill in your Name and GNumber in the following two comment fields
 * Name:Mohamed Yousif Mohamed
 * GNumber:G01303134
 */

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Helpers
int isValidVertex(int v1);
int charToInt(char *c);
void Dispose(void *ptr);
int isdigit_(char * c);
int isemptyline(char *line);
int processfile(Graph *graph,FILE *fp);
void closefile(FILE *file);
long int findSize(char *filename);


Graph *graph_initialize()
{
    int i=0;
    int j=0;
    Graph * graph = graph = (Graph *) malloc(sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    
    for (;i<MAX_VERTICES ;i++)
    {
        graph->max_vertex = 0;
        graph->visited[i] = 0;
        //initialize adj_matrix
        for (;j<MAX_VERTICES;j++)
        {
            graph->adj_matrix[i][j] = 0;
        }
    }
    
    return graph;
}

// Vertex Operations
int graph_add_vertex(Graph *graph, int v1)
{
    //Check if vertex is invalid or graph is null
    if (graph == NULL || !isValidVertex(v1))
    {
        return -1;
    }
    
    if (graph_contains_vertex(graph,v1))
    {
        return 0;
    }
    if(v1 == 0)
    {
        
    }
    
    graph->visited[v1] = 1;
    if(v1 > graph->max_vertex)
    {
        graph->max_vertex = v1;
    }
    
    return 0;
}

int graph_contains_vertex(Graph *graph, int v1)
{
    //Check if vertex is invalid or graph is null
    if (graph == NULL || !isValidVertex(v1)|| (graph->visited[v1] == 0))
    {
        return 0;
    }
    
    if (graph->visited[v1] == 1)
    {
        return 1;
    }
    
    return 0;
}

int graph_remove_vertex(Graph *graph, int v1)
{
    int i = 0;
    //Check if vertex is invalid or graph is null
    if (graph == NULL || !isValidVertex(v1))
    {
        return -1;
    }
    
    if (!graph_contains_vertex(graph,v1))
    {
        return 0;
    }
    
    for (;i< MAX_VERTICES;i++)
    {
        if(graph->adj_matrix[v1][i] > 0)
        {
            graph_remove_edge(graph, v1, i);
        }
    }
    
    graph->visited[v1] = 0;
    
    return 0;
}

// Edge Operations
int graph_add_edge(Graph *graph, int v1, int v2, int wt)
{
    //Check if vertex is invalid or graph is null
    if (graph == NULL || !isValidVertex(v1))
    {
        return -1;
    }
    
    if(!graph_contains_vertex(graph, v1) || !graph_contains_vertex(graph, v2))
    {
        return -1;
    }
    
    graph->adj_matrix[v1][v2] = wt;
    return 0;
}

int graph_contains_edge(Graph *graph, int v1, int v2)
{
    //Check if vertics is invalid or graph is null
    if (graph == NULL || !isValidVertex(v1) || !isValidVertex(v2))
    {
        return 0;
    }
    
    if(graph->adj_matrix[v1][v2] > 0)
    {
        return 1;
    }
    
    return 0;
}

int graph_remove_edge(Graph *graph, int v1, int v2)
{
    //Check if vertics is invalid or graph is null
    if (graph == NULL || !isValidVertex(v1) || !isValidVertex(v2))
    {
        return -1;
    }
    
    if (!graph_contains_vertex(graph,v1) || !graph_contains_vertex(graph,v2))
    {
        return -1;
    }
    
    graph->adj_matrix[v1][v2] = 0;
    return 0;
}

// Graph Metrics Operations
int graph_num_vertices(Graph *graph)
{
    if (graph == NULL)
    {
        return -1;
    }
    
    int i = 0,count = 0;
    for(;(i<=graph->max_vertex);i++)
    {
        if(graph->visited[i] == 1)
        count++;
    }
    
    return count;
}

int graph_num_edges(Graph *graph)
{
    int i = 0 ,count = 0;
    if (graph == NULL)
    {
        return -1;
    }
    
    for(;i<graph->max_vertex;i++)
    {
        int j = 0;
            for(;j<graph->max_vertex;j++)
            {
                if(graph->adj_matrix[i][j] > 0)
                count++;
            }
    }
    
    return count;
}

int graph_total_weight(Graph *graph)
{
    int i = 0 ,sum = 0;
    if (graph == NULL)
    {
        return -1;
    }
    for(;i<graph->max_vertex;i++)
    {
        int j = 0;
            for(;j<graph->max_vertex;j++)
            {
                if(graph->adj_matrix[i][j] > 0)
                sum+=graph->adj_matrix[i][j];
            }
    }
    
    return sum;
}

// Vertex Metrics Operations
int graph_get_degree(Graph *graph, int v1)
{
    int i = 0 ,outdegree = 0 , indegree = 0;
    if (graph == NULL || !graph_contains_vertex(graph, v1))
    {
        return -1;
    }
    
    for(;i<graph->max_vertex;i++)
    {
        if(graph->adj_matrix[v1][i] > 0)
            outdegree++;
        if(graph->adj_matrix[i][v1] > 0)
            indegree++;
    }
    
    return outdegree+indegree;
}

int graph_get_edge_weight(Graph *graph, int v1, int v2)
{
    if (graph == NULL || !graph_contains_vertex(graph, v1) || !graph_contains_vertex(graph, v2))
    {
        return -1;
    }
    
    return graph->adj_matrix[v1][v2];
}

int graph_is_neighbor(Graph *graph, int v1, int v2)
{
    if (graph == NULL)
    {
        return 0;
    }
    
    int v1tov2weight = graph_get_edge_weight(graph,v1, v2);
    int v2tov1weight = graph_get_edge_weight(graph,v2, v1);
    
    if (v1tov2weight < 0 || v2tov1weight < 0)
    {
        return 0;
    }
    
    if (v1tov2weight > 0 || v2tov1weight > 0)
    {
        return 1;
    }
    
    return 0;
}

int *graph_get_predecessors(Graph *graph, int v1)
{
    int index = 0,i = 0;
    int *predecessorsary = NULL;
    if (graph == NULL || !graph_contains_vertex(graph, v1))
    {
        return NULL;
    }
    
    predecessorsary = (int *) malloc(graph->max_vertex+1 * sizeof(int));
    if (predecessorsary == NULL)
    {
        return NULL;
    }
    
    for(;i<graph->max_vertex;i++)
    {
        if(graph->adj_matrix[i][v1] > 0)
        {
                predecessorsary[index++] = i;
        }
    }
        
    predecessorsary[index] = -1;
    predecessorsary = (int *) realloc(predecessorsary, ++index * sizeof(int));
    return predecessorsary;
}

int *graph_get_successors(Graph *graph, int v1)
{
    int index = 0,i = 0;
    int *successorsary = NULL;
    if (graph == NULL || !graph_contains_vertex(graph, v1))
    {
        return NULL;
    }
    
    successorsary = (int *) malloc(graph->max_vertex+1 * sizeof(int));
    if (successorsary == NULL)
    {
        return NULL;
    }
    
    //predecessorsary[rear++] = v1;
    for(;i<graph->max_vertex;i++)
    {
        if(graph->adj_matrix[v1][i] > 0)
        {
            successorsary[index++] = i;
        }
    }
    successorsary[index] = -1;
    successorsary = (int *) realloc(successorsary, ++index * sizeof(int));
    return successorsary;
}

int graph_has_path(Graph *graph, int v1, int v2)
{
    /* uses array as a queue to queue the vertics that need to be search
       in order to find the required path*/
    int front =0;
    int rear =0;
    int *queue = (int *) malloc(MAX_VERTICES * sizeof(int));
    if (graph == NULL || !graph_contains_vertex(graph, v1) || !graph_contains_vertex(graph, v1))
    {
        return 0;
    }
    
    queue[rear++] = v1;
    
   while(front!=rear)
    {
        int i=0;
            for(;i<=graph->max_vertex;i++)
            {
                int row =queue[front];
                if(graph->adj_matrix[row][i] > 0 && i == v2)
                {
                    return 1;
                }
                else
                {
                    if(graph->adj_matrix[row][i] > 0 && rear+1 < MAX_VERTICES)
                    {
                        queue[rear++] = i;
                    }
                    
                }
            }
        front++;
    }
    free(queue);
    Dispose(queue);
    return 0;
}

// Input/Output Operations
void graph_print(Graph *graph)
{
    int i =0;
    int j = 0;
    printf("*Legand:*\n");
    printf("1- dot(.) means the vertex exist but no weight for that edge.\n");
    printf("2- (V) means the vertex exist but no self loop for it.\n");
    printf("3- dash(-) means the vertex doesn't exist on the graph.\n");
    printf("Have a nice Graph LOOOL !!\n");
    printf("----------------------------------------------------------------\n");
    if(graph == NULL)
    {
        printf("Graph is empty!");
        return;
    }
    
    for(;j<=graph->max_vertex;j++)
    {
            printf("\t%d\t",j);
    }
    printf("\n");
    for(;i<=graph->max_vertex;i++)
    {
        int j=0;
        printf("%d\t",i);
        for(;j<=graph->max_vertex;j++)
        {
                if (graph->adj_matrix[i][j] == 0)
                {
                    if(i==j && graph_contains_vertex(graph, j))
                        printf("(V)\t\t");
                    else if(!graph_contains_vertex(graph, i))
                        printf("-\t\t");
                    else
                    printf(".\t\t");
                }
                else
                {
                    printf("%d\t\t",graph->adj_matrix[i][j]);
                }
        }
            printf("\n");
    }
}

void graph_output_dot(Graph *graph, char *filename)
{
    int i =0;
    if(graph == NULL)
    {
        printf("Graph is empty!");
        return;
    }
    
    FILE *file = fopen(filename, "w+");
    if (file == NULL)
    {
        closefile(file);
        return;
    }
    
    fprintf(file,"digraph {\n");
    for(;i<=graph->max_vertex;i++)
    {
        int j=0;
        if(graph_contains_vertex(graph, i))
        {
            fprintf(file,"%d;\n",i);
        for(;j<=graph->max_vertex;j++)
        {
            if (graph->adj_matrix[i][j] > 0)
            {
                fprintf(file,"%d->%d [label = %d];\n",i,j,graph->adj_matrix[i][j]);
            }
        }
        }
    }
    fprintf(file,"}\n");
    closefile(file);
}

int graph_load_file(Graph *graph, char *filename)
{
    long size =findSize(filename);
    int processresult = 0;
      if(size == 0)
      {
          return -1;
      }
    
      FILE* fp = fopen(filename, "r");
      if(fp == NULL || graph == NULL)
      {
        // return -1 if there's a file error
        return -1;
      }
    processresult = processfile(graph,fp);
    if(processresult == -1)
    {
        free(graph);
        closefile(fp);
    }
    
    closefile(fp);
   
    return processresult;
}

int graph_save_file(Graph *graph, char *filename)
{
    int i =0;
    FILE *file = fopen(filename, "w+");
    if (file == NULL || graph == NULL)
    {
        closefile(file);
        return -1;
    }
    
    
    for(;i<=graph->max_vertex;i++)
    {
        int j=0;
        fprintf(file,"%d\n",i);
        
        if(graph_contains_vertex(graph, i))
        {
        for(;j<=graph->max_vertex;j++)
        {
            if (graph->adj_matrix[i][j] > 0)
            {
                fprintf(file,"%d,%d,%d\n",i,j,graph->adj_matrix[i][j]);
            }
        }
        }
    }
    closefile(file);
    return 0;
}

//helper methods
int isValidVertex(int v1)
{
    if (v1 < 0 || v1 >= MAX_VERTICES)
    {
        return 0;
    }
    
    return 1;
}
int charToInt(char *c)
{
    if(!isdigit_(c))
        return -1;
    
    int number =(int) strtol(c,NULL,10);
    return number;
}

void Dispose(void *ptr)
{
    ptr = NULL;
}

int isdigit_(char * c)
{
    int i=0;
    for(;i<strlen(c)-1;i++)
    {
        if(!isdigit(c[i]))
        {
            return 0;
        }
            
    }
    return 1;
}

int isemptyline(char *line)
{
    if (strcmp(line, "\n") == 0)
    {
        return 1;
    }
    return 0;
}

int processfile(Graph *graph,FILE *fp)
{
    const char *delimeter = ",";
    char currentline[FILE_ENTRY_MAX_LEN];
    
    while(fgets(currentline,sizeof(currentline),fp)!= NULL)
    {
        char *linegraph = NULL;
        int index = 0;
        int vertex =0;
        int edge =0;
        linegraph = strtok(currentline,delimeter);
        
        if (isemptyline(linegraph))
        {
            continue;
        }
        
        while (linegraph != NULL)
        {
            int number =charToInt(linegraph);
            if (number == -1)
            {
                return -1;
            }
            
            switch(index)
            {
                case 0:
                    if(!graph_contains_vertex(graph, number))
                    {
                         graph_add_vertex(graph, number);
                    }
                    vertex =number;
                    break;
                case 1:
                        if(!graph_contains_vertex(graph, number))
                        {
                            graph_add_vertex(graph, number);
                        }
                        edge =number;
                    break;
                case 2:
                    if(!graph_contains_edge(graph, vertex,edge))
                    {
                        graph_add_edge(graph, vertex, edge, number);
                    }
            }
            index++;
            linegraph = strtok(NULL, delimeter);
        }
        
        Dispose(linegraph);
    }
    return 0;
}

long int findSize(char *filename)
{
    FILE *file =fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
  
    fseek(file, 0L, SEEK_END);
  
    // calculating the size of the file
    long int res = ftell(file);
    closefile(file);
    return res;
}

void closefile(FILE *file)
{
    fclose(file);
    Dispose(file);
}
