#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"

/*
	addlast function:
		Adds a node at the end of the circular linked list. Essentially, we want to updated the list with a new node at the end of the list.
		Connects the head of the first node and the tail of the last node to the new node, but at a position...
		...where it occurs at the end of the circular linked list before it wraps back to the first node.
*/
void addlast(Node **list, long value, char *words, int *length, long *total, char *stat){
	// Initialize the new transaction.
	Node *n = (Node*)malloc(sizeof(Node));
        if (n == NULL){
                printf("\nNode memory allocation failed\n");
		printf("\nFailed to add transaction\n");
                return;
        }
        n->amnt = value;
        // Allocate space for transaction description. The amount of memory corresponds to how long the description is.
        n->desc = (char*)malloc(strlen(words) + 1);
        strcpy(n->desc, words);
        // Allocate space for the status of the added transaction.
        n->status = (char*)malloc(strlen(stat) + 1);
        strcpy(n->status, stat);

        if (*list == NULL){
                // In the case of an empty list, initialize the first node by having its head and tail point to each other.
                n->tail = n;
                n->head = n;
                *list = n;
        }
        else {
                // Get both the first and last nodes.
                Node *first = *list;
                Node *last = first->head;

                // Set the last node's tail and the first node's head pointing to new transaction
                n->tail = first;
                n->head = last;
                last->tail = n;
                first->head = n;
        }
	if (value >= (long)0){
        	printf("Income added.");
	}
	else {
        	printf("Expense added.");
	}
        // Update the total number of currency after transactions and the length of the list.
        *total += value;
        (*length)++;
}

/*
	add function:
		Add a node to the circular, dynamic linked list with information at position pos.
		Update the list with a node at position pos with the following information.
*/
void add(Node **list, long value, char *words, int pos, int *length, long *total){
	// Condition for an out of bounds position.
	if (pos > *length || pos < 0){
		printf("\nPosition is out of bounds\n");
		printf("\nFailed to add transaction\n");
		return;
	}
	// Initialize the new transaction.
	Node *n = (Node*)malloc(sizeof(Node));
	if (n == NULL){
		printf("\nNode memory allocation failed\n");
		printf("\nFailed to add transaction\n");
		return;
	}
	n->amnt = value;
	// Allocate space for the description and status of the transaction
	n->desc = (char*)malloc(strlen(words) + 1);
	strcpy(n->desc, words);
	n->status = (char*)malloc(strlen("+++ i") + 1);
	strcpy(n->status, "+++ i");
	Node *current = *list;

	// Find the node at the designated position.
	if (pos > *length/2){
		current = current->head;
		for (int i = 0; i < *length-pos; i++){
                	current = current->head;
        	}
	}
	else {
		for (int i = 0; i < pos; i++){
                	current = current->tail;
       		}
	}

	// Connect the ends.
	Node *prevNode = current->head;
	n->head = prevNode;
	n->tail = current;
	prevNode->tail = n;
	current->head = n;

	if (pos == 0) {
                *list = n;
        }

	if (value >= (long)0){
                printf("Income added at position %d.", pos+1);
        }
        else {
                printf("Expense added at position %d.", pos+1);
        }
        // Update the total number of currency after transactions and the length of the list.
        *total += value;
        (*length)++;
}

/*
	dlt function:
		Mark the node for deletion. Update the node in the list with a "deletion" status --> status of "--- d"
		Additionally, this function will return the transaction amount for the purpose of deducting the total.
*/
void dlt(Node **list, int pos, int *length, long *total){
	// Check if the given position is out of bounds of the length of the list.
	if (pos >= *length || pos < 0){
		printf("\nPosition is out of bounds\n");
		printf("\nFailed to mark transaction for deletion\n");
		return;
	}
	if (*list == NULL){
		printf("\nNo transactions exists to delete\n");
		printf("Failed to mark transaction for deletion\n");
		return;
	}
	Node *current = *list;
	/*
		For a position that is past half way the length of the list, then we will traverse the list from the tail to the head
		Otherwise, traverse normally from the head to the tail
	*/
	if (pos > *length/2){
		for (int i = 0; i < *length-pos; i++){
			current = current->head;
		}
	}
	else {
		for (int i = 0; i < pos; i++){
			current = current->tail;
		}
	}

	free(current->status);
	current->status = (char*)malloc(strlen("--- d") + 1);
	strcpy(current->status, "--- d");
	*total -= current->amnt;
	printf("Transaction at position %d marked for deletion.", pos+1);
	return;
}

/*
	clear_memory function:
		Clears all memory allocations
*/
void clear_memory(Node **list){
	if (*list == NULL || list == NULL){ return; }

	Node *current = *list;
	Node *nextNode;
	current->head->tail = NULL;

	while (current != NULL){
		nextNode = current->tail;
		free(current->desc);
		free(current->status);
		free(current);
		current = nextNode;
	}

	*list = NULL;
	printf("\nMemory cleared\n");
}

/*
	print function:
		Prints the contents of the list, node by node, in the following format...
			[ Transactions ]
			1. [desc]   [amnt]   [status]
			2. [desc]   [amnt]   [status]
			3. [desc]   [amnt]   [status]
*/
void print(Node *list, int *length){
	if (list == NULL){
		printf("[ Transactions ]\n(Empty)\n");
		return;
	}
	Node *current = list;
	printf("[ Transactions ]\n");
	for (int i = 0; i < *length; i++){
		printf("%d. %s\t%ld\t%s\n", i+1, current->desc, current->amnt, current->status);
		current = current->tail;
	}
}

