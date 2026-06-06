#include <stdio.h>
#include <stdlib.h>
#include "../include/linkedlist.h"

/*
	Functions list:
		addlast
		add(position)
		delete(position)
		clear memory
		print
*/

/*
	addlast function:
		Adds a node at the end of the circular linked list.
		Connects the head of the first node and the tail of the last node to the new node, but at a position...
		...where it occurs at the end of the circular linked list before it wraps back to the first node.
*/
void addlast(Node *list, long value, char *words){
	Node *current = *list;
	Node *n = (Node*)malloc(sizeof(Node));
	if (n == NULL){
		printf("Node memory allocation failed");
                return;
	}
	n->amnt = value;
	n->desc = *words;
	n->stauts = "(new)";
	if (*list == NULL && pos = 0){
                n->head = NULL;
                n->tail = n->head;
                n->head = n->tail;
                current = n;
                return;
        }
	current = current->head;
	n->head = current;
        n->tail = current->tail;
        current->tail->head = n;
        current->tail = n;
        return;
}

/*
	add function:
		Add a node to the circular, dynamic linked list with information at position pos
*/
void add(Node *list, long value, char *words, int pos, int length){
	Node *current = *list;
	Node *n = (Node*)malloc(sizeof(Node));
	if (n == NULL){
		printf("Node memory allocation failed");
		return;
	}
	n->amnt = value;
        n->desc = *words;
	n->status = "+++ i";
	if (*list == NULL && pos = 0){
		n->head = NULL;
		n->tail = n->head;
		n->head = n->tail;
		current = n;
		return;
	}
	if (pos > length){
                printf("Location out of bounds");
                return;
        }
	else if (pos > length/2){
		current = current->head;
		for (int i = 0; i < length-pos; i++){
			current = current->head;
		}
	}
	else {
		for (int i = 0; i < pos; i++){
			current = current->tail;
		}
	}
        n->head = current->head;
        n->tail = current;
        current->head->tail = n;
        current->head = n;
        current=n;
	return;
};

/*
	dlt function:
		Mark the node for deletion
*/
void dlt(Node *list, int pos){
	Node *current = list;
	if (pos >= length){
                printf("Location out of bounds");
                return;
        }
        else if (pos > length/2){
                current = current->head;
                for (int i = 0; i < length-pos; i++){
                        current = current->head;
                }
        }
        else {
                for (int i = 0; i < pos; i++){
                        current = current->tail;
                }
        }
	current->status = "--- d";
	return;
};

/*
	clear_memory function:
		Clears all memory allocations
*/
void clear_memory(Node *list){
	Node *current = *list;
	Node *nextNode;
	// Loop through every Node and free memory from each one.
	while (current != NULL){
		nextNode = current->tail;
		free(current);
		current = nextNode;
	}
	*list = NULL;
};

/*
	print function:
		Prints the contents of the list, node by node, in the following format...
			[ Transactions ]
			1. [desc]   [amnt]   [status]
			2. [desc]   [amnt]   [status]
			3. [desc]   [amnt]   [status]
*/
void print(Node *list){

}
