#include "errors.h"
#include <stdio.h>

void errorCheck(int* status, FILE* file) {

    if (*status == -1) {

        // Null pointer
        printf("%s\n", S5);
        fprintf(file, "%s\n\n", S5);


    } else if (*status == 0) {

        // Successful return
//        printf("Success: %s\n", S4);

    } else if (*status == -2) {

        // Too many numbers
        printf("%s\n", S5);
        fprintf(file, "%s\n\n", S2);


    } else if (*status == -3) {

        // too many operators
        printf("%s\n", S1);
        fprintf(file, "%s\n\n", S1);


    } else if (*status == -4) {

        // Invalid input of some kind
        printf("%s\n", S3);
        fprintf(file, "%s\n\n", S3);


    } else if (*status == -5) {

        // Mismatched Parentheses
        printf("%s\n", S4);
        fprintf(file, "%s\n\n", S4);


    } else if (*status == -6) {

        // Invalid operator
        printf("\n%s\n", S6);
        fprintf(file, "%s\n\n", S6);


    } else {

        printf("Error: Something unexpected happened.\n");

    }

}