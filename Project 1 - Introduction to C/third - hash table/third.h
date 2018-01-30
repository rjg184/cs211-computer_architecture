#ifndef _third_h
#define _third_h

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct hashtable {
	struct node **t;
} hashtable;

void buildNode(struct node *n, int num);

int search(struct hashtable *table, int key, int capacity, int index);

int makeIndex(int key, int capacity);

int findKey(struct node *ptr, int key);

int insert(struct hashtable *table, int key, int capacity, int index);

#endif
