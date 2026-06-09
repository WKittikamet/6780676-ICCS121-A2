#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Defining the LinkedList Node structure;
typedef strcut Node {
	struct Node *head;
	long amnt;
	char *desc;
	char *status
	struct Node *tail;
} Node;

// Functions used for LinkedList Nodes
void addlast(Node *list, long value, char *words);
void add(Node *list, long value, char *words, int pos, int length);
void dlt(Node *list, int pos);
void clear_memory(Node *list);
void print(Node *list);

#endif
