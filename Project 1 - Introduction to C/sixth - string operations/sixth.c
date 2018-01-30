#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

	// Empty input -> print error
	if(argc < 2){
		printf("error\n");
		return 0;
	}

	// Initializing variables
	int index;
	int length = argc;
	char letter;
	
	// Looping through string -> print every first letter
	for(index = 1; index < length; index++){
		letter = argv[index][0];
		putchar(letter);
		
		// Printing new line at end of output
		if(index == (length - 1)){
			printf("\n");
		}
		
	}
	
	return 0;
}
