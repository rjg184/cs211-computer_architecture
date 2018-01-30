#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

	// Empty input -> print error
	if(argc < 2){
		printf("error\n");
		return 0;
	}

	// Initializing Variables
	int index;
	int length = argc;
	int end;
	char letter;
	
	// Looping through string -> print every word's last letter
	for(index = 1; index < length; index++){
		end = strlen(argv[index]) - 1;
		letter = argv[index][end];
		putchar(letter);
		
		// Printing new line at end of output
		if(index == (length - 1)){
			printf("\n");
		}
		
	}
	
	return 0;
}
