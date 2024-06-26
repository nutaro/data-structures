#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *left;
	struct node *right;
	int height;
} Node;

int max(int a, int b);

int get_height(Node *node);

int get_balance(Node *node);

Node * create_node(int value);

Node * right_rotate(Node *node);

Node * left_rotate(Node *node);

Node * insert_node(Node *node, int value);

Node * delete_node(Node *head, int value);

Node * minimal_value_node(Node *node);

void print_tree(Node *head);

int main() {
	Node *head = NULL;

	head = insert_node(head, 2);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 1);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 7);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 4);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 5);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 3);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 8);
	print_tree(head);
	printf("\n");
	head = insert_node(head, 9);
	print_tree(head);
	printf("\n");


	head = delete_node(head, 4);

	printf("\nAfter delete\n");

	print_tree(head);
}

Node * insert_node(Node *node, int value) {
	if (node == NULL)
		return create_node(value);
	if (value < node->value)
		node->left = insert_node(node->left, value);
	else if (value > node->value)
		node->right = insert_node(node->right, value);
	else
		return node;
	
	node->height = 1 + max(get_height(node->left), get_height(node->right));

	int balance = get_balance(node);

	if (balance > 1 && value < node->left->value)
		return right_rotate(node);
	if (balance < -1 && value > node->right->value)
		return left_rotate(node);
	
	if (balance > 1 && value > node->left->value) {
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if (balance < -1 && value < node->right->value) {
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

Node * create_node(int value) {
	Node *node  = (Node *) malloc(sizeof(Node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;	
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int get_height(Node *node) {
	if (node == NULL)
		return 0;
	return node->height;
}

int get_balance(Node *node) {
	if (node == NULL)
		return 0;
	return get_height(node->left) - get_height(node->right);
}

Node * right_rotate(Node *node) {
	Node *temp_one = node->left;
	Node *temp_two = temp_one->right;

	temp_one->right = node;
	node->left = temp_two;

	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	temp_one->height = max(get_height(temp_one->left), get_height(temp_one->right)) + 1;

	return temp_one;
}

Node * left_rotate(Node *node) {
	Node *temp_one = node->right;
	Node *temp_two = temp_one->left;

	temp_one->left = node;
	node->right = temp_two;

	node->height = max(get_height(node->left), get_height(node->right)) + 1;
    temp_one->height = max(get_height(temp_one->left), get_height(temp_one->right)) + 1;

	return temp_one;
}

Node * delete_node(Node *head, int value) {
	if (head == NULL)
		return head;

	if (value < head->value)
		head->left = delete_node(head->left, value);
	else if (value > head->value)
		head->right = delete_node(head->right, value);
	else {
		if ((head->left == NULL) || (head->right == NULL)) {
			Node *temp = head->left ? head->left : head->right;
			if (temp == NULL) {
				temp = head;
				head = NULL;
			} else
				*head = *temp;
			free(temp);
		} else { 
			Node *temp = minimal_value_node(head->right);
			head->value = temp->value;
			head->right = delete_node(head->right, head->value);
		}
	}

	if (head == NULL)
		return head;

	head->height = 1 + max(get_height(head->left), get_height(head->right));

  	int balance = get_balance(head);
  	if (balance > 1 && get_balance(head->left) >= 0)
    	return right_rotate(head);

  	if (balance > 1 && get_balance(head->left) < 0) {
    	head->left = left_rotate(head->left);
    	return right_rotate(head);
  	}

  	if (balance < -1 && get_balance(head->right) <= 0)
    	return left_rotate(head);

  	if (balance < -1 && get_balance(head->right) > 0) {
    	head->right = right_rotate(head->right);
    	return left_rotate(head);
  	}
  	return head;
}

Node * minimal_value_node(Node *node) {
	Node *current = node;
	while (current->left != NULL)
    	current = current->left;

  	return current;
}

void print_tree(Node *head) {
	if (head != NULL) {
    printf("%d ", head->value);
    print_tree(head->left);
    print_tree(head->right);
  }
}