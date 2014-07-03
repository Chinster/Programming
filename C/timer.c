#include <stdio.h>
#include <limits.h>
#include <time.h>

int main(){
    clock_t begin, end;
    double time_spent;
    begin = clock();
    //
    //
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   
    printf("Time spent: %f\n", time_spent);
    return 0;
}
