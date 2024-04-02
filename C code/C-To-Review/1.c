/*This program uses a function to print a pyramid 'like' structure, increment the number (+1) in every position like so: 
        1
       2 3
      4 5 6
     6 7 8 9 
*/

// Bugs can be of the following types:
// 1. Logical bug
// 2. Performance bug
// 3. Variable type bug
// 4. Memory managment bug
// 5. Documentation bug

// The review should take no longer than 5 minutes.
// Review starts on Line 23

#include <stdio.h> 

// Functions
void printPyramid(int rows);

// REVIEW STARTS HERE

int main() {
   printPyramid(5);

   return 0;
}

/**********************************************************************
Function: print pyramid 'like' pattern, increment numbers throughtout
the positions of the pyramid
Parameters: rows - number of rows.
Comments:
Out: void
***********************************************************************/
void printPyramid(int rows){
   int i, j = 1; // counters
   int spaces = 1; // spaces and rows for user input 
   int k, numb = 1;  // k and t for spaces

   spaces = rows + 4 - 1;  // initial number of spaces

   for (i = 1; i < rows; i++) { 
      for (k = spaces; k >= 1; k--) {  // print spaces before numbers
         printf(" ");
      }

      for (j = 1; j <= i; j++) {  // loop to print numbers based on the current row.
         printf("%d ", numb++);
         numb++;
      }

      printf("\n");  // move to the next line for the next row.
      spaces--;  // decrement the number of spaces for the next row.
   }
}