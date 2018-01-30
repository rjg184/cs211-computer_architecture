#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "third.h"

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
	
	// Initializing Variables
	int capacity = 10000;
	char input[256];
	char *ch;
	int isSearch;
	int isInsert;
	int status;
	int key;
	int j;
	
	// Creating Hashtable
	struct hashtable *hashtable = (struct hashtable*)(malloc(sizeof(struct hashtable)));
	hashtable->t = malloc(capacity * sizeof(struct node*));
	for(j = 0; j < capacity; j++){
		hashtable->t[j] = NULL;
	}
	
	while(fgets(input, 256, textfile)){
	
		ch = strtok(input, "\t");
		key = atoi(strtok(NULL, "\t"));
		isSearch = strcmp(ch, "s");
		isInsert = strcmp(ch, "i");
		
		// Finding index
		int index = makeIndex(key, capacity);
	
		// Search
		if(isSearch == 0){
		
			status = search(hashtable, key, capacity, index);
			
			if(status == -1){
				printf("absent\n");
			} else {
				printf("present\n");
			}
		
		// Insert
		} else if(isInsert == 0){
		
			status = insert(hashtable, key, capacity, index);
			
			if(status == 1){
				printf("inserted\n");
			} else {
				printf("duplicate\n");
			}
			
		// Error
		} else {
			printf("error\n");
		}

	}
	
	// Improper structure -> print error
	if(!(feof(textfile))){
		printf("error\n");
		return 0;
	}

	return 0;
	
} //end of 'main' method


void buildNode(struct node *n, int num) {
	
	n->data = num;
	n->next = NULL;

} //end of 'buildNode' method


int search(struct hashtable *hashtable, int key, int capacity, int index) {

	// Initializing Variables
	struct node *ptr = hashtable->t[index];
	int present = 1;
	int absent = -1;
	
	// Case 1 -> hastable is empty
	if(ptr == NULL){
		return absent;
	
	// Case 2 -> target already exists
	} else if(key == ptr->data){
		return present;
	
	// Case 3 -> search hashtable for target
	} else {
		
		ptr = ptr->next;
		
		while(ptr != NULL){
		
			int check = findKey(ptr, key);
			
			if(check == 1){
				return present;
			} else {
				ptr = ptr->next; //increment pointer
			}
			
		}
		
	}
	
	return absent;

} //end of 'search' method


int makeIndex(int key, int capacity) {
	
	int key2 = (key * -1); //negative
	int index = (key >= 0) ? (key % capacity) : (key2 % capacity);

	return index;

} //end of 'makeIndex' method


int findKey(struct node *ptr, int key) {

	// Key found
	if(key == ptr->data){
		return 1; //'present' or 'duplicate'
	}
	
	return -1; //'absent' or 'inserted'

} //end of 'findKey' method


int insert(struct hashtable *hashtable, int key, int capacity, int index) {
	
	// Initializing Variables
	struct node *ptr = hashtable->t[index];
	int inserted = 1;
	int duplicate = -1;
	
	// Creating new node
	struct node *n = (struct node*)(malloc(sizeof(struct node)));
	buildNode(n, key);
	
	// Case 1 -> empty hashtable
	if(ptr == NULL){
		hashtable->t[index] = n;
		return inserted;
		
	// Case 2 -> first entry is target
	} else if(ptr->data == key){
		return duplicate;
		
	// Case 3 -> iterate through hashtable
	} else {
		
		while(ptr->next != NULL){
			
			int check = findKey(ptr, key);
			
			if(check == 1){
				return duplicate;
			} else {
				ptr = ptr->next;
			}
			
		}
	
		ptr->next = n; //new node is inserted after 'ptr'
	
	}
	
	return inserted;	
	
} //end of 'insert' method
