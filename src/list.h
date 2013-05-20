#ifndef LIST_H
#define LIST_H

struct node {
	void *value;
	struct node *previous;
	struct node *next;
};

typedef struct node node;

struct list {
	node *head;
	node *tail;
	int length;
};

typedef struct list list;

/* ================================================================================
 function prototypes for nodes
 ================================================================================ */
node *create_node(void *);
void destroy_node(node *);
void *get_value(node *);
void set_value(node *, void *);

/* ================================================================================
 function prototypes for lists
 ================================================================================ */
list *create_list(void);
int is_empty_list(list *);
void append(list *,void *);
void *pop(list *);
void *remove_first(list *);
void destroy_list(list *);
void insert_left(list *, node *,void *);
void delete_node(list *,node *);
void merge_lists(list *, list *);

#endif