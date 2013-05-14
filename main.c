#include<stdio.h>
#include<string.h>
#include"reedmuller.c"
#include"utils.c"
#include"vector.c"

void loop(char *,int,int);

int main(void) {

    vector *e, *d;
    loop("0111010",2,3);
    loop("01101001010",2,4);
    loop("0110",1,3);
    loop("00000000000",2,4);
    loop("11111111111",2,4);
    loop("0",0,3);
    loop("1",0,3);
    loop("00110011",3,3);
	loop("00111111",3,3);
    loop("00110010",3,3);
    loop("1111111111111111",2,5);
	loop("0010011111111111",2,5);

    
    e = to_int_vector("1010111111111010",16);
    d = decode(e,2,4);
    printf("encoded:\n");
    print_vector(e);
    printf("decoded:\n");
    print_vector(d);
    destroy_vector(e);
    printf("\n\n");
	
    e = to_int_vector("1010111111111010",16);
    d = decode(e,2,4);
    printf("encoded:\n");
    print_vector(e);
    printf("decoded:\n");
    print_vector(d);
    destroy_vector(e);
	printf("\n\n");
	
    e = to_int_vector("01111110111010001110100010000001",32);
    d = decode(e,2,5);
    printf("encoded:\n");
    print_vector(e);
    printf("decoded:\n");
    print_vector(d);
    destroy_vector(e);
    printf("\n\n");
	
    e = to_int_vector("01101110101010001110101010000001",32);
    d = decode(e,2,5);
    printf("encoded:\n");
    print_vector(e);
    printf("decoded:\n");
    print_vector(d);
    destroy_vector(e);
    printf("\n\n");

	e = to_int_vector("10111100",8);
    d = decode(e,1,3);
    printf("encoded:\n");
    print_vector(e);
    printf("decoded:\n");
    print_vector(d);
    destroy_vector(e);
    return 0;
}


void loop(char *s,int r,int m) {
    vector *v = to_int_vector(s,strlen(s));
	vector *e = encode(v,r,m);
    vector *d = decode(e,r,m);
	printf("original:\n");
    print_vector(v);
    printf("encoded:\n");
    print_vector(e);
    printf("decoded:\n");
    print_vector(d);
	
	if (compare_vectors(v,d) == 0) {
		printf("SAME\n");
	} else {
		printf("DIFFERENT\n");
	}
	
    destroy_vector(e);
	destroy_vector(v);
    destroy_vector(d);
    printf("\n\n");
}