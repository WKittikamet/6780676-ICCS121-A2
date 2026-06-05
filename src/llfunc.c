#include <stdio.h>
#include <stdlib.h>
#include "../include/linkedlist.h"

// Add a node to the circular, dynamic linked list with information at position pos
void add(Node *list, long value, char *words, int pos, int length){
	Node *current = *list;
	Node *n = (Node*)malloc(sizeof(Node));
	if (n == NULL){
		printf("Node memory allocation failed");
		return;
	}
	n->amnt = value;
        n->desc = *words;
	if (*list == NULL && pos = 0){
		n->head = NULL;
		n->tail = NULL;
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

// Delete node at position pos
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
	current->head->tail = current->tail;
	current->tail->head = current->head;
	free(current);
	return;
};

// Clears all memory allocations
void clear_memory(Node *list){
	Node *current = *list;
	Node *nextNode;
	// Looping through every Node and free memory from each one.
	while (current != NULL){
		nextNode = current->tail;
		free(current);
		current = nextNode;
	}
	*list = NULL;
};
