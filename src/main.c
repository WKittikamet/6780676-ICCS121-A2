#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/linkedlist.h"

int main(){
	char conf[100];
	Node *list = NULL;
	printf("**Starting the Program (Loading Previous Transactions)**\n");
	printf("\n**Original Log File (logs/transaction_log.txt) Before Running the Program:**\n");
	printf("```\n# Format: TYPE|DESCRIPTION|AMOUNT\n# TYPE: INC (Income) or EXP (Expense)\n# AMOUNT: Positive decimal number\n");
	printf("\nINC|Freelance Project|250.00\nEXP|Phone Bill|-45.00\nEXP|Electricity Bill|-100.00\n```\n");
	printf("\n**Program Startup Output:**\n");
	printf("\n```\nWelcome to your Personal Finance Tracker!\n");
	while(1) {
        	printf("Would you like to resume your previous session? (y/n): ");
		if (fgets(conf, sizeof(conf), stdin) != NULL) {
			conf[strcspn(conf, "\n")] = '\0';
			if (strcmp(conf, "y") == 0 || strcmp(conf, "n") == 0) {
				break;
			}
			else {
				printf("\nConfirmation not recognized\n");
			}
		}
	}
	if (strcmp(conf, "y") == 0){
		printf("Resuming from last session...\n");
		FILE *log = fopen("../logs/transaction_log", "r");
		if (log != NULL){
			list = (*Node)malloc(sizeof(Node));
			if (*list == NULL){
				printf("Node memory allocation failed");
				return 1;
			}
			/*
				Insert all contents from the transaction_log.txt into the list
				Do so by utilizing an 'insert_last' function
			*/
		}
		else {
			list = (*Node)malloc(sizeof(Node));
			printf("No previous transactions found. Continuing with new transaction.\n")
		}
	}
	printf("\nAvailable actions:\nadd income [amount] [description]\nadd income [amount] [description] [position]\n");
	printf("add expense [amount] [description]\nadd expense [amount] [description] [position]\ndelete [position]\nprint\nquit\n"
	while(1) {
		printf("\n> ");
		if (fgets(conf, sizeof(conf), stdin) != NULL) {
		// Get command -> Interpret and execute designated function -> repeat until 'quit'
		}
	}
	// Save all transactions into transaction_log.txt, clear memory and exit the program
	return 0;
}
