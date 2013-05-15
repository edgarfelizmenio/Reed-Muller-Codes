#ifndef REEDMULLER_C
#define REEDMULLER_C

#include"vector.c"
#include"matrix.c"
#include"monomial.c"
#include"list.c"

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
matrix *create_generator_matrix(int, list *);
vector **generate_characteristic_vectors(monomial *, int);
int majority_logic(vector *, monomial *, int);

vector *encode(vector*,int,int);
vector *decode(vector*,int,int);
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
    
	for (i = 0; i < mn->degree; i++) {
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
		for (i = 0; i < mn->degree; i++) {
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

list *generate_reduced_monomials(int r,int m) {
	list *reduced_monomials;
    list *gmonomials;
	list *gmonomial_group;
    
	generating_monomial *gm;
	
	gmonomials = create_list();
	reduced_monomials = create_list();
    
	gm = (generating_monomial*)malloc(sizeof(generating_monomial));
	
	gm->last_position = -1;
	gm->num_bits = 0;
	gm->mon = create_monomial(m);
	
	append(gmonomials, gm);
	
	while (!is_empty_list(gmonomials)) {
		gm = (generating_monomial*)remove_first(gmonomials);
		gmonomial_group = create_gmonomials(gm,r,m);
		merge_lists(gmonomials,gmonomial_group);
		
		append(reduced_monomials,gm->mon);
		
		free(gm);
	}    
    
    return reduced_monomials;
}

list *group_reduced_monomials(list* reduced_monomials, int r, int m) {
	int i, j, group_size;
	list *monomial_groups = create_list();
	list *monomial_group;
	
	for (i = 0, group_size = 1; i <= r; i++) {
		monomial_group = create_list();
		for (j = 0; j < group_size; j++) {
			append(monomial_group, remove_first(reduced_monomials));
		}
		append(monomial_groups, monomial_group);
		
		group_size = group_size * (m - i) / (i + 1);
	}
	
	return monomial_groups;
}

list *create_gmonomials(generating_monomial *ref, int r,  int m) {
	int i,j;
	list *gmonomial_group;
	generating_monomial *gm;
	generating_monomial *ngm;
	
	gm = ref;
	gmonomial_group = create_list();
	if (gm->num_bits < r) {
		for (i = gm->last_position + 1; i < gm->mon->degree; i++) {
			ngm = (generating_monomial *)malloc(sizeof(generating_monomial));
			ngm->num_bits = gm->num_bits + 1;
			ngm->mon = create_monomial(m);
			ngm->mon->coefficient = 1;
			
			for (j = 0; j <= gm->last_position; j++) {
				ngm->mon->exponents[j] = gm->mon->exponents[j];
			}
			
			ngm->last_position = i;
			ngm->mon->exponents[i] = 1;
			append(gmonomial_group,ngm);
		}
	}
	
	return gmonomial_group;
}

matrix *create_generator_matrix(int m, list *monomials) {
	int i,j;
	list *vectors;
	node *mnode;
	monomial *mon;
	matrix *generator_matrix;
	vector *row;
	
	vectors = create_list();
	mnode = monomials->head;

	while (mnode != NULL) {
		mon = (monomial*)get_value(mnode);
		mnode = mnode->next;
		append(vectors, psi_monomial(m,mon));
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

vector **generate_characteristic_vectors(monomial *mon, int m) {
    int i;
    list *characteristic_vectors = create_list();
    list *characteristic_vectors_temp;
	vector *characteristic_vector;
    
	vector *psi;
    vector *psi_inv;
	vector **characteristic_vector_array;
    
    characteristic_vector = create_vector(1<<m);
    for (i = 0; i < characteristic_vector->length; i++) {
        characteristic_vector->values[i] = 1;
    }
    append(characteristic_vectors,characteristic_vector);
		   
    for (i = 0; i < mon->degree; i++) {
        if (mon->exponents[i] == 0) {
            psi = psi_x(m,i);
            psi_inv = complement_vector(psi);
            characteristic_vectors_temp = create_list();
			
			while (!is_empty_list(characteristic_vectors)) {
				characteristic_vector = (vector*)remove_first(characteristic_vectors);
				append(characteristic_vectors_temp, multiply_vectors(characteristic_vector,psi));
				append(characteristic_vectors_temp, multiply_vectors(characteristic_vector,psi_inv));
				destroy_vector(characteristic_vector);
			}
			
			destroy_vector(psi);
			destroy_vector(psi_inv);
            destroy_list(characteristic_vectors);
			characteristic_vectors = characteristic_vectors_temp;
			characteristic_vectors_temp = NULL;
        }
    }

    characteristic_vector_array = (vector **)calloc(characteristic_vectors->length, sizeof(vector *));
    for (i = 0; !is_empty_list(characteristic_vectors); i++) {
        characteristic_vector_array[i] = (vector *)remove_first(characteristic_vectors);
    }
    destroy_list(characteristic_vectors);
    
    return characteristic_vector_array;
}

int majority_logic(vector *v, monomial * mon, int m) {
    int i, count_1;
    int num_vectors;
    vector *characteristic_vector;
    vector **characteristic_vectors = generate_characteristic_vectors(mon, m);
    num_vectors = 1;
    
    for (i = 0; i < mon->degree; i++) {
        if (mon->exponents[i] == 0) {
            num_vectors <<= 1;
        }
    }
    
    for (i = 0, count_1 = 0; i < num_vectors; i++) {
        if (dot_product(v, characteristic_vectors[i]) == 1) {
            count_1++;
        }
        destroy_vector(characteristic_vectors[i]);
    }
		
    free(characteristic_vectors);
    return count_1 * 2 >= num_vectors? 1:0;
}

vector *encode(vector* v,int r,int m) {	
	int i, j, num_chunks, pos_v, pos_e;
	vector *result, *chunk, *partial;
	node *rmnode;
	list *reduced_monomials = generate_reduced_monomials(r,m);
	matrix *generator_matrix = create_generator_matrix(m,reduced_monomials);
    
    num_chunks = (v->length / generator_matrix->num_rows) + (v->length % generator_matrix->num_rows > 0? 1:0);
    result = create_vector(num_chunks * generator_matrix->num_columns);
    
    for (i = 0, pos_v = 0, pos_e = 0; i < num_chunks; i++) {
        chunk = create_vector(generator_matrix->num_rows);
        for (j = 0; j < chunk->length && pos_v < v->length; j++, pos_v++) {
            chunk->values[j] = v->values[pos_v];
        }
        partial = lmultiply_vector(chunk, generator_matrix);
        for (j = 0; j < partial->length && pos_e < result->length; j++, pos_e++) {
            result->values[pos_e] = partial->values[j];
        }
        destroy_vector(partial);
        destroy_vector(chunk);
    }

	rmnode = reduced_monomials->head;
	while (rmnode != NULL) {
		destroy_monomial((monomial*)get_value(rmnode));
		rmnode = rmnode->next;
	}
	
	destroy_list(reduced_monomials);
	destroy_matrix(generator_matrix);
	return result;
}

vector *decode(vector* v, int r, int m) {
    int i,j,count_1, diff = 0;
    list *reduced_monomials = generate_reduced_monomials(r,m);
	vector *result = create_vector(reduced_monomials->length);
	list *monomial_groups = group_reduced_monomials(reduced_monomials,r,m);
	list *monomial_group;
	vector *majority, *s, *u = create_vector(v->length), *temp_vector;
	monomial *mon;
	matrix *generator_matrix;
	
	temp_vector = u;
	u = add_vectors(u,v);
	destroy_vector(temp_vector);
	
	j = result->length - 1;
	while (!is_empty_list(monomial_groups)) {
		monomial_group = (list *)pop(monomial_groups);
		
		majority = create_vector(monomial_group->length);
		generator_matrix = create_generator_matrix(m, monomial_group);
		
		i = 0;
		while (!is_empty_list(monomial_group)) {
			mon = (monomial *)remove_first(monomial_group);
			majority->values[i] = majority_logic(u,mon,m);
			i++;
			destroy_monomial(mon);
		}
		
		i = majority->length - 1;
		while (i >= 0) {
			result->values[j] = majority->values[i];
			i--;
			j--;
		}
		
		s = lmultiply_vector(majority,generator_matrix);

		temp_vector = u;
		u = add_vectors(u,s);

		destroy_vector(s);
		destroy_vector(temp_vector);
		destroy_list(monomial_group);
		destroy_vector(majority);
		destroy_matrix(generator_matrix);
	}
	
	destroy_vector(u);
	destroy_list(reduced_monomials);
	destroy_list(monomial_groups);
    return result;
}

#endif
