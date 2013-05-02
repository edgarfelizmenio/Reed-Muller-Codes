#ifndef REEDMULLER_C
#define REEDMULLER_C

#include"vector.c"
#include"matrix.c"
#include"monomial.c"
#include"list.c"

struct gmonomial {
	int last_position;
	int num_bits;
	monomial *mon;
};

typedef struct gmonomial gmonomial;

/* ================================================================================
	function prototypes for reed-muller functions
================================================================================ */
vector *psi_monomial(int, monomial *);
vector *psi_x(int,int);
matrix *create_generator_matrix(int,int);

/* ================================================================================
	function definitions for reed-muller functions
================================================================================ */

vector *psi_monomial(int m, monomial *mn) {
	vector *v = create_vector(1<<m);
	vector *mul1;
	vector *mul2;
	int i,j;
	int constant = 1;

    for (i = 0; i < v->length; i++) {
        v->values[i] = 1;
    }
    
	for (i = 0; i < mn->unknowns; i++) {
		if (mn->exponents[i] > 0) {
			constant = 0;
			break;
		}
	}

	if (mn->exponents == NULL || constant) {
		for (i = 0; i < v->length; i++) {
			v->values[i] = mn->coefficient;
		}
	} else if (mn->coefficient > 0) {
		for (i = 0; i < mn->unknowns; i++) {
			if (mn->exponents[i] > 0) {
				mul1 = v;
				mul2 = psi_x(m,i);
				v = multiply_vectors(mul1,mul2);
				destroy_vector(mul1);
				destroy_vector(mul2);
			}
		}		
	}
	return v;

}

vector *psi_x(int m, int pos) {
	int i,j;
	int num_ones = 1 << (m - pos - 1);
	vector *v = create_vector(1 << m);
	
	for (i = 0; i < num_ones; i++) {
		for (j = 0; i + j < v->length; j++) {
			v->values[i + j] = 1;
			j += num_ones + num_ones - 1;
		}
	}

	return v;	
}

matrix *create_generator_matrix(int r,int m) {
	int i,j;
    matrix *generator_matrix;
    gmonomial *ngm;
    gmonomial *gm;
    list *gmonomials;
    list *vectors;
    vector *row;
    
	gmonomials = create_list();
	vectors = create_list();
    
	gm = (gmonomial*)malloc(sizeof(gmonomial));

	gm->last_position = -1;
	gm->num_bits = 0;
	gm->mon = create_monomial(m);
	
	append(gmonomials, gm);

	while (!is_empty_list(gmonomials)) {
        
		gm = (gmonomial*)remove_first(gmonomials);
		
        print_monomial(gm->mon);
        append(vectors, psi_monomial(m,gm->mon));
		if (gm->num_bits < r) {
			for (i = gm->last_position + 1; i < gm->mon->unknowns; i++) {
				ngm = (gmonomial *)malloc(sizeof(gmonomial));
				ngm->num_bits = gm->num_bits + 1;
				ngm->mon = create_monomial(m);
				ngm->mon->coefficient = 1;
	
				for (j = 0; j <= gm->last_position; j++) {
					ngm->mon->exponents[j] = gm->mon->exponents[j];
				}

				ngm->last_position = i;
				ngm->mon->exponents[i] = 1;

				append(gmonomials,ngm);

			}
		}

		destroy_monomial(gm->mon);
		free(gm);

	}
    
    generator_matrix = create_matrix(vectors->length, 1 << m);
    
    for (i = 0; !is_empty_list(vectors); i++) {
        row = (vector *)remove_first(vectors);
        
        for (j = 0; j < generator_matrix->num_columns; j++) {
            set_matrix_value(generator_matrix, row->values[j], i, j);
        }

        destroy_vector(row);
    }
    
    
    return generator_matrix;
}

#endif
