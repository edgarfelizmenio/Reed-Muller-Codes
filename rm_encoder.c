#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.c"
#include "reedmuller.c"
#include "utils.c"

int main(int argc, char **argv) {
    int r, m, length;
	int i, n, k, d;
    vector *original, *encoded;
    
    if (argc != 4) {
        printf("Usage:\n\n");
        printf("\t%s <r> <m> <message>\n\n", argv[0]);
        printf("\tWhere\n\n");
        printf("\t\t<r> - the degree of the code.\n\n");
        printf("\t\t<m> - the length of the code.\n\n");
        printf("\t\t<message> - the message to be encoded (in bits).\n\n");
    } else {
     
        r = atoi(argv[1]);
        m = atoi(argv[2]);
    
        if (m <= 0) {
            printf("m must be greater than 0!\n\n");
            exit(1);
        }
    
        if (r >= m) {
            printf("r must be less than m!\n\n");
            exit(1); 
        }
    
        length = strlen(argv[3]);
    
        if (!is_bin_string(argv[3],length)) {
            printf("message must only contain 0s and 1s!\n\n");
            exit(1);         
        }
		
		n = 1 << m;
		for (i = 0, k = 1; i <= r; i++) {
			k = k * (m - i)/(i + 1);
		}
		d = n >> r;
    
		printf("\n[%d, %d, %d]-code\n", n, d, r);
		
        original = to_int_vector(argv[3], length);
        encoded = encode(original,r,m);
    
        printf("\nencoded message: ");
        print_vector(encoded);
    
        printf("\nencoded message must not receive more than %d error(s) per %d bits.\n\n", k >> 1, n);
    }
    return 0;
}