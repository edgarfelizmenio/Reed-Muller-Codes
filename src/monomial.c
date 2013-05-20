#ifndef MONOMIAL_C
#define MONOMIAL_C

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "monomial.h"

/* ================================================================================
	function definitions for monomials
================================================================================ */
monomial *create_monomial(int degree) {
	int i;
	monomial *m = (monomial*)malloc(sizeof(monomial));
	m->degree = degree;
	m->coefficient = 1;
	if (degree > 0) {
		m->exponents = (int*)calloc(m->degree,sizeof(int));	
		for (i = 0; i < m->degree; i++){
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
	reduced->degree = m->degree;
	reduced->coefficient = m->coefficient;

	if (reduced->degree > 0) {
		reduced->exponents = (int *)calloc(reduced->degree,sizeof(int));
		
		for (i = 0; i < reduced->degree; i++) {
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
}

int compare_monomial(monomial *m1, monomial *m2) {
	int i;
	if (m1->degree != m2->degree) {
		if (m1->degree < m2->degree) {
			return -1;
		}
		return 1;
	}
	else if (m1->degree == 0){
		if (m1->coefficient < m2->coefficient) {
			return -1;
		} else if (m1->coefficient > m2->coefficient) {
			return 1;
		}
		return 0;
	} else {
		for (i = 0; i < m1->degree; i++) {
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
    printf("%d\t",mn->degree);
	for (i = 0; i < mn->degree; i++) {
		printf("%d",mn->exponents[i] & 1);
	}
	printf("\n");
}

#endif
