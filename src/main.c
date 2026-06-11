#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/linkedlist.h"

int main(){
	// ---Variable Definition---
	char conf[200]; // conf will be used to read the user input
	long t = 0; // t is the total amount of currency left after all transactions (positive amount being within budget, negative amount being over budger)
	long *total = &t; // *total will be the pointer to t. We will be using a pointer in our functions so that we can update t.
	int l = 0; // l is the length of the circular, dynamic linked list.
	int *length = &l; // *length will be the pointer to l. Same purpose as *total
	char desc[100]; // desc will hold a description for a transaction until stored in a linked list node.
	long amnt; // amnt will hold the transaction amount until stored in a linked list node.
	char status[10]; // status will hold the status of the transaction until stored in a linked list node.
	Node *list = NULL; // *list will be are linked list. Initialize as a NULL pointer until we finish some pre-requisite checks

	// ---Intro Text---
	printf("**Starting the Program (Loading Previous Transactions)**\n");
	printf("\n**Original Log File (logs/transaction_log.txt) Before Running the Program:**\n");
	printf("```\n# Format: TYPE|DESCRIPTION|AMOUNT\n# TYPE: INC (Income) or EXP (Expense)\n# AMOUNT: Positive decimal number\n");
	printf("\nINC|Freelance Project|250.00\nEXP|Phone Bill|-45.00\nEXP|Electricity Bill|-100.00\n```\n");
	printf("\n**Program Startup Output:**\n");
	printf("\n```\nWelcome to your Personal Finance Tracker!\n");

	// Section 1: Asking for user input (reloading previous session)
	while(1) {
        	printf("\nWould you like to resume your previous session? (y/n): ");
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

	// Section 2: Reloading previous transaction_log.txt
        /*
                Insert all contents from the transaction_log.txt into the list
        	If transaction_log.txt is empty or doesn't exist, start with an empty list.
        */
	if (strcmp(conf, "y") == 0){
		printf("\nResuming from last session...\n\n");
		FILE *log = fopen("../logs/transaction_log.txt", "r");
		// Check if transaction_log.txt exists in the logs folder
		if (log != NULL){
			// conf is used to store the user inputed line
			while (fgets(conf, sizeof(conf), log) != NULL) {
				int p = sscanf(conf, "%s\t%ld\t%s", desc, &amnt, status);
				status[strcspn(status, "\n")] = '\0';
				addlast(&list, amnt, desc, length, total, status);
				printf("\n");
			}
			printf("\nLast session loaded.\n");
			fclose(log);
		}
		else {
			printf("\nNo previous transactions found. Continuing with new transaction.\n");
			fclose(log);
		}
	}

	// Section 3: Transaction Management
	printf("\nAvailable actions:\nadd income [amount] [description]\nadd income [amount] [description] [position]\n");
	printf("add expense [amount] [description]\nadd expense [amount] [description] [position]\ndelete [position]\nprint\nquit\n");
	printf("Disclaimer: [position] starts from 1\n");
	while(1) {
		/*
			Get command -> Interpret and execute designated function -> repeat until 'quit'
			Command function guidelines:
				if command == "add income [amount] [desc]" -> addlast(list, amount, desc)
									      ++length;
                                                                              total += amount;
				if command == "add expense [amount] [desc]" -> addlast(list, -(amount), desc)
                                                                              ++length;
                                                                              total -= amount;
				if command == "add income [amount] [desc] [pos]" -> add(list, amount, desc, pos, length)
                                                                                    ++length;
                                                                                    total += amount;
                                if command == "add expense [amount] [desc] [pos]" -> add(list, -(amount), desc, pos, length)
                                                                                     ++length;
                                                                                     total -= amount;
				if command == "delete [pos]" -> dlt(list, pos)
								--length;
                                                                total -= amount at pos;
				if command == "print" -> print(list)
		*/
                int wscount=0;
                char cmnd[10];
                char cmnd2[10];
                int pos;
		int p;
		printf("\nCurrent total: %ld\n", *total);
		if (*total >= (long)0){
                        printf("Budget Status: Within Budget\n");
		}
		else {
			printf("Budget Status: Over Budget!\n");
		}
		printf("```\n\n```");
                printf("\n> ");
                if (fgets(conf, sizeof(conf), stdin) != NULL) {
			conf[strcspn(conf, "\n")] = '\0';
			if (strcmp(conf, "quit") == 0) {
                                break;
                        }
			// Counting the whitespace between arguments helps indicate what command the user inputed
                        for(int i = 0; i < strlen(conf); i++){
                                if (conf[i] == ' '){ wscount++; }
                                if (wscount == 4){ break; }
                        }
                        switch(wscount){
				// Four whitespaces indicate adding an income/expense at a certain position
                                case 4:
                                        p = sscanf(conf, "%s %s %ld %s %d", cmnd, cmnd2, &amnt, desc, &pos);
					if (p == 5 && strcmp(cmnd, "add") == 0){
						if (amnt < (long)0){
							printf("\nInvalid transaction amount\n");
						}
                                        	else if (strcmp(cmnd2, "income") == 0){
                                                	add(&list, amnt, desc, pos-1, length, total);
							printf("\n");
                                        	}
                                        	else if (strcmp(cmnd2, "expense") == 0){
                                                	add(&list, -amnt, desc, pos-1, length, total);
                                                        printf("\n");
						}
                                                else {
                                                        printf("\nInvalid Command\n");
                                                }
					}
                                        else {
                                                printf("\nInvalid Command\n");
                                     	}
                                        break;
				// Three whitespaces indicate adding an income/expense with no location given
                                case 3:
                                        p = sscanf(conf, "%s %s %ld %s", cmnd, cmnd2, &amnt, desc);
					if (p == 4 && strcmp(cmnd, "add") == 0){
						if (amnt < (long)0){
                                                	printf("\nInvalid transaction amount\n");
						}
						else if (strcmp(cmnd2, "income") == 0){
                                                	addlast(&list, amnt, desc, length, total, "(new)");
                                        		printf("\n");
						}
                                        	else if (strcmp(cmnd2, "expense") == 0){
                                                	addlast(&list, -amnt, desc, length, total, "(new)");
                                        		printf("\n");
						}
						else {
							printf("\nInvalid Command\n");
						}
					}
					else {
						printf("\nInvalid Command\n");
					}
                                        break;
				// One whitespace indicate deleting a transaction at a certain position
                                case 1:
                                        p = sscanf(conf, "%s %d", cmnd, &pos);
					if (p == 2 && strcmp(cmnd, "delete") == 0){
						dlt(&list, pos-1, length, total);
						printf("\n");
					}
					else{
						printf("\nInvalid Command\n");
					}
                                        break;
				// No whitespace indicates print
                                default:
					if (strcmp(conf, "print") == 0){
						print(list, length);
					}
					else {
						printf("\nInvalid Command\n");
					}
					break;
                        }
		}
	}

	// Section 4: Saving and Clearing
	/*
                Save all transactions into ../logs/transaction_log.txt, clear memory and exit the program

                If no transaction_log.txt exists, create a new one in ../logs/.
                Else if one does exist, then we overwrite it and save our current transactions

                Saving to transaction_log.txt goes as follows:
                        if the status of a node is "--- d", then they will not be saved saved onto transaction_log.txt
                        Otherwise, save each node's amnt, desc and status as "(saved)" into their own lines in transaction_log.txt in the following format:
                                [desc]  [amnt]  (saved)
        */
	printf("\nSaving transactions to file...\n\n");
	FILE *log = fopen("../logs/transaction_log.txt", "w");
	if (log == NULL){
		printf("\nUnable to save\n");
		clear_memory(&list);
		return 1;
	}
	if (list != NULL) {
		printf("# Format: TYPE|DESCRIPTION|AMOUNT\n# TYPE: INC (Income) or EXP (Expense)\n# AMOUNT: Positive decimal number\n\n");
		Node *current = list;
		for (int i = 0; i < *length; i++){
			if (strcmp(current->status, "--- d") == 0){
				printf("- **%s (%ld) was removed**\n", current->desc, current->amnt);
				current = current->tail;
				continue;
			}
			else {
				fprintf(log, "%s\t%ld\t(saved)\n", current->desc, current->amnt);
				if (strcmp(current->status, "+++ i") == 0){
					if (current->amnt >= (long)0){
                                        	printf("INC(insert)|%s|%ld\n", current->desc, current->amnt);
                                	}
                                	else {
                                        	printf("EXP(insert)|%s|%ld\n", current->desc, current->amnt);
                                	}
				}
				else if (current->amnt >= (long)0){
	                                printf("INC%s|%s|%ld\n", current->status, current->desc, current->amnt);
				}
				else {
	                                printf("EXP%s|%s|%ld\n", current->status, current->desc, current->amnt);
				}
			}
			current = current->tail;
		}
	}
	fclose(log);
	clear_memory(&list);
	printf("\nDone. Exiting program.\n");
	return 0;
}
