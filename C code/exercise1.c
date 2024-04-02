#include <stdio.h>

// Functions
void printPyramid(int rows);

int main() {
    printPyramid(5);

    return 0;
}

/**
Function: print pyramid 'like' pattern, increment numbers throughtout
the positions of the pyramid
Parameters: rows - number of rows.
Comments:
Out: void
***/
void printPyramid(int rows) {
    int i, j = 1;    // counters
    int spaces = 1;  // spaces and rows for user input
    int k, numb = 1; // k and t for spaces

    spaces = rows + 4 - 1; // initial number of spaces

    for (i = 1; i < rows; i++) {        // generate rows // BUG -> for (i = 1; i <= rows; i++)
        for (k = spaces; k >= 1; k--) { // print spaces before numbers
            printf(" ");
        }

        for (j = 1; j <= i; j++) { // loop to print numbers based on the current row.
            printf("%d ", numb++); // -> BUG
            numb++;
        }

        printf("\n"); // move to the next line for the next row.
        spaces--;     // decrement the number of spaces for the next row.
    }
}