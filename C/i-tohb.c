// Receives input, converts to hex and binary
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    unsigned int input;
    char *binstring(unsigned int);
    printf("Enter an integer to convert to hexadecimal and binary: ");
    scanf("%u", &input);
    printf("%u = %#x = 0b", input, input);

    while(input){
        if(input & 1)
            printf("1");
        else
            printf("0");
        input >>= 1;
    }

    printf("\n");
    return 0;
}
