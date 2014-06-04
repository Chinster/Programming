#include <stdio.h>

// sets n bits at position in x to rightmost n bits of y
unsigned setbits(unsigned x, int pos, int n, unsigned y);

main(){
    char x = ~0;
    printf("%u", setbits( x, 5, 2, 0));
    return 0;
}


unsigned setbits(unsigned x, int pos, int n, unsigned y){
    unsigned loc = ~(~(~0 << n) << (pos + 1 - n)); //Used with & to zero out desired positions
    unsigned ybits = y & ~(~0 << n) << (pos + 1 - n); // Desired bits of y positioned at correct location
    return x & loc | ybits;
}
