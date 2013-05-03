/*
 *  utils.c
 *  
 *
 *  Created by Edgar Felizmenio on 5/3/13.
 *  Copyright 2013 University of the Philippines. All rights reserved.
 *
 */
#ifndef UTILS_C
#define UTILS_C

#include<stdlib.h>
#include"vector.c"

vector *to_int_vector(char *s, int length);
vector *to_bin_vector(char *s, int length);

vector *to_int_vector(char *s, int length) {
	int i;
	vector *v = create_vector(length);

	for (i = 0; i < length || s[i] != '\0'; i++) {
		v->values[i] = (int)s[i] - 32;
	}

	return v;
}


#endif