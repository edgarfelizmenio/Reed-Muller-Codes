#ifndef VECTOR_C
#define VECTOR_C

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "vector.h"

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
		if (v1->values[i] % DEGREE != v2->values[i] % DEGREE) {
			return v1->values[i] - v2->values[i];
		}
	}
	return 0;
}

int dot_product(vector *v1, vector *v2) {
    int i;
    int sum = 0;
    for (i = 0; i < v1->length; i++) {
        sum += ((v1->values[i] % DEGREE) * (v2->values[i] % DEGREE)) % DEGREE;
    }
    return sum % DEGREE;
}

void print_vector(vector *v, FILE *outputstream) {
	int i;
    /*printf("length: %d\t",v->length);*/
	for (i = 0; i < v->length; i++) {
		if (v->values[i] == -1) {
			fprintf(outputstream, "*");
		} else {
			fprintf(outputstream, "%d",v->values[i] & 1);
		}
	}
    fprintf(outputstream, "\n");
}

int distance(vector *v1, vector *v2) {
	int i,d;
	if (v1->length != v2->length) {
		printf("vector length mismatch!\n");
		exit(1);
	}
	
	for (i = 0, d = 0; i < v1->length; i++) {
		if (v1->values[i] % DEGREE != v2->values[i] % DEGREE) {
			d++;
		}
	}
	
	return d;
}

void destroy_vector(vector *v) {
    if (v != NULL) {
        free(v->values);
        free(v);
        v = NULL;
    }
}

#endif
