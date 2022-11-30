#ifndef RTT_H
#define RTT_H
#include <stdlib.h>
#include <stdio.h>

typedef struct inflation Inflation;

/// @brief Prints two ids followed by the rtt value
/// @param f 
/// @param size 
/// @param output 
void rtt_print(Inflation* f, int size, FILE* output);

/// @brief Free memory
/// @param i 
void rtt_free(Inflation* i);

/// @brief Calculate the inflation value of all pairs of vertices of S and C
/// @param minimum_path 
/// @param S 
/// @param C 
/// @param M 
/// @param server 
/// @param client 
/// @param monitor 
/// @return 
Inflation* rtt_calculate_inflation(double** minimum_path, int S, int C, int M, int *server, int *client, int *monitor);

/// @brief Sort the inflation in non decreassing order
/// @param f 
/// @param size 
void rtt_sort(Inflation* f, int size);
#endif