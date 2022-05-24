#ifndef PS5_ERRORS_H
#define PS5_ERRORS_H

#include <stdio.h>

#define S1 "ERROR: There are too many operators. The function has failed."
#define S2 "ERROR: There are too many numbers. The function has failed."
#define S3 "ERROR: Invalid input. The function has failed."
#define S4 "ERROR: The expression has mismatched parentheses."
#define S5 "ERROR: There was an unexpected null pointer."
#define S6 "ERROR: There was an invalid operator."

void errorCheck( int*, FILE* );

#endif //PS5_ERRORS_H
