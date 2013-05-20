#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "reedmuller.h"
#include "utils.h"

int main(int argc, char **argv) {
    int i, r, m, length, err_count;
	int n,k,d;
    vector *original, *decoded, *encoded;
    
    if (argc != 4) {
        printf("Usage:\n\n");
        printf("\t%s <r> <m> <message>\n\n", argv[0]);
        printf("\tWhere\n\n");
        printf("\t\t<r> - the degree of the code.\n\n");
        printf("\t\t<m> - the length of the code.\n\n");
        printf("\t\t<message> - the message to be decoded (in bits).\n\n");
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

        printf("\na maximum of %d error(s) can be corrected per %d bits.\n", d >> 1, n);        
        
        original = to_int_vector(argv[3], length);
        decoded = decode(original,r,m);
        encoded = encode(decoded,r,m);
        
        printf("\ndecoded message: ");
        print_vector(decoded);
        printf("\noriginal encoded message: ");
        print_vector(encoded);
        printf("\nreceived encoded message: ");
        print_vector(original);
        
        printf("\nError indices:");
        for (i = 0, err_count = 0; i < original->length; i++) {
            if (original->values[i] % 2 != encoded->values[i] % 2) {
                err_count++;
                printf(" %d", i);
            }
        }
        if (err_count == 0) {
            printf(" None\n\n");
        } else {
            printf("\nNumber of errors: %d\n\n", err_count);
            
        }
        
        
    }

    return 0;
}