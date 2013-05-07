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
list *generate_characteristic_vectors(monomial *, int);
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

list *generate_characteristic_vectors(monomial *mon, int m) {
    int i,j,length;
    list *characteristic_vectors = create_list();
    vector *characteristic_vector = create_vector(1<<m);
    vector *psi;
    vector *psi_inv;
    
    for (i = 0; i < characteristic_vector->length; i++) {
        characteristic_vector->values[i] = 1;
    }
    
    append(characteristic_vectors, characteristic_vector);
    
    for (i = 0; i < mon->degree; i++) {
        if (mon->exponents[i] == 0) {
            psi = psi_x(m,i);
            psi_inv = complement_vector(psi);
            
            j = characteristic_vectors->length;

            
            for (; j > 0; j--) {
                characteristic_vector = remove_first(characteristic_vectors);

                append(characteristic_vectors, multiply_vectors(characteristic_vector,psi));
                append(characteristic_vectors, multiply_vectors(characteristic_vector,psi_inv));

                destroy_vector(characteristic_vector);
            }
            
            destroy_vector(psi);
            destroy_vector(psi_inv);
        }
    }
    return characteristic_vectors;
}

int majority_logic(vector *v, monomial * mon, int m) {
    int count_1 = 0;
    int num_vectors;
    vector *characteristic_vector;
    list *characteristic_vectors = generate_characteristic_vectors(mon, m);
    num_vectors = characteristic_vectors->length;
    
    while (!is_empty_list(characteristic_vectors)) {
        characteristic_vector = remove_first(characteristic_vectors);
        count_1 += dot_product(v,characteristic_vector);
        destroy_vector(characteristic_vector);
    }
    destroy_list(characteristic_vectors);
    return count_1 * 2 >= num_vectors? 1:0;
}

vector *encode(vector* v,int r,int m) {	
	vector *result, *errors;
	node *rmnode;
	list *reduced_monomials = generate_reduced_monomials(r,m);
	matrix *generator_matrix = create_generator_matrix(m,reduced_monomials);
    
	result = lmultiply_vector(v, generator_matrix);

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
    int i,j, count_1;
     
    list *reduced_monomials = generate_reduced_monomials(r,m);
    vector *result = create_vector(reduced_monomials->length), *top;
    monomial *mon = (monomial *)remove_first(reduced_monomials);
    
    vector *majority = create_vector(reduced_monomials->length), *s, *temp;
    matrix *generator_matrix = create_generator_matrix(m, reduced_monomials);

    destroy_monomial(mon);
    
    i = 0;
    while (!is_empty_list(reduced_monomials)) {
        mon = (monomial *)remove_first(reduced_monomials);
        majority->values[i] = majority_logic(v,mon,m);
        i++;
        destroy_monomial(mon);
    }
    
	for (i = 0, j = 1; i < majority->length; i++,j++) {
        result->values[j] = majority->values[i];
	}

    s = lmultiply_vector(majority, generator_matrix);
    
    temp = s;
    s = add_vectors(s,v);
	destroy_vector(temp);
    	
	for(i = 0, count_1 = 0; i < s->length; i++) {
        if (s->values[i] == 1) {
            count_1++;
        } 
    }
	
    if (count_1 * 2 >= s->length) {
        result->values[0] = 1;
    } else {
		result->values[0] = 0;
	}

	top = create_vector(s->length);
	for (i = 0; i < top->length; i++) {
		top->values[i] = result->values[0];
	}
	

	temp = s;
	s = add_vectors(top,s);
	
	printf("received:\n");
	print_vector(v);
	printf("generated:\n");
	print_vector(s);
	
	
	
	printf("error indices: ");
	for (i = 0; i < s->length; i++) {
		if (s->values[i] != v->values[i]) {
			printf("%d\t",i);
		}
	}
	printf("\n");

	destroy_vector(top);
    destroy_vector(temp);
    destroy_vector(s);
    destroy_vector(majority);
    destroy_matrix(generator_matrix);
    destroy_list(reduced_monomials);
    return result;
}


#endif
