#include <stdlib.h>
#include <stdio.h>
#include "assertx.h"
#include "graph.h"
#include "priority_queue.h"
#include "adjacency_list.h"
#include "rtt.h"

//infinitE is 1M
#define INFINITE 1000000
//undefined is -1
#define UNDEFINED -1

struct graph{
    double** adjacency_matrix;
    int qtd_vertex;
    int* vetor_vertex;
    Adjacency_list* list;
};

Graph* graph_init(int qtd){
    //initializing the graph (just the elements)
    Graph* g = (Graph*)malloc(sizeof(Graph));
    assertx(g!=NULL, "GRAPH IS NULL");
    g->qtd_vertex = qtd;
    g->vetor_vertex = (int*)calloc(qtd, sizeof(int));
    assertx(g->vetor_vertex!=NULL, "VECTOR OF VERTEX IS NULL");
    /*initializing the adjacency_list wich contain the structure being used to search in the graph
    */
    g->list = adjacency_list_init(qtd);
    return g;
}

int graph_get_qtd(Graph* g){
    return g->qtd_vertex;
}

void graph_set_vertex_type(Graph* g, int index, char type){
    if(g!=NULL)
        g->vetor_vertex[index] = type;
}
char graph_get_vertex_type(Graph* g, int index){
    if(g!=NULL) 
        return g->vetor_vertex[index];
    return 0;
}

void graph_set_edge(Graph* g, int line, int column, double weight){
    if(g!=NULL)
        g->adjacency_matrix[line][column] = weight;
}

double graph_get_edge(Graph* g, int line, int column){
    if(g!=NULL) 
        return  g->adjacency_matrix[line][column];
    return __DBL_MAX__;
}

void graph_set_edge_list(Graph* g, int line, int column, double weight, Cell* neighbor){
    adjacency_list_create_next_neighbor(g->list, line, neighbor, column, weight );
}

double graph_get_edge_list(Graph* g, int line, int column){
    return adjacency_list_get_edge(g->list, line, column);
}

double** graph_get_minimum_paths(Graph* g){
    return g->adjacency_matrix;
}

void graph_print_adjacency(Graph* g){
    if(g==NULL) return;
    adjacency_list_print(g->list);
}

void graph_print_minimum_paths(Graph* g){
    if(g==NULL) return;
    int i,j;
    for(i = 0; i < graph_get_qtd(g); i++){
        for(j = 0; j < graph_get_qtd(g); j++){
            printf("%lf ",g->adjacency_matrix[i][j]);//.4lf
        }
        printf("\n");
    }
}

void graph_print_vertex(Graph* g){
    if(g==NULL) return;
    int i;
    for(i = 0; i < g->qtd_vertex; i++){
        printf("%c ", g->vetor_vertex[i]);
    }
    printf("\n");
}

void graph_print(Graph* g){
    if(g==NULL) return;
    printf("Vertex qtd: %d\n", g->qtd_vertex);
    printf("AdjacencyMatrix:\n");
    graph_print_adjacency(g);
    printf("\nVertex Types:\n");
    graph_print_vertex(g);
    printf("\n");
}

void graph_free(Graph* g){
    if(g==NULL) return;
    //free in adjacency matrix
    int i;
    for(i = 0; i <g->qtd_vertex; i++){
        free(g->adjacency_matrix[i]);
    }
    free(g->adjacency_matrix);

    //free in vetor_vertex
    free(g->vetor_vertex);

    //ver se a lista de adjacencia já foi desalocada
    if(g->list != NULL){
        adjacency_list_free(g->list);
    }
    //free in graph g
    free(g);
}

/**
 * Dijkstra eh do graph.h??
 * Fazer funcoes:
 * 
 */
void graph_TOTAL_Dijkstra(Graph* g){
    int i;
    priority_queue* q = new_priority_queue(g->qtd_vertex);
    //adjacency_list_print(g->list);
    for(i = 0; i < g->qtd_vertex; i++){
        //printf("Dijkstra vertex %d\n", i);
        graph_Dijkstra(g, i, g->adjacency_matrix[i], q);
    }
    
    //printf("\n\n");
    //graph_print_minimum_paths(g);
    delete_priority_queue(q);
    g->list = adjacency_list_free(g->list);
}

void graph_PARCIAL_Dijkstra(Graph* g,  int S, int C, int M, int *server, int *client, int *monitor){
    /*allocating space for the adjacency_matrix containing the minimum paths
        of servers, clients and monitors*/
    g->adjacency_matrix = (double**)calloc( g->qtd_vertex, sizeof(double*));
    assertx( (g->adjacency_matrix)!=NULL, "ADJ MATRIX IS NULL");
    
    priority_queue* q = new_priority_queue(g->qtd_vertex);
    
    int i;
    for(i = 0; i < S; i++){
        g->adjacency_matrix[ server[i] ] = (double*)calloc( g->qtd_vertex, sizeof(double));
        assertx(g->adjacency_matrix[ server[i] ] != NULL, "ADJ MATRIX LINE IS NULL");

        graph_Dijkstra(g, server[i], g->adjacency_matrix[ server[i] ], q);
    }

    for(i = 0; i < M; i++){
        g->adjacency_matrix[ monitor[i] ] = (double*)calloc( g->qtd_vertex, sizeof(double));
        assertx(g->adjacency_matrix[ monitor[i] ] != NULL, "ADJ MATRIX LINE IS NULL");

        graph_Dijkstra(g, monitor[i], g->adjacency_matrix[ monitor[i] ], q);
    }

    for(i = 0; i < C; i++){
        g->adjacency_matrix[ client[i] ] = (double*)calloc( g->qtd_vertex, sizeof(double));
        assertx(g->adjacency_matrix[ client[i] ] != NULL, "ADJ MATRIX LINE IS NULL");

        graph_Dijkstra(g, client[i], g->adjacency_matrix[ client[i] ], q);
    }

    delete_priority_queue(q);
    g->list = adjacency_list_free(g->list);
}

void graph_Dijkstra(Graph* g, int source, double* dist, priority_queue* queue){
    int size = graph_get_qtd(g);
    //printf("---Beginning of a new Djikstra: %d\n", source);
    dist[source] = 0;
    //prev[source] = -1;
    //priority_queue* queue = new_priority_queue(g->qtd_vertex); ?
    int i;
    for(i = 0; i < size; i++){
        if(i != source){
            dist[i] = INFINITE;
            //prev[i] = UNDEFINED;
        }
        //adicionar com prioridade
        push(queue, i, dist[i]);
    }

    //show_inside_priority_queue(queue);
    int u,v;
    //neighbor eh um vizinho de u na lista de adjacência
    Cell* neighbor = NULL;
    int count = 0;

    while( size_queue(queue) > 0){
        u = pop(queue);
        //stops when neighbor == NULL
        while(1){
            neighbor = adjacency_list_next_neighbor(g->list, u, neighbor);
            if(neighbor == NULL){
                //printf("SHIT");
                break;
            }
            count++;
            v = adjacency_list_get_index_neighbor(neighbor);
            //melhorar o jeito de encontrar vizinho
            double edge = adjacency_list_get_weight(neighbor);

            double alt = dist[u] + edge;
                if(alt < dist[v]){
                    dist[v] = alt;
                    //prev[v] = u;
                    //assertx(0, "Ate aq foi");
                    set_priority(queue, v, alt);
                    //decrease_priority(queue, v, alt);
                }

        }
    }
    clear(queue);
    //assertx(count == 9, "Faltando analisar aresta");
    //delete_priority_queue(queue); ?
    //printf("Trying to do Dijkstra\n");
}

/**
 * INFLATION CALCULATION----------------------------------
 * ----------------------------------
 * --------------------------
 * ----------------------
 * -----------------
 * -------------
 * -------
 * ---
 * -------------INFLATION CALCULATION
 */
/*
static double calculate_RTT(Graph *g, int i, int j)
{
    double RTT;
    RTT = g->adjacency_matrix[i][j] + g->adjacency_matrix[j][i];

    return RTT;
}

static double calculate_RTT_approximate(Graph *g, int server, int client, int *monitor, int M)
{
    double RTT_maior;
    double RTT_menor = calculate_RTT(g, server, monitor[0]) + calculate_RTT(g, monitor[0], client);

    for (int i = 1; i < M; i++)
    {
        RTT_maior = calculate_RTT(g, server, monitor[i]) + calculate_RTT(g, monitor[i], client);
        if (RTT_menor > RTT_maior)
        {
            RTT_menor = RTT_maior;
        }
    }
    // printf("RTT devolvido: %f\n", RTT_menor);
    return RTT_menor;
}

void graph_calculate_inflation(Graph *g, int S, int C, int M, int *server, int *client, int *monitor, FILE* output)
{   
    //printf("Server: %d, Client: %d, Monitor: %d\n", S,C,M);
    int size_vector = S * C;
    Inflation* vector_inflation = inflation_init(size_vector);
    double RTT_pointer;
    double RTT;

    int position = 0;
    for (int j = 0; j < S; j++)
    {
        for (int k = 0; k < C; k++)
        {   
            if(server[j] == client[k] && client[k] == 0){
                printf("Pq tem dois 0? %d,%d\n", server[j], client[k]);
            }
            //printf("%d,%d\n", server[j], client[k]);
            RTT = calculate_RTT(g, server[j], client[k]);
            RTT_pointer = calculate_RTT_approximate(g, server[j], client[k], monitor, M);
            // printf("RTT POINTER: %f", RTT_pointer);
            rtt_set_elements(vector_inflation, position, server[j], client[k], RTT_pointer / RTT);
            position++;
        }
    }
    printf("Trying to sort the inflation\n");
    inflation_sort(vector_inflation, size_vector);
    inflation_print(vector_inflation, size_vector, output);
    
    inflation_free(vector_inflation);
}*/