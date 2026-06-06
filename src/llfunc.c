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
	// Initialize the new transaction.
	Node *n = (Node*)malloc(sizeof(Node));
        if (n == NULL){
                printf("Node memory allocation failed");
                return;
        }
        n->amnt = value;
        // Allocate space for transaction description. The amount of memory corresponds to how long the description is.
        n->desc = (char*)malloc(strlen(words) + 1);
        strcpy(n->desc, words);
        // Allocate space for the status of the added transaction.
        n->stauts = (char*)malloc(strlen("(new)") + 1);
        strcpy(n->status, "(new)");

        if (*list == NULL){
                // In the case of an empty list, initialize the first node by having its head and tail point to eachother.
                n->tail = n;
                n->head = n;
                *list = n;
        }
        else {
                // Get both the first and last nodes.
                Node *first = *list;
                Node *last = list->head;

                // Set the last node's tail and the first node's head pointing to new transaction
                n->tail = first;
                n->head = last;
                last->tail = n;
                first->head = n;
        }
	/*
	***Past Code:***

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
	*/
}

/*
	add function:
		Add a node to the circular, dynamic linked list with information at position pos
*/
void add(Node **list, long value, char *words, int pos, int length){
	// Condtion for an out of bounds position.
	if (pos > length || pos < 0){
		printf("Position is out of bounds");
		return;
	}
	// Initialize the new transaction.
	Node *n = (Node*)malloc(sizeof(Node));
	if (n == NULL){
		printf("Node memory allocation failed");
		return;
	}
	n->amnt = value;
	n->desc = (char*)malloc(strlen(words) + 1);
	strcpy(n->desc, words);
	n->status = (char*)malloc(strlen("+++ i") + 1);
	strcpy(n->status, "+++ i");
	Node *current = *list;

	// Find the node at the designated position.
	if (pos > length/2){
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

	// Connect the ends.
	Node *prevNode = current->head;
	n->head = prevNode;
	n->tail = current;
	prevNode->tail = n;
	current->head = n;
	/*
	***Past Code:***

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
	return;*/
}

/*
	dlt function:
		Mark the node for deletion
*/
void dlt(Node **list, int pos, int length){
	if (pos >= length || pos < 0){
		printf("Position is out of bounds");
		return;
	}
	Node *current = *list;
	if (pos > length/2){
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

	free(current->status);
	current->status = (str*)malloc(strlen("--- d") + 1);
	strcpy(current->status, "--- d");
	/*
	***Past Code:***

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
	*/
}

/*
	clear_memory function:
		Clears all memory allocations
*/
void clear_memory(Node **list){
	if (*list == NULL){ return; }

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
	/*
	***Past Code:***

	Node *current = *list;
	Node *nextNode;
	// Loop through every Node and free memory from each one.
	while (current != NULL){
		nextNode = current->tail;
		free(current);
		current = nextNode;
	}
	*list = NULL;*/
}

/*
	print function:
		Prints the contents of the list, node by node, in the following format...
			[ Transactions ]
			1. [desc]   [amnt]   [status]
			2. [desc]   [amnt]   [status]
			3. [desc]   [amnt]   [status]
*/
void print(Node *list, int length){
	if (list == NULL){
		printf("[ Transactions ]\n(Empty)\n");
		return;
	}
	Node *current = list;
	printf("[ Transactions ]");
	for (int i = 0; i < length; i++){
		printf("%d. %s\t%.2f\t%s\n", i+1, current->desc, current->amnt, current->status);
		current = current->tail;
	}
}

