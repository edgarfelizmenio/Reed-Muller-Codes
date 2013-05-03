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
	decode(NULL,2,4);
	decode(NULL,4,5);
	v = to_int_vector("0111010",7);
	e = encode(v,2,3);
	print_vector(e);
	destroy_vector(e);
	destroy_vector(v);
	printf("%d",1<<2);
    return 0;
}
