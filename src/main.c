#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/linkedlist.h"

int main(){
	char conf[10];
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
			
		}
		else {
			printf("No previous transactions found. Continuing with new transaction.\n")
		}
	}
	printf("You chose: %s\n", conf);
	return 0;
}
