#include <stdlib.h>
#include <stdio.h>
#include "rtt.h"

struct inflation
{
    int source;
    int destiny;
    float weight;
};

Inflation* inflation_init(int size){
    return (Inflation*)malloc(size*sizeof(Inflation));
}

void inflation_set_elements(Inflation* f, int index, int s, int c, double weight){
    f[index].source = s;
    f[index].destiny = c;
    f[index].weight = weight;

    if(s == c && c == 0){
        printf("Pq tem dois 0? %d,%d\n", s, c);
    }
}

void inflation_print(Inflation* f, int size, FILE* output){
    int i;
    for(i = 0; i < size; i++){
        fprintf(output, "%d %d %lf\n", f[i].source, f[i].destiny, f[i].weight);
    }
}

void inflation_free(Inflation* i){
    free(i);
}


/**
 * FUNCOES USADAS NA ORDENACAO
 * 
 */
int inflation_comparison(const void* a, const void* b){
    Inflation first_ = *( (Inflation*)(a) );
    Inflation second_ = *( (Inflation*)(b) );

    double first = first_.weight;
    double second = second_.weight;

    if(first > second)return 1;
    else if(first < second)return -1;
    else return 0;
}

void inflation_sort(Inflation* f, int size){
    qsort(f, size, sizeof(Inflation), inflation_comparison);
}