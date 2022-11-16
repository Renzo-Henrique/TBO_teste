#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <stdio.h>
#include "adjacency_list.h"
#include "priority_queue.h"

typedef struct graph Graph;

typedef struct graph_inflation Graph_inflation;

Graph* graph_init(int qtd);

int graph_get_qtd(Graph* g);

void graph_set_vertex_type(Graph* g, int index, char type);
char graph_get_vertex_type(Graph* g, int index);

void graph_set_edge(Graph* g, int line, int column, double weight);

double graph_get_edge(Graph* g, int line, int column);

void graph_set_edge_list(Graph* g, int line, int column, double weight, Cell* neighbor);

double graph_get_edge_list(Graph* g, int line, int column);

void graph_print_adjacency(Graph* g);

void graph_print_minimum_paths(Graph* g);

void graph_print_vertex(Graph* g);

void graph_print(Graph* g);

void graph_free(Graph* g);

void graph_TOTAL_Dijkstra(Graph* g);

void graph_Dijkstra(Graph* g, int source, double* dist, int* prev);

double calculate_RTT(Graph* g, int i, int j);

double calculate_RTT_approximate(Graph *g, int server, int client, int *monitor, int M);

void inicitialize_inflation(Graph *g, int S, int C, int M, int *server, int *client, int *monitor);

void inflation_free(Graph_inflation* i);

#endif