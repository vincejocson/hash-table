#include "hash.c"

// Helper function for output file
int output(String15 filename, char* hash_table[], int n, int tablesize, int stringcount, int stored_homeaddress, int stored_collisions) {
    FILE* file = fopen(filename, "w");
    int comparisons = 0;
    float average;
    if (file == NULL) {
        printf("Error: Cannot open file for writing.\n");
        return -1;
    }
    else{
    	fprintf(file, "%d\n", n);
    	fprintf(file, "%d\n", stringcount);
    	fprintf(file, "%d\n", stored_homeaddress);
    	fprintf(file, "%d\n", stored_collisions);
    	for(int i = 0; i < tablesize; i++){
    		if(hash_table[i] != NULL){
    			comparisons += searchattempts(hash_table, hash_table[i], tablesize)+1; // will count all the search attempts
//				printf("%d", comparisons);
			}
		}
		average = (float)comparisons / stringcount;
		fprintf(file, "%.6f\n", average);
    	fprintf(file, "%s", "\n");

    	for (int i = 0; i < tablesize; i++) {
			if (hash_table[i] != NULL) {
    	        fprintf(file, "%d	%-15s	", i, hash_table[i]);
    	        if(i == hash_function(hash_table[i], tablesize)){
     	       		fprintf(file, "%5d	YES	1\n", i);
				}
				else{
					fprintf(file, "%5d	NO	", hash_function(hash_table[i], tablesize)); 
					fprintf(file, "%d\n", searchattempts(hash_table, hash_table[i], tablesize)+1); //counts the search attempts
				}
    	        
    	    } else {
    	        fprintf(file, "%d	%-15s %5s	---	---\n", i, "---", "---");
    	    }
    	}
    	printf("Output written to %s\n", filename);
    	return 0;
	}

    fclose(file);
}

int main(){
	FILE* input_file;
	int stringcount = 0;
	String15 buffer;
	String15 filename;
	int n;
	int tablesize;
	int stored_homeaddress = 0;
	int stored_collision = 0;
	
	char* hash_table[MAX_HASH_TABLE_SIZE];
	
	// get filename
	printf("Enter Input Filename: ");
	scanf("%s", filename);
	
	input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("File %s does not exist or cannot be opened.\n", filename);
        fclose(input_file);
    }
	else {
		fscanf(input_file, "%d", &n);
		tablesize = next_prime(n);
		initialize_table(hash_table, tablesize);
		while (fscanf(input_file, "%s", buffer) != EOF) {
			int status = insert(hash_table, buffer, tablesize);
			if(status == 0){
        		stored_homeaddress++;
        		stringcount++;
			}
			else if(status == 2){
				stored_collision++;
        		stringcount++;
			}
    	}
    	fclose(input_file);
    	
    	printf("Enter Output Filename: ");
    	scanf("%s", filename);
    	strcat(filename, ".txt");
    	output(filename, hash_table, n, tablesize, stringcount, stored_homeaddress, stored_collision);
	}
  
    
	
	return 0;
}
