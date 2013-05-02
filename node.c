#ifndef NODE_C
#define NODE_C

#include<stdlib.h>
#include<stdio.h>

struct node {
	void *value;
	struct node *previous;
	struct node *next;
};

typedef struct node node;


/* ================================================================================
	function prototypes for nodes
================================================================================ */
node *create_node(void *);
void destroy_node(node *);
void *get_value(node *);
void set_value(node *, void *);

/* ================================================================================
	function definitions for nodes
================================================================================ */
node *create_node(void *value) {
	node *n = (node *)malloc(sizeof(node));

	if (n == NULL) {
		printf("MEMORY OVERFLOW!!!");
		exit(1);
	}

	n->value = value;
	n->previous = NULL;
	n->next = NULL;
}

void destroy_node(node *n) {
	n->previous = NULL;
	n->next = NULL;
	n->value = NULL;
	free(n);
}

void *get_value(node *n) {
	return n->value;
}

void set_value(node *n, void *value) {
	n->value = value;
}




#endif
