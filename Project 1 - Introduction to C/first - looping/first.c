#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){

	// Case 1: Empty input -> print error
	if(argc < 2){
		printf("error\n");
		return 0;
	}

	// Initializing variables
	int index;
	int input = atoi(argv[1]);

	// Case 2: Input is 0 or 1 -> NOT prime
	if(input == 0 || input == 1){
		printf("no\n");
		return 0;
	}

	// Case 3: Input is divisible -> NOT prime
	for(index = 2; index <= sqrt(input); index++){
		if(input % index == 0){
			printf("no\n");
			return 0;
		}
	}
	
	// Case 4: Otherwise, input is prime
	printf("yes\n");

	return 0;

}
