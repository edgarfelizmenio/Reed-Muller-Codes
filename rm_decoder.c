#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.c"
#include "reedmuller.c"
#include "utils.c"

int main(int argc, char **argv) {
    int i, r, m, length, err_count;
    vector *original, *decoded, *encoded;
    
    if (argc != 4) {
        printf("Usage:\n\n");
        printf("\t./rm_decoder <r> <m> <message>\n\n");
        printf("\tWhere\n\n");
        printf("\t\tr - the degree of the code.\n\n");
        printf("\t\tm - the length of the code.\n\n");
        printf("\t\tmessage - the message to be decoded (in bits).\n\n");
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

        printf("\na maximum of %d error(s) can be corrected per %d bits.\n", 1 << (m - r - 1), 1 << m);        
        
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