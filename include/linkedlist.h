#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Defining the LinkedList Node structure;
typedef struct Node {
	struct Node *head;
	long amnt;
	char *desc;
	char *status;
	struct Node *tail;
} Node;

// Functions used for LinkedList Nodes
void addlast(Node **list, long value, char *words, int *length, long *total, char *stat);
void add(Node **list, long value, char *words, int pos, int *length, long *total);
void dlt(Node **list, int pos, int *length, long *total);
void clear_memory(Node **list);
void print(Node *list, int *length);

#endif
