// Defining the LinkedList Node structure;
typedef strcut Node {
	struct Node *head;
	long amnt;
	char *desc;
	struct Node *tail;
} Node;

// Functions used for LinkedList Nodes
void add(Node **list, long value, char *str, int pos);
void dlt(Node **list, int pos);
void clearmem(Node **list);
