#ifndef _eighth_h
#define _eighth_h

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

#endif
