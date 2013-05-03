#include<stdio.h>
#include"reedmuller.c"
#include"utils.c"
#include"vector.c"

int main(void){
	vector *v = to_int_vector("01101001010",11);
	vector *e = encode(v,2,4);
	print_vector(e);
	destroy_vector(e);
	destroy_vector(v);
	
    return 0;
}
