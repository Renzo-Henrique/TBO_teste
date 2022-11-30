#include <stdlib.h>
#include <stdio.h>
#include "rtt.h"
#include "graph.h"
#define MIN(a,b)    ((a)<(b)?(a):(b))
struct inflation{
    int source;
    int destiny;
    double weight;
};

/*
*   Funcões estáticas
*
*/
static Inflation* rtt_init(int size){
    return (Inflation*)malloc(size*sizeof(Inflation));
}

static double calculate_RTT(double** minimum_path, int i, int j){
    double RTT = minimum_path[i][j] + minimum_path[j][i];
    return RTT;
}

static void rtt_set_elements(Inflation* f, int index, int s, int c, double weight){
    f[index].source = s;
    f[index].destiny = c;
    f[index].weight = weight;
}

static double calculate_RTT_approximate(double** minimum_path, int server, int client, int *monitor, int M){
    double RTT_maior, RTT_menor = calculate_RTT(minimum_path, server, monitor[0]) + calculate_RTT(minimum_path, monitor[0], client);
    for (int i = 1; i < M; i++){
        RTT_maior = calculate_RTT(minimum_path, server, monitor[i]) + calculate_RTT(minimum_path, monitor[i], client);
        RTT_menor = MIN(RTT_menor, RTT_maior);
    }
    return RTT_menor;
}

static int rtt_comparison(const void* a, const void* b){
    if( (((Inflation*)(a))->weight) > (((Inflation*)(b))->weight) )return 1;
    else if( (((Inflation*)(a))->weight) < (((Inflation*)(b))->weight) )return -1;
    else return 0;
}

/*
*   Funcões da interface
*/

void rtt_print(Inflation* f, int size, FILE* output){
    int i;
    for(i = 0; i < size; i++){
        fprintf(output, "%d %d %lf\n", f[i].source, f[i].destiny, f[i].weight);
    }
}

void rtt_free(Inflation* i){
    free(i);
}


Inflation* rtt_calculate_inflation(double** minimum_path, int S, int C, int M, int *server, int *client, int *monitor){   
    int size_vector = S * C, position = 0;
    Inflation* vector_inflation = rtt_init(size_vector);
    double RTT_star, RTT;

    for (int j = 0; j < S; j++){
        for (int k = 0; k < C; k++){   
            if(server[j] == client[k] && client[k] == 0){
                printf("Pq tem dois 0? %d,%d\n", server[j], client[k]);
            }
            RTT = calculate_RTT(minimum_path, server[j], client[k]);
            RTT_star = calculate_RTT_approximate(minimum_path, server[j], client[k], monitor, M);
            rtt_set_elements(vector_inflation, position, server[j], client[k], RTT_star / RTT);
            position++;
        }
    }
    return vector_inflation;  
}


void rtt_sort(Inflation* f, int size){
    qsort(f, size, sizeof(Inflation), rtt_comparison);
}