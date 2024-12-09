#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Maximum 1D array size (prime number > 1.1 * n)
#define MAX_HASH_TABLE_SIZE 18041

// Maximum string length (excluding null byte)
#define MAX_STRING_LENGTH 15

typedef char String15[MAX_STRING_LENGTH];

// Prototypes
unsigned int hash_function(const char* str, int n);
unsigned int resolve_collision(const char* str, unsigned int home_address, int attempt, int n);
int search(char* hash_table[], const char* str, int n);
bool is_prime(int num);
int next_prime(double n);
void initialize_table(char* hash_table[], int n);
int searchattempts(char* hash_table[], const char* str, int n);
int insert(char* hash_table[], const char* str, int n);

#endif
