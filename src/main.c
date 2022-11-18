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

static void print_vector(int* vet, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}
int main(int argc, char* argv[]){
    assertx( !(argc <= 1) , "Insira parametros de leitura e escrita");
    assertx( !(argc <= 2) , "Insira parametros de escrita");

    double start_total = clock();

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
    //graph_TOTAL_Dijkstra(g);
    graph_PARCIAL_Dijkstra(g, S, C, M, server, client, monitor);

    double end_dijkstra = clock();

    FILE* output_file = file_open(argv[2], "w");
    double start_rtt = clock();
    Inflation* vector_inflation = rtt_calculate_inflation(graph_get_minimum_paths(g), graph_get_qtd(g), S, C, M, server, client, monitor);
    double end_rtt = clock();
    /* ---- Trying to free memory to improve execution time of rtt_sort
    */
    graph_free(g);
    free(server);
    free(client);
    free(monitor);
    delete_priority_queue(q);
    file_close(input_file);

    /* Trying to sort the structs of inflation to print in the exit file
    */
    //printf("Trying to sort the inflation\n");
    

    double start_sort = clock();

    int size_vector = S * C;
    rtt_sort(vector_inflation, size_vector);
    rtt_print(vector_inflation, size_vector, output_file);
    
    rtt_free(vector_inflation);
    file_close(output_file);

    double end_total = clock();

    printf("Djikstra execution time is: %lf\n", (end_dijkstra - start_total)/CLOCKS_PER_SEC);
    printf("Inflation calculation execution time is: %lf\n", (end_rtt - start_rtt)/CLOCKS_PER_SEC);
    printf("Sort execution time is: %lf\n", (end_total - start_sort)/CLOCKS_PER_SEC);
    printf("Total execution time is: %lf\n\n", (end_total - start_total)/CLOCKS_PER_SEC);

    
    return 0;
}
