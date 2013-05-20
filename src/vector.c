#ifndef VECTOR_C
#define VECTOR_C

#include <stdlib.h>

#include "common.c"

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
vector *add(vector *,vector *);
vector *complement_vector(vector *);
vector *multiply(vector *, vector *);
vector *subtract_vectors(vector *, vector *);
int compare_vectors(vector *, vector *);
int dot_product(vector *,vector *);
void destroy_vector(vector *);
void print_vector(vector*);

/* ================================================================================
	function definitions for vectors
================================================================================ */
vector *create_vector(int length) {
	vector *v = NULL;
	int i;	

	v = (vector*)malloc(sizeof(vector));
	v->length = length;
	v->values = (int*)calloc(length, sizeof(int));
	
	for (i = 0; i < length; i++) {
		v->values[i] = 0;
	}

	return v;
}

vector *scalar_add(vector *v, int a) {
	int i;
	vector *s = create_vector(v->length);

	for (i = 0; i < v->length; i++) {
		s->values[i] = (v->values[i] + a) % DEGREE;
	}

	return s;
}

vector *complement_vector(vector *v) {
	return scalar_add(v,1);
}

vector *multiply_vectors(vector *v1, vector *v2) {
	int i;
	vector *p = create_vector(v1->length);

	for (i = 0; i < v1->length; i++) {
		p->values[i] = (v1->values[i] * v2->values[i]) % DEGREE;
	}
	
	return p;
}

vector *add_vectors(vector *v1, vector *v2) {
	int i;
	vector *s;
    
    if (v1->length != v2->length) {
        printf("vector length mismatch!!!\n");
        exit(1);
    }
    
    s = create_vector(v1->length);

	for (i = 0; i < v1->length; i++) {
		s->values[i] = (v1->values[i] + v2->values[i]) % DEGREE;
	}

	return s;
}

int compare_vectors(vector *v1, vector *v2) {
	int i;
	for (i = 0 ; i < v1->length; i++) {
		if (v1->values[i] != v2->values[i]) {
			return v1->values[i] - v2->values[i];
		}
	}
	return 0;
}

int dot_product(vector *v1, vector *v2) {
    int i;
    int sum = 0;
    for (i = 0; i < v1->length; i++) {
        sum += (v1->values[i] * v2->values[i]) % DEGREE;
    }
    return sum % DEGREE;
}

void print_vector(vector *v) {
	int i;
    /*printf("length: %d\t",v->length);*/
	for (i = 0; i < v->length; i++) {
		printf("%d",v->values[i] & 1);
	}
    printf("\n");
}

void destroy_vector(vector *v) {
    if (v != NULL) {
        free(v->values);
        free(v);
        v = NULL;
    }
}

#endif
