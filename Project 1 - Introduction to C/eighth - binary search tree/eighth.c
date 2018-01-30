#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eighth.h"

int main(int argc, char **argv) {

	// Input is empty -> print error
	if(argc < 2){
		printf("error\n");
		return 0;
	}

	// Text file (opens in read mode)
	FILE *textfile = fopen(argv[1], "r");
	char ch;
	char s = 's';
	char i = 'i';
	int key;
	int h = 1;
	
	// Text file is null or doesn't exist -> print error
	if(textfile == NULL || !(textfile)){
		printf("error\n");
		return 0;
	}
	
	fscanf(textfile, "%c %d\n", &ch, &key);
	
	// Allocating space/memory for the root node
	struct Node *root;
	root = malloc(sizeof(Node));
	buildNode(root, h, key); //building root node
	printf("inserted %d\n", h);
	
	// Scanning text file (input)
	while(fscanf(textfile, "%c %d\n", &ch, &key) == 2){
	
		// Search (returns '-1' if not found)
		if(ch == s){
		
			int height = search(root, key);
			
			if(height == -1){
				printf("absent\n");
			} else {
				printf("present %d\n", height);
			}

		// Insert (inserts node at appropriate location)
		} else if(ch == i){
			insert(root, h, key);

		// Error
		} else {
			printf("error\n");
		}

	}

	return 0;
	
} //end of 'main' method

void buildNode(struct Node *n, int h, int key) {

	// Assigning values to the newly created node
	n->data = key; //
	n->height = h;
	n->left = NULL;
	n->right = NULL;

} //end of 'buildNode' method

int search(struct Node *root, int key) {
	
	// Empty BST -> not found
	if(root == NULL){
		return -1;
	}
	
	struct Node *ptr = root;
	int height = 0;
	
	while(ptr != NULL){
	
		height = height + 1;
	
		if(key == ptr->data){ //key found
			
			ptr->height = height;
			return height;
			
		} else if(key < ptr->data){ //goes left
			ptr = ptr->left;
			
		} else { //goes right
			ptr = ptr->right;
		}
	
	}
	
	return -1;
	
} //end of 'search' method

void insert(struct Node *root, int height, int key) {

	// Initializing Pointers (ptr and prev)
	struct Node *ptr = root;
	struct Node *prev = NULL;
	
	// Searching for place to insert
	while(ptr != NULL){
	
		// Duplicate (key found)
		if(key == ptr->data){
			printf("duplicate\n");
			return;
			
		// Left Subtree
		} else if(key < ptr->data){
			prev = ptr;
			ptr = ptr->left;
			height++;
			
		// Right Subtree
		} else {
			prev = ptr;
			ptr = ptr->right;
			height++;
		}

	}
	
	helper(root, ptr, prev, key, height);
	
} //end of 'insert' method

void helper(struct Node *root, struct Node *ptr, struct Node *prev, int key, int height) {
	
	// Creating new node
	struct Node *temp = malloc(sizeof(Node)); //allocating space/memory
	buildNode(temp, height, key); //filling in values for new node
	
	// Either left or right child of parent
	if(key < prev->data){
		prev->left = temp;
	} else {
		prev->right = temp;
	}
	
	printf("inserted %d\n", height);
	
	return;
	
} //end of 'helper' method
