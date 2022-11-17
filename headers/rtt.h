#ifndef RTT_H
#define RTT_H
#include <stdlib.h>
#include <stdio.h>
typedef struct inflation Inflation;

Inflation* inflation_init(int size);
void inflation_set_elements(Inflation* f, int index, int s, int c, double weight);
void inflation_print(Inflation* f, int size, FILE* output);
void inflation_free(Inflation* i);

int inflation_comparison(const void* a, const void* b);
void inflation_sort(Inflation* f, int size);
#endif