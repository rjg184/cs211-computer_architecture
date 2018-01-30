#ifndef _second_h
#define _second_h

typedef struct node{
	int data;
	struct node *next;
} node;

void insert(struct node **front, int value);

void delete(struct node **front, int value);

void printLL(struct node *front);

void freeLL(struct node **front);

#endif
