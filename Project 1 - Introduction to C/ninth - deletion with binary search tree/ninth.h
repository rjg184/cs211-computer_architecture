#ifndef _ninth_h
#define _ninth_h

typedef struct Node{
	int data;
	int height;
	struct Node *left;
	struct Node *right;
} Node;

void buildNode(struct Node *n, int h, int key);

int search(struct Node *root, int key);

void insert(struct Node *root, int height, int key);

void helper(struct Node *root, struct Node *ptr, struct Node *prev, int key, int height);

struct Node *delete(struct Node *root, int key);

void deleteHelper(struct Node *root, struct Node *ptr, struct Node *prev);

void eraseBST(struct Node *root);

#endif
