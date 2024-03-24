#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node *next;
} Node;


void fill_list(Node *list);
void print_list(Node *list);
void free_resources(Node *list);


int main() {
	Node *head = NULL;
	head = (Node *) malloc(sizeof(Node));
	if(head == NULL)
		return 1;
	fill_list(head);
	print_list(head);
	free_resources(head);
	return 0;
}

void fill_list(Node *list) {
	Node *current = list;
	for (int i = 0;  i < 10; i++) {
		current->value = i;
		if(i <= 9)
			current->next = (Node *) malloc(sizeof(Node));
		current = current->next;

	}
	current->next = NULL;

}

void print_list(Node *list) {
	Node *current = list;
	while(current->next != NULL) {
		printf("%d \n", current->value);
		current = current->next;
	}
}

void free_resources(Node *list) {
	Node *current = list;
	while (current != NULL){
		Node *next = current->next;
		free(current);
		current = next;
	}
}

