#ifndef VECTOR_H
#define VECTOR_H

struct vector {
	int *values;
	int length;
};

typedef struct vector vector;

/* ================================================================================
 function prototypes for vectors
 ================================================================================ */
vector *create_vector(int);
vector *scalar_add(vector *, int);
vector *add_vectors(vector *,vector *);
vector *complement_vector(vector *);
vector *multiply_vectors(vector *, vector *);
vector *subtract_vectors(vector *, vector *);
int compare_vectors(vector *, vector *);
int dot_product(vector *,vector *);
void destroy_vector(vector *);
void print_vector(vector*);

#endif