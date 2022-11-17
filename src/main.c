#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"
#include "graph.h"
#include "file.h"
#include "io.h"

#define SERVER 1
#define CLIENT 2
#define MONITOR 3

static void print_vector(int* vet, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}
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
    priority_queue* q = new_priority_queue(10);

    //printf("Server:\n");
    //print_vector(server, S);
    //printf("Client:\n");
    //print_vector(client, C);
    //printf("Server:\n");
    //print_vector(monitor, M);

    //doing Dijkstra
    graph_TOTAL_Dijkstra(g);

    FILE* output_file = file_open(argv[2], "w");
    
    graph_calculate_inflation(g, S, C, M, server, client, monitor, output_file);

    graph_free(g);
    free(server);
    free(client);
    free(monitor);
    delete_priority_queue(q);
    file_close(input_file);
    file_close(output_file);

    
    return 0;
}
