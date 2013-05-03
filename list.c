#ifndef LIST_C
#define LIST_C

#include<stdlib.h>
#include<stdio.h>
#include"node.c"

struct list {
	node *head;
	node *tail;
	int length;
};

typedef struct list list;

/* ================================================================================
	function prototypes for lists
================================================================================ */
list *create_list(void);
int is_empty_list(list *);
void append(list *,void *);
void *pop(list *);
void *remove_first(list *);
void destroy_list(list *);
void insert_left(list *, node *ref,void *);
void delete_node(list *,node *);
void merge_lists(list *, list *);

/* ================================================================================
	function definitions for lists
================================================================================ */
list *create_list() {
	list *l = (list*)malloc(sizeof(list));
	l->head = NULL;
	l->tail = NULL;
	l->length = 0;
	return l;
}

int is_empty_list(list *l) {
	return (l->head == NULL) && (l->tail == NULL) && (l->length == 0);
}

void append(list *l, void *item) {
	node* n = create_node(item);	

	if (is_empty_list(l)) {
		l->head = l->tail = n;
	} else {
		l->tail->next = n;
		n->previous = l->tail;
        l->tail = l->tail->next;
	}
	l->length++;
}

void insert_left(list *l, node *ref,void *item) {
	node *n = create_node(item);

	if (is_empty_list(l)) {
		l->head = l->tail = n;
	} else if (ref == NULL) {
		n->next = l->head;
		l->head->previous = n;
		l->head = n;
	} else {
		n->next = ref;
		n->previous = ref->previous;
		if (ref->previous != NULL) {
			ref->previous->next = n;
		}
		ref->previous = n;
	}

	l->length++;
}

void *pop(list *l) {
	void *result;
	node *temp;
	
	if (is_empty_list(l)) {
		printf("Memory underflow!");
		exit(1);
	}

	temp = l->tail;
	l->tail = l->tail->previous;
	if (l->tail != NULL) {
		l->tail->next = NULL;
	} else {
        l->head = NULL;
    }
	result = temp->value;
	destroy_node(temp);

	l->length--;
	return result;
}

void *remove_first(list *l) {
	void *result;
	node *temp;

	if (is_empty_list(l)) {
		printf("Memory underflow!");
		exit(1);
	}

	temp = l->head;
	l->head = l->head->next;
	if (l->head != NULL) {
		l->head->previous = NULL;
	} else {
        l->tail = NULL;
    }

	result = temp->value;
	destroy_node(temp);
    l->length--;
	return result;
}

void destroy_list(list *l) {
	node *temp = l->head;
	node *i = temp;
	while (temp != NULL) {
		temp = temp->next;
		destroy_node(i);
		i = temp;
		l->length--;
	}
	free(l);
	l = NULL;
}

void delete_node(list *l, node *n) {
	if (l->head == l->tail && n == l->head) {
		l->head = l->tail = NULL;
	} else if (n->previous == NULL && n == l->head) {
		l->head = l->head->next;
		l->head->previous = NULL;
		destroy_node(n);
	} else if (n->next == NULL && n == l->tail) {
		l->tail = l->tail->previous;
		l->tail->next = NULL;
		destroy_node(n);
	} else {
		n->previous->next = n->next;
		n->next->previous = n->previous;
	}
	destroy_node(n);
	l->length--;
}

void merge_lists(list *l1, list *l2) {
	if (is_empty_list(l1)) {
		l1->head = l2->head;
		l1->tail = l2->tail;
		l1->length = l2->length;
	} else if (!is_empty_list(l2)) {
		l1->tail->next = l2->head;
		l2->head->previous = l1->tail;
		l1->tail = l2->tail;
		l1->length = l1->length + l2->length;
	}
	l2->head = NULL;
	l2->tail = NULL;
	l2->length = 0;
	destroy_list(l2);
}


#endif
