#ifndef MONOMIAL_H
#define MONOMIAL_H

struct monomial {
	int degree;
	int *exponents;
	int coefficient;
};

typedef struct monomial monomial;

/* ================================================================================
 function prototypes for monomials
 ================================================================================ */
monomial *create_monomial(int);
monomial *get_reduced_monomial(monomial *);
void destroy_monomial(monomial *);
int compare_monomial(monomial *, monomial *);
void print_monomial(monomial *);

#endif