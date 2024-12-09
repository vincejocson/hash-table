#include "hash.h"

// Custom hash function: simple weighted sum with modulus
unsigned int hash_function(const char* str, int tablesize) {
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) { 
        hash = (hash * 37 + str[i]); //adds every character value to hash and multiplies by a prime number 37
    }
    return hash % tablesize;
}

// Collision resolution function: linear probing
unsigned int resolve_collision(const char* str, unsigned int home_address, int attempt, int tablesize) {
    return (home_address + attempt) % tablesize;
}

// Search function: find string in the hash table
int search(char* hash_table[], const char* str, int tablesize) {
    unsigned int home_address = hash_function(str, tablesize);
    unsigned int index = home_address;
    int attempt = 0;

    while (hash_table[index] != NULL) {
        if (strcmp(hash_table[index], str) == 0) {
            return index; // Found
        }
        attempt++;
        index = resolve_collision(str, home_address, attempt, tablesize);

        // If we've checked all slots, stop searching
        if (attempt >= tablesize) {
            break;
        }
    }
    return -1; // Not found
}

// helper function to return the number of search comparisons
int searchattempts(char* hash_table[], const char* str, int tablesize) {
    unsigned int home_address = hash_function(str, tablesize);
    unsigned int index = home_address;
    int attempt = 0;

    while (hash_table[index] != NULL) {
        if (strcmp(hash_table[index], str) == 0) {
            return attempt; // Found
        }
        attempt++;
        index = resolve_collision(str, home_address, attempt, tablesize);

        // If we've checked all slots, stop searching
        if (attempt >= tablesize) {
            break;
        }
    }
    return -1; // Not found
}

bool is_prime(int num) {
    if (num < 2) return false; // Numbers less than 2 are not prime
    for (int i = 2; i <= sqrt(num); i++) { // checks divisibility from 2 to sqrt of num, this will reduce input
        if (num % i == 0) {
            return false; // Divisible by i, so not prime
        }
    }
    return true; // Prime number
}

int next_prime(double n) {
    int start = (int)ceil(n * 1.1); // Calculate n * 1.1 and round up
    while (!is_prime(start)) {
        start++; // Increment until a prime is found
    }
    return start;
}


// Helper function to initialize the hash table
void initialize_table(char* hash_table[], int tablesize) {
    for (int i = 0; i < tablesize; i++) {
        hash_table[i] = NULL;
    }
}

// Helper function that will insert string param to the hash table
int insert(char* hash_table[], const char* str, int tablesize) {
    unsigned int home_address = hash_function(str, tablesize);
    unsigned int index = home_address;
    int attempt = 0;

    while (hash_table[index] != NULL) {
        if (strcmp(hash_table[index], str) == 0) {
            // String already exists, no need to insert again
            return 1;	//signs that it is an already existing string case
        }
        attempt++;
        index = resolve_collision(str, home_address, attempt, tablesize);
        if (attempt >= tablesize) {
            printf("Error: Hash table is full.\n");
            return -1; //signs error
        }
    }

    // Insert the string into the resolved index
    hash_table[index] = strdup(str);
    if(attempt > 0)
    	return 2;	//signs that it is a collision case
    else
    	return 0;	// signs that things went as normal
}
