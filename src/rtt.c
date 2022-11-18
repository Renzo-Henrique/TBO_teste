#include <stdlib.h>
#include <stdio.h>
#include "rtt.h"
#include "graph.h"

struct inflation
{
    int source;
    int destiny;
    float weight;
};

Inflation* rtt_init(int size){
    return (Inflation*)malloc(size*sizeof(Inflation));
}

void rtt_set_elements(Inflation* f, int index, int s, int c, double weight){
    f[index].source = s;
    f[index].destiny = c;
    f[index].weight = weight;

    if(s == c && c == 0){
        printf("Pq tem dois 0? %d,%d\n", s, c);
    }
}

void rtt_print(Inflation* f, int size, FILE* output){
    int i;
    for(i = 0; i < size; i++){
        fprintf(output, "%d %d %lf\n", f[i].source, f[i].destiny, f[i].weight);
    }
}

void rtt_free(Inflation* i){
    free(i);
}


static double calculate_RTT(double** minimum_path, int i, int j)
{
    double RTT = minimum_path[i][j] + minimum_path[j][i];

    return RTT;
}

static double calculate_RTT_approximate(double** minimum_path, int server, int client, int *monitor, int M)
{
    double RTT_maior;
    double RTT_menor = calculate_RTT(minimum_path, server, monitor[0]) + calculate_RTT(minimum_path, monitor[0], client);

    for (int i = 1; i < M; i++)
    {
        RTT_maior = calculate_RTT(minimum_path, server, monitor[i]) + calculate_RTT(minimum_path, monitor[i], client);
        if (RTT_menor > RTT_maior)
        {
            RTT_menor = RTT_maior;
        }
    }
    // printf("RTT devolvido: %f\n", RTT_menor);
    return RTT_menor;
}

Inflation* rtt_calculate_inflation(double** minimum_path, int S, int C, int M, int *server, int *client, int *monitor)
{   
    //printf("Server: %d, Client: %d, Monitor: %d\n", S,C,M);
    int size_vector = S * C;
    Inflation* vector_inflation = rtt_init(size_vector);
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
            RTT = calculate_RTT(minimum_path, server[j], client[k]);
            RTT_pointer = calculate_RTT_approximate(minimum_path, server[j], client[k], monitor, M);
            // printf("RTT POINTER: %f", RTT_pointer);
            rtt_set_elements(vector_inflation, position, server[j], client[k], RTT_pointer / RTT);
            position++;
        }
    }

    return vector_inflation;
    
}


/**
 * FUNCOES USADAS NA ORDENACAO
 * 
 */
int rtt_comparison(const void* a, const void* b){
    Inflation first_ = *( (Inflation*)(a) );
    Inflation second_ = *( (Inflation*)(b) );

    double first = first_.weight;
    double second = second_.weight;

    if(first > second)return 1;
    else if(first < second)return -1;
    else return 0;
}

void rtt_sort(Inflation* f, int size){
    qsort(f, size, sizeof(Inflation), rtt_comparison);
}