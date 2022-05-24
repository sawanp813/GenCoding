#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rpn.h"
#include "converter.h"


int main(int argc, char* argv[]) {

    // Checking for errors in configurations
    if (argc < 3) {
        printf("ERROR: Wrong number of arguments\n");
        return EXIT_FAILURE;
    }

    // Parameters

    char* expression;
    int statusVal = 0; // Default status
    int* status = &statusVal;
    double result;
    int length = 150; // default buffer length
    char DataLine[length];


    // Opening infile and checking to see if it opened correctly

    FILE* data = fopen(argv[1], "r");

    if (!data) {
        perror("I/O Error: \n");
        return -1;
    }

    if (!feof(data)) {
        printf("EOF not set\n\n");
    }

    // Opening outfile and checking to see if it opened correctly

    FILE* Result = fopen(argv[2], "w");

    if (!Result) {
        perror("I/O Error\n ");
        return -1;
    } else;

    fprintf(Result, "Printing before loop\n");

    while (fgets(DataLine, sizeof(DataLine), data)) {

        // Printing infix expression & writing to file
        fprintf(Result, "Printing during loop\n");
        printf("Infix: \t\t%s", DataLine);
//        DataLine[strcspn(DataLine, "\n")] = "0";
        fprintf(Result, "Infix: %t%t%s\n", DataLine);

        // Conversion from infix to postfix & writing postfix to file
        expression = convert(DataLine, status, length, Result);

        // If there is an error, the convert function returns an empty string
        // Error output is printed directly to outfile
        if (strlen(expression) == 0 ) {

            printf("\n");
            continue;
        }

        printf("Postfix: \t%s\n", expression);
        fprintf(Result, "Postfix: \t%s\n", expression);

        // Evaluating postfix expression & writing result to file

        result = evaluate(expression, status);
        printf("Result: \t%f\n\n", result);
        fprintf(Result, "Result: \t%f\n\n", result);

    }

    fprintf(Result, "Printing after loop\n");

    // Checking to see if input files closed correctly

    int fstatus = fclose(data);

    if (fstatus != 0) {
        printf("%s was not closed correctly.\n", argv[1]);
        return -1;
    }

    fstatus = fclose(Result);
    if (fstatus != 0) {
        printf("%s was not closed correctly\n", argv[2]);
        return -1;
    }

    return 0;
}