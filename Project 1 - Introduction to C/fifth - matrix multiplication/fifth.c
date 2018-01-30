#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifth.h"

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
	
	// Matrix 1
	int **m1;
	int m1Row = atoi(strtok(input, "\t"));
	int m1Column = atoi(strtok(NULL, "\t"));
	
	// Other Variables
	int i, j, k;
	int x = 0;
	int index = 0;
	int **newMatrix; //resultant (new matrix with values of matrix A + B)

// ------------ Matrix 1:

	// Matrix is empty -> print error
	if(m1Row == 0 || m1Column == 0){
		printf("error\n");
		return 0;
	}
	
	// Allocating memory for number of rows
	int intS1 = sizeof(int*);
	int intS2 = sizeof(int);
	m1 = (int**)(malloc(intS1*m1Row));
	
	// Allocating memory for number of columns
	while(index < m1Row){
		m1[index] = (int*)(malloc(intS2*m1Column));
		index++;
	}
	
	// Reading input from text file
	while(fgets(input, 256, textfile) != NULL){

		int val = strcmp(input, "\n");
		if(val == 0){ break; }
		
		char *temp = strtok(input, "\t");
		construct(temp, m1, x);
		x++;
	}
	
// ------------ Matrix 2:

	// Reading input from text file
	fgets(input, 256, textfile);
	
	// Initializing Variables (Matrix 2)
	int **m2;
	int m2Row = atoi(strtok(input, "\t"));
	int m2Column = atoi(strtok(NULL, "\t"));
	int y = 0;
	int index2 = 0;
	int index3 = 0;
	
	// Matrix 2 is empty -> print error
	if(m2Row == 0 || m2Column == 0){
		printf("error\n");
		return 0;
	}
	
	// Columns in Matrix 1 = / = rows in Matrix 2 -> cannot multiply
	if(m1Column != m2Row){
		printf("error\n");
		return 0;
	}
	
	// Allocating memory for number of rows
	m2 = (int**)(malloc(intS1*m2Row));
	
	// Allocating memory for number of columns
	while(index2 < m2Row){
		m2[index2] = (int*)(malloc(intS2*m2Column));
		index2++;
	}
	
	// Reading input from text file
	while(fgets(input, 256, textfile) != NULL){
		char *temp = strtok(input, "\t");
		construct(temp, m2, y);
		y++;
	}
	
// ------------ Product Matrix (Matrix 3):

	int newRow = 0;
	int newColumn = 0;

	if(m1Row < m2Row){ newRow = m2Row; } 
	else { newRow = m1Row; }
	
	if(m1Column < m2Column){ newColumn = m2Column; } 
	else { newColumn = m1Column; }
	
	// Allocating memory for number of rows
	newMatrix = (int**)(malloc(intS1*newRow));
	
	// Allocating memory for number of columns
	while(index3 < newRow){
		newMatrix[index3] = (int*)(malloc(intS2*newColumn));
		index3++;
	}
	
	// Multiplication of the two matrices
	for(i = 0; i < m1Row; i++){
		for(j = 0; j < m2Column; j++){
			for(k = 0; k < m2Row; k++){
				newMatrix[i][j] = newMatrix[i][j] + m1[i][k] * m2[k][j];
			}
		}
	}
	
	// Printing out the resultant (the two added matrices)
	// 	 -> *code/method translated to C from my java CS111 matrix assignment*
	for(i = 0; i < m1Row; i++){ //rows from matrix 1 (denoated by i)
		for(j = 0; j < m2Column; j++){ //columns from matrix 2 (denoted by j)
			printf("%d\t", newMatrix[i][j]);
		}
		printf("\n"); //new line for next row
	}
    
	return 0;
}

void construct(char *temp, int **matrix, int x) {

	int r = x;
	int s;

	for(s = 0; temp != NULL; s++){
		int num = atoi(temp);
		matrix[r][s] = matrix[r][s] + num;
		temp = strtok(NULL, "\t");
	}
	
}
