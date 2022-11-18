#ifndef RTT_H
#define RTT_H
#include <stdlib.h>
#include <stdio.h>

typedef struct inflation Inflation;

Inflation* rtt_init(int size);
void rtt_set_elements(Inflation* f, int index, int s, int c, double weight);
void rtt_print(Inflation* f, int size, FILE* output);
void rtt_free(Inflation* i);

Inflation* rtt_calculate_inflation(double** minimum_path, int S, int C, int M, int *server, int *client, int *monitor);

int rtt_comparison(const void* a, const void* b);
void rtt_sort(Inflation* f, int size);
#endif