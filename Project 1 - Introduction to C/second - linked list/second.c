#include <stdio.h>
#include <stdlib.h>
#include "second.h"

// Main Driver
int main(int argc, char** argv) {

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
	
	// Initializing Variables
	struct node *front = NULL;
	char ch;
	char i = 'i';
	char d = 'd';
	int value;
	
	// Scanning the textfile (input)
	while(fscanf(textfile, "%c %d\n", &ch, &value) == 2){
		
		// Case 1 - Insert
		if(ch == i){
			insert(&front, value);
			
		// Case 2 - Delete
		} else if(ch == d){
			delete(&front, value);
			
		// Case 3 - Error
		} else {
			printf("error\n");
			return 0;
		}

	}
	
	// Improper structure -> print error
	if(!(feof(textfile))){
		printf("error\n");
		return 0;
	}
	
	// Empty linked list -> print blank line
	if(front == NULL){
		printf("\n");
		return 0;
	}

	printLL(front); //prints out LL
	freeLL(&front); //frees the LL

	return 0;
}

void insert(struct node **front, int value) {

	// Initializing Pointers
	struct node *ptr = *front;
	struct node *prev = NULL;
	struct node *n;
	
	// Creating new node with value
	n = (struct node*)(malloc(sizeof(struct node)));
	n->data = value;

	// Empty linked list -> insert node
	if((*front) == NULL){
		*front = n;
		return;
	}
	
	// Iterating through linked list
	while(ptr != NULL){
	
		// Target exists -> duplicate
		if(value == ptr->data){
			//printf("duplicate\n");
			return;
		
		// Insert before pointer node
		} else if(value < ptr->data){
		
			// Case 1-> insert before front
			if(ptr == (*front)){
				n->next = *front;
				*front = n;
				return;
				
			// Case 2 -> insert before regular node
			} else {
				n->next = ptr;
				prev->next = n;
				return;
			}
		
		// Inserting new node at end of linked list
		} else if(ptr->next == NULL && value > ptr->data){
			prev = ptr;
			ptr = ptr->next;
			prev->next = n;
		
		// Advancing Pointers
		} else {
			prev = ptr;
			ptr = ptr->next;
		}
	}

} //end of 'insert' method

void delete(struct node **front, int value) {

	// Empty linked list -> print error
	if(*front == NULL){
		return;
	}
		
	// Initializing Pointers
	struct node *ptr = *front;
	struct node *prev = NULL;
	struct node *deleted;
	
	// Iterating through linked list
	while(ptr != NULL){
	
		// Target found
		if(value == ptr->data){
			
			// Case 1 -> Target is front (w/o nodes attached)
			if(ptr == (*front) && ptr->next == NULL){
				*front = NULL;
				return;
				
			// Case 2 -> Target is front (w/ nodes attached)
			} else if(ptr == (*front) && ptr->next != NULL) {
				prev = *front;
				*front = (*front)->next;
				prev = NULL;
				return;
			
			// Case 3 -> Target is a regular node (not front)
			} else {
				deleted = ptr;
				ptr = ptr->next;
				prev->next = ptr;
				prev = deleted;
			}
		
		// Advancing Pointers
		} else {
			prev = ptr;
			ptr = ptr->next;
		
		}
	}
	
} //end of 'delete' method

void printLL(struct node *front) {

	struct node *ptr = front;
	
	while(ptr != NULL){
		
		if(ptr->next == NULL){ //nodes
			printf("%d", ptr->data);
			printf("\n");
		} else { //last node
			printf("%d\t", ptr->data);
		}
		
		ptr = ptr->next; //advancing pointer
	}
	
	return;

} //end of 'printLL' method

void freeLL(struct node **front) {

	// Initializing Pointers
	struct node *ptr = *front;
	struct node *prev = NULL;

	//Freeing each individual node in LL
	while(ptr != NULL){
		prev = ptr;
		ptr = ptr->next;
		free(prev);
		prev = ptr;
	}
	
	// Making the front null
	*front = NULL;
	
} //end of 'freeLL' method
