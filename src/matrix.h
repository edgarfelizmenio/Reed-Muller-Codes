#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "vector.h"
#include "common.h"

struct matrix {
	int num_rows;
	int num_columns;
	int **values;
};

typedef struct matrix matrix;

/* ================================================================================
 function prototypes for matrices
 ================================================================================ */
matrix *create_matrix(int,int);
void destroy_matrix(matrix *);
void set_matrix_value(matrix *, int, int, int);
vector *lmultiply_vector(vector *, matrix *);
void print_matrix(matrix *);

#endif