#include <stdio.h>

//copies all characters in t into s
void strcopy(char *s, char *t){
    while(*s++ = *t++){ //++ has more precedence but its evaluated before adding
        //s++;
        //t++;
    }
}

int main(){
    char string1[] = "Merpie";
    char string2[] = "asdfjk";
    strcopy(string2, string1);
    printf(string2);
    printf("\n");
    return 0;
}
