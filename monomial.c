#ifndef MONOMIAL_C
#define MONOMIAL_C

#include<stdlib.h>

struct monomial {
	int unknowns;
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

/* ================================================================================
	function definitions for monomials
================================================================================ */
monomial *create_monomial(int unknowns) {
	int i;
	monomial *m = (monomial*)malloc(sizeof(monomial));
	m->unknowns = unknowns;
	m->coefficient = 1;
	if (unknowns > 0) {
		m->exponents = (int*)calloc(m->unknowns,sizeof(int));	
		for (i = 0; i < m->unknowns; i++){
			m->exponents[i] = 0;
		}
	} else {
		m->exponents = NULL;
	}
	
	return m;
}

monomial *get_reduced_monomial(monomial *m) {
	int i;	
	monomial *reduced = (monomial*)malloc(sizeof(monomial));
	reduced->unknowns = m->unknowns;
	reduced->coefficient = m->coefficient;

	if (reduced->unknowns > 0) {
		reduced->exponents = (int *)calloc(reduced->unknowns,sizeof(int));
		
		for (i = 0; i < reduced->unknowns; i++) {
			reduced->exponents[i] = m->exponents[i];
		}

	} else {
		reduced->exponents = NULL;
	}
	return reduced;
}

void destroy_monomial(monomial *m) {
	free(m->exponents);
    m->exponents = NULL;
	free(m);
    m = NULL;
}

int compare_monomial(monomial *m1, monomial *m2) {
	int i;
	if (m1->unknowns != m2->unknowns) {
		if (m1->unknowns < m2->unknowns) {
			return -1;
		}
		return 1;
	}
	else if (m1->unknowns == 0){
		if (m1->coefficient < m2->coefficient) {
			return -1;
		} else if (m1->coefficient > m2->coefficient) {
			return 1;
		}
		return 0;
	} else {
		for (i = 0; i < m1->unknowns; i++) {
			if (m1->exponents[i] < m2->exponents[i]) {
				return -1;
			} else if (m1->exponents[i] > m2->exponents[i]) {
				return 1;
			} else {
				if (m1->coefficient < m2->coefficient) {
					return -1;
				} else if (m1->coefficient > m2->coefficient) {
					return 1;
				}
			}
		}
		return 0;
	}
}

void print_monomial(monomial *mn) {
	int i;
    printf("monomial: ");
    printf("%d\t",mn->unknowns);
	for (i = 0; i < mn->unknowns; i++) {
		printf("%d",mn->exponents[i] & 1);
	}
	printf("\n");
}

#endif
