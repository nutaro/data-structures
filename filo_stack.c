#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * previous;
} Node;


Node * push(Node **list, int value);
Node * pop(Node **list);

int main() {
	Node *head = (Node *) malloc(sizeof(Node));
	head->previous = NULL;
	head->value = 1;
	head = push(&head, 2);
	head = push(&head, 3);
	head = pop(&head);
	head = pop(&head);
	free(head);
	return 0;
}

Node * push(Node **list, int value) {
	Node *node = (Node *) malloc(sizeof(Node));
	node->previous = *list;
	node->value = value;
	return node;
}

Node * pop(Node **list) {
	if ((*list)->previous == NULL)
		return *list;
	Node *pop = (*list)->previous;
	printf("removed value %d\n", (*list)->value);
	free(*list);
	return pop;
}
