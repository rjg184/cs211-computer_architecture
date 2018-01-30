#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fourth.h"

int main(int argc, char **argv) {

	// Input is empty -> print error
	if(argc < 2){
		printf("error\n");
		return 0;
	}

	// Text file (opens in read mode)
	FILE *textfile = fopen(argv[1], "r");
	
	// Text file is null or doesn't exist -> print error
	if(textfile == NULL || !(textfile)){
		printf("error\n");
		return 0;
	}	
	
	// Reading input from text file
	char input[256];
	fgets(input, 256, textfile);
	
	// Initializing Variables
	int i, j;
	int x = 0;
	int index = 0;
	int rows = atoi(strtok(input, "\t"));
	int columns = atoi(strtok(NULL, "\t"));
	int **result; //resultant (new matrix with values of matrix A + B)

	// Matrix is empty -> print error
	if(rows == 0 || columns == 0){
		printf("error\n");
		return 0;
	}
	
	// Allocating memory for number of rows
	int intS1 = sizeof(int*);
	int intS2 = sizeof(int);
	result = (int**)(malloc(intS1*rows));
	
	// Allocating memory for number of columns
	while(index < rows){
		result[index] = (int*)(malloc(intS2*columns));
		index++;
	}
	
	// Reading input from text file
	while(fgets(input, 256, textfile) != NULL){

		int val = strcmp(input, "\n");
		
		switch(val){
			case 0:
				x = 0;
				continue;
			default: 
				break;
		}
		
		char *temp = strtok(input, "\t");
		construct(temp, result, x);
		x++;
	}
	
	// Printing out the resultant (the two added matrices)
	// 	 -> *code/method translated to C from my java CS111 matrix assignment*
	for(i = 0; i < rows; i++){ //rows (denoated by i)
		for(j = 0; j < columns; j++){ //columns (denoted by j)
			printf("%d\t", result[i][j]);
		}
		printf("\n"); //new line for next row
	}
    
	return 0;
}

void construct(char *temp, int **result, int x) {

	int y;

	for(y = 0; temp != NULL; y++){
		int num = atoi(temp);
		result[x][y] = result[x][y] + num;
		temp = strtok(NULL, "\t");
	}
	
}
