#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ninth.h"

// External Variable (for delete method)
int status = 0;

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
	char d = 'd';
	int key;
	int h = 1;
	
	// Text file is null or doesn't exist -> print error
	if(textfile == NULL || !(textfile)){
		printf("error\n");
		return 0;
	}
	
	fscanf(textfile, "%c %d\n", &ch, &key);
	
	struct Node *root;
	
	// Allocating space/memory for the root node
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

		// Delete
		} else if(ch == d){
			root = delete(root, key);
			
			if(status == -1){
				printf("fail\n");
				status = 1;
			} else {
				printf("success\n");
				status = 1;
			}
			
		// Error
		} else {
			printf("error\n");
		}

	}

	eraseBST(root);
	return 0;
}

void buildNode(struct Node *n, int h, int key) {

	// Assigning values to the newly created node
	n->data = key; //
	n->height = h;
	n->left = NULL;
	n->right = NULL;

}

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
}

void insert(struct Node *root, int height, int key) {

	if(root == NULL){
		// Creating new node
		root = malloc(sizeof(Node)); //allocating space/memory
		buildNode(root, 1, key); //filling in values for new node
		printf("inserted %d\n", 1);
		return;
	}

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
}

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
}

struct Node *delete(struct Node *root, int key) {
	
	// Initializing Pointer (prev)
	struct Node *prev = NULL;
	
	// Root is null or node doesn't exist
	if(root == NULL){
		status = -1; //deletion was a 'fail'
		return NULL;
	
	// Right Subtree (recursively)
	} else if(key > root->data){
		root->right = delete(root->right, key);
	
	// Left Subtree (recursively)
	} else if(key < root->data){
		root->left = delete(root->left, key);
		
	// Target Node was found
	} else {
	
		// Case 1 - Target only has a LEFT CHILD
		if(root->right == NULL){
			return root->left;
		
		// Case 2 - Target only has a RIGHT CHILD
		} else if(root->left == NULL){
			return root->right;
			
		// Case 3 - Target has TWO CHILDREN
		} else {
		
			// Initializing Pointer (ptr)
			struct Node *ptr = root->right;
			
			// Finds minimum value 
			while(ptr->left != NULL){
				prev = ptr;
				ptr = ptr->left;
			}
			
			// Copy root data to ptr
			root->data = ptr->data;
			deleteHelper(root, ptr, prev);
		}
	
	}
	
	return root;

} //end of delete method

void deleteHelper(struct Node *root, struct Node *ptr, struct Node *prev) {

	//Semi-recursion for delete method
	if(prev !=  NULL){
		prev->left = delete(prev->left, prev->left->data);
	} else {
		root->right = delete(root->right, root->right->data);
	}

} //end of 'deleteHelper' method

void eraseBST(struct Node *root) {

	// Freeing all nodes in the BST
	if(root != NULL) {
	
		eraseBST(root->left); //left subtree
		eraseBST(root->right); //right subtree
		
		free(root); //freeing root
	}
    
} //end of 'eraseBST' method
