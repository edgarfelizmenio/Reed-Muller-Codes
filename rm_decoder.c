#include <stdio.h>
#include "reedmuller.c"

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage:\n\n");
        printf("\t./rm_decoder <r> <m> <message>\n\n");
        printf("\tWhere\n\n");
        printf("\t\tr - the degree of the code.\n\n");
        printf("\t\tm - the length of the code.\n\n");
        printf("\t\tmessage - the message to be decoded (in bits).\n\n");
    }
    
    return 0;
}