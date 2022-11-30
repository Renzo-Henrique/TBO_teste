#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "priority_queue.h"
#include "graph.h"
#include "file.h"
#include "io.h"
#include "rtt.h"

#define SERVER 1
#define CLIENT 2
#define MONITOR 3

int main(int argc, char* argv[]){
    assertx( !(argc <= 1) , "Insira parametros de leitura e escrita");
    assertx( !(argc <= 2) , "Insira parametros de escrita");

    int V, E, S, C, M;
    Graph* g;
    int* server;
    int* client;
    int* monitor;

    FILE* input_file = file_open(argv[1], "r");
    read_input(input_file, &V, &E, &S, &C, &M, &server, &client, &monitor, &g);
    graph_PARCIAL_Dijkstra(g, S, C, M, server, client, monitor);

    FILE* output_file = file_open(argv[2], "w");
    Inflation* vector_inflation = rtt_calculate_inflation(graph_get_minimum_paths(g), S, C, M, server, client, monitor);
    /* ---- Trying to free memory to improve execution time of rtt_sort
    */
    graph_free(g);
    free(server);
    free(client);
    free(monitor);
    file_close(input_file);
    int size_vector = S * C;
    rtt_sort(vector_inflation, size_vector);
    rtt_print(vector_inflation, size_vector, output_file);  
    rtt_free(vector_inflation);
    file_close(output_file);
    return 0;
}
