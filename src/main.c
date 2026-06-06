#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/linkedlist.h"

int main(){
	char conf[100];
	long total;
	int length;
	Node *list = NULL;
	printf("**Starting the Program (Loading Previous Transactions)**\n");
	printf("\n**Original Log File (logs/transaction_log.txt) Before Running the Program:**\n");
	printf("```\n# Format: TYPE|DESCRIPTION|AMOUNT\n# TYPE: INC (Income) or EXP (Expense)\n# AMOUNT: Positive decimal number\n");
	printf("\nINC|Freelance Project|250.00\nEXP|Phone Bill|-45.00\nEXP|Electricity Bill|-100.00\n```\n");
	printf("\n**Program Startup Output:**\n");
	printf("\n```\nWelcome to your Personal Finance Tracker!\n");
	while(1) {
        	printf("Would you like to resume your previous session? (y/n): ");
		// Read the line of text from input(stdin)
		if (fgets(conf, sizeof(conf), stdin) != NULL) {
			// Replace the newline with a null terminator for the if-conditions
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
			length=0;
			/*
				Insert all contents from the transaction_log.txt into the list:
					Each line in transaction_log must have the description, amount and status preserved when inserted into a node.
				Do so by utilizing 'addlast' function. Add 1 to length at every addition.
			*/
		}
		else {
			list = (*Node)malloc(sizeof(Node));
			if (*list == NULL){
                       		printf("Node memory allocation failed");
                        	return 1;
                	}
                	length=0;
			printf("No previous transactions found. Continuing with new transaction.\n")
		}
	}
	else {
		list = (*Node)malloc(sizeof(Node));
        	if (*list == NULL){
                	printf("Node memory allocation failed");
                        return 1;
       		}
		length=0;
	}
	printf("\nAvailable actions:\nadd income [amount] [description]\nadd income [amount] [description] [position]\n");
	printf("add expense [amount] [description]\nadd expense [amount] [description] [position]\ndelete [position]\nprint\nquit\n"
	while(1) {
		printf("\n> ");
		if (fgets(conf, sizeof(conf), stdin) != NULL) {
		/*
			Get command -> Interpret and execute designated function -> repeat until 'quit'
			Command function guidelines:
				if command == "add income [amount] [desc]" -> addlast(list, amount, desc)
									      ++length;
				if command == "add expense [amount] [desc]" -> addlast(list, -(amount), desc)
                                                                              ++length;
				if command == "add income [amount] [desc] [pos]" -> add(list, amount, desc, pos, length)
                                                                                    ++length;
                                if command == "add expense [amount] [desc] [pos]" -> add(list, -(amount), desc, pos, length)
                                                                                     ++length;
				if command == "delete [pos]" -> dlt(list, pos)
								--length;
				if command == "print" -> print(list)
		*/
		}
	}
	/*
		Save all transactions into ../logs/transaction_log.txt, clear memory and exit the program

		If no transaction_log.txt exists, create a new one in ../logs/.
		Else if one does exist, then we overwrite it and save our current transactions

		Saving to transaction_log.txt goes as follows:
			if the status of a node is "--- d", then they will not be saved saved onto transaction_log.txt
			Otherwise, save each node's amnt, desc and status as "(saved)" into their own lines in transaction_log.txt in the following format:
				[desc]	[amnt]	(saved)
	*/
	return 0;
}
