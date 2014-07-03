#include <stdio.h>

#define LOWER 0 //lower limit of table
#define UPPER 300 //upper limit
#define STEP 20 //step size

float fahrToCels(int f);
/* Prints Fahrenheit-Celsius table
 */
main(){
    /*float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while(fahr <= upper){
        celsius = (5.0 / 9.0) * (fahr-32.0);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }*/
    int fahr;

    for(fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d\t%6.1f\n", fahr, fahrToCels(fahr));
}

float fahrToCels(int f){
    return (5.0/9.0) * (f-32);
}
