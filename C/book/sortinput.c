#include <stdio.h>
#include <string.h>

#define MAXLINEs 5000   /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

// sorts input lines
main(){
    int nlines; //number of input lines to read

    if((nlines=readlines(lineptr, MAXLINES)) >= 0){
        qsort(lineptr, 0, nlines-1);
    }
