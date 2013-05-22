#include <stdio.h>
#include "../src/vector.h"
#include "../src/reedmuller.h"

void test(int,int);
void increment(vector *);

int main(void) {
	int r, m = 3;

	for (r = 0; r <= m; r++) {
		test(r,m);
	}
	
	return 0;
}

void test(int r,int m) {
	int n = 1 << m;
	int i, k = 1, d,s, max;
	vector *message, *decoded, *encoded;
	char filename[100];
	FILE *outputstream;
	
	sprintf(filename, "test2_out_%d_%d.txt", m, r);
	outputstream = fopen(filename,"w");
	
	for (i = 0, s = 1; i < r; i++) {
		s = s * (m - i)/(i + 1);
		k += s;
	}
	max = 1 << n;
	d = n >> r;
	
	fprintf(outputstream, "r = %d, m = %d\n", r,m);
	fprintf(outputstream, "[%d, %d, %d]\n\n", n, k, d);
	
	message = create_vector(n);
	
	for (i = 0; i < max; i++) {
		fprintf(outputstream, "received: ");
		print_vector(message, outputstream);
				
		decoded = decode(message, r, m);
		
		fprintf(outputstream, "decoded: ");
		if (decoded == NULL) {
			fprintf(outputstream, "Error - 0s and 1s tied in majority logic. Indeterminate message.\n\n");
		} else {
			print_vector(decoded, outputstream);
			
			encoded = encode(decoded,r, m);
			fprintf(outputstream, "encoded: ");
			print_vector(encoded, outputstream);
			if (compare_vectors(encoded,message) == 0) {
				fprintf(outputstream, "NO ERRORS\n\n");
			} else {
				fprintf(outputstream, "%d ERROR(S)\n\n", distance(encoded, message));
			}
			
			destroy_vector(encoded);
			destroy_vector(decoded);
		}
		
		increment(message);
	}
	
	fclose(outputstream);
	destroy_vector(message);
}

void increment(vector *v) {
	int i = v->length;
	do {
		i--;
		if (v->values[i] == 1) {
			v->values[i] = 0;
		} else {
			v->values[i] = 1;
		}
	} while (v->values[i] == 0 && i > 0);
	return;
}