#include <stdio.h>

//Inverts n bits from position pos

unsigned invert(unsigned x, int pos, int n);
main(){
    invert(~0, 5, 3);
    return 0;
}

unsigned invert(unsigned x, int pos, int n){
    unsigned loc = ((1 << (n + 1)) - 1) << (pos + 1 - n);
    return x ^ loc;
}
