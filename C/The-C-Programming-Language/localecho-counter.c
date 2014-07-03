#include <stdio.h>

#define IN 1 //inside a word
#define OUT 0 //outside a word

/* Receives characters and prints them out.*/
main(){
    int c, nc, nl, nw, state;
    nc = nl = nw = 0; //num char, line, word.
    state = OUT;
    while((c = getchar()) != EOF){
        putchar(c);
        nc++;
        if(c == '\n')
            nl++;
        if(c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if( state == OUT){
            state = IN;
            ++nw;
        }
    }
    printf("\n%d characters were pressed.", nc);
    printf("\n%d lines were typed.\n", nl );
    printf("%d words were typed.\n", nw );
}
