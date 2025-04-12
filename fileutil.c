#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileutil.h"

const int CAPACITY_START = 20;
const int CAP_INCREMENT = 10;

// Note: I did Array of Arrays functions
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.

char ** loadFileAA(char *filename, int *size)
{	
	// initial capacity
	int capacity = CAPACITY_START;
	
	// Load the text file from the given filename.
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}

	// Allocate memory for an array of strings (arr).
	char ** arr = malloc(capacity * sizeof(char *));
	
	// buffer string
	char buffer[1000];

	// The size should be the number of entries in the array.
	*size = 0;

	// Read the file line by line.
	while (fgets(buffer, sizeof(buffer), in) != NULL){

    	//   Trim newline.
		char *newLine = strchr(buffer, '\n');
        if (newLine) *newLine = '\0';

		//   Expand array if necessary (realloc).
		if(*size == capacity){
			capacity += CAP_INCREMENT;
			arr = realloc(arr, capacity * sizeof(char *));
		}

		//   Allocate memory for the string (str).
		int len = strlen(buffer);
		arr[*size] = malloc((len + 1) * sizeof(char));


		//   Copy each line into the string (use strcpy).
		strcpy(arr[*size], buffer);

		//   Increment size
		(*size)++;
	}

    // Close the file.
	fclose(in);
	
	// Return pointer to the array of strings.
	return arr;
}


// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	// check every word in the array for target
	for(int i = 0; i < size; i++){

		// if word found return it
		if(strstr(lines[i], target) != NULL){
			return lines[i];
		}
	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	// Free everything inside the array
	for(int i = 0; i < size; i++){
		free(arr[i]);
	}

	// Free the array
	free(arr);
}