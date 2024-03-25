#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
}  Node;

typedef struct queue {
	struct node *head;
	struct node *tail;
} Queue;

void enqueue(Queue **queue, int value);
Node * dequeue(Queue **queue);

int main() {
	Queue * queue = (Queue *) malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	enqueue(&queue, 1);
	enqueue(&queue, 2);
	enqueue(&queue, 3);
	printf("head queue %d\n", queue->head->value);
	printf("tail queue %d\n", queue->tail->value);
	Node *node = dequeue(&queue);
	printf("dequeued node value %d\n", node->value);
	free(node);
	node = dequeue(&queue);
        printf("dequeued node value %d\n", node->value);
	free(node);
	node = dequeue(&queue);
        printf("dequeued node value %d\n", node->value);
	free(node);
	free(queue);
	return 0;
}

void enqueue(Queue **queue, int value) {
	Node *node = (Node *) malloc(sizeof(Node));
	node->value = value;
	if ((*queue)->head == NULL) {
		(*queue)->head = node;
		(*queue)->tail = node;
	} else {
		(*queue)->tail->next = node;
		(*queue)->tail = node;		
	}

}

Node * dequeue(Queue **queue) {
	Node *node = NULL;
	if ((*queue)->head == (*queue)->tail){
		node = (*queue)->head;
		(*queue)->head = NULL;
		(*queue)->tail = NULL;
	} else {
		node = (*queue)->head;
		(*queue)->head = node->next;
	}
	return node;
}
