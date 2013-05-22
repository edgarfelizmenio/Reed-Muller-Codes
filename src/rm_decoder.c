#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "reedmuller.h"
#include "utils.h"

int main(int argc, char **argv) {
    int i, r, m, length, err_count;
	int n,k,d,s;
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
        
        if (r > m) {
            printf("r must not exceed m!\n\n");
            exit(1); 
        }
        
        length = strlen(argv[3]);
        
        if (!is_bin_string(argv[3],length)) {
            printf("Message must only contain 0s and 1s!\n\n");
            exit(1);         
        }
		
		n = 1 << m;
		for (i = 0, s = 1, k = 1; i < r; i++) {
			s = s * (m - i)/(i + 1);
			k += s;
		}
		d = n >> r;
		
		printf("\n[%d, %d, %d]-code\n", n, k, d);

        printf("\nA maximum of %d error(s) can be corrected per %d bits.\n", (d >> 1) - 1, n);        
        
        original = to_int_vector(argv[3], length);
        decoded = decode(original,r,m);
		if (decoded == NULL) {
			printf("\nToo many errors. Indeterminate message.\n\n");
		} else {
			encoded = encode(decoded,r,m);
        
			printf("\nDecoded message: ");
			print_vector(decoded, stdout);
			printf("\nOriginal encoded message: ");
			print_vector(encoded, stdout);
			printf("\nReceived encoded message: ");
			print_vector(original, stdout);
        
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
        
    }

    return 0;
}