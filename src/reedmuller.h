#ifndef REEDMULLER_H
#define REEDMULLER_H

#include "vector.h"
#include "matrix.h"
#include "monomial.h"
#include "list.h"

struct generating_monomial {
	int last_position;
	int num_bits;
	monomial *mon;
};

typedef struct generating_monomial generating_monomial;

/* ================================================================================
 function prototypes for reed-muller functions
 ================================================================================ */
vector *psi_monomial(int, monomial *);
vector *psi_x(int,int);
list *create_gmonomials(generating_monomial *, int, int);
list *generate_reduced_monomials(int, int);
list *group_reduced_monomials(list *, int, int);

matrix *create_generator_matrix(int, list *);
vector **generate_characteristic_vectors(monomial *, int);
int majority(vector *, vector **, int);

vector *encode(vector*,int,int);
vector *decode(vector*,int,int);

#endif