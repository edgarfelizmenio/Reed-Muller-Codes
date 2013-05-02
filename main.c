#include<stdio.h>
#include"reedmuller.c"
#include"matrix.c"
#include"vector.c"

int main(void){
	matrix *gm;
    vector *v;
    vector *encoded;
    
	printf("calling generator matrix...\n");
    print_vector(psi_x(4,1));
    print_vector(psi_x(4,2));
    print_vector(psi_x(4,3));
    print_vector(psi_x(4,4));
	gm = create_generator_matrix(3,5);
    print_matrix(gm);
    destroy_matrix(gm);
    gm = create_generator_matrix(1,3);
    print_matrix(gm);
    destroy_matrix(gm);
    gm = create_generator_matrix(2,3);
    print_matrix(gm);
    destroy_matrix(gm);
    gm = create_generator_matrix(1,1);
    print_matrix(gm);
    destroy_matrix(gm);
    gm = create_generator_matrix(1,2);
    print_matrix(gm);
    destroy_matrix(gm);
    gm = create_generator_matrix(1,3);
    print_matrix(gm);
    destroy_matrix(gm);
    gm = create_generator_matrix(1,4);
    print_matrix(gm);
    destroy_matrix(gm);
   
    
    gm = create_generator_matrix(2,4);
    print_matrix(gm);
    
    v = create_vector(11);
    v->values[0] = 0;
    v->values[1] = 1;
    v->values[2] = 1;
    v->values[3] = 0;
    v->values[4] = 1;
    v->values[5] = 0;
    v->values[6] = 0;
    v->values[7] = 1;
    v->values[8] = 0;
    v->values[9] = 1;
    v->values[10] = 0;
    
    print_vector(v);
	
    encoded = lmultiply_vector(v,gm);
    
    print_vector(encoded);
    
    destroy_vector(v);
    destroy_vector(encoded);                 
    destroy_matrix(gm);
    return 0;
}
