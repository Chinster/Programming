#include <stdio.h>

//Copies string t to the end of s
char *strcat(char s[], char t[]){
    char *len = &s[0];
    while(*len != '\0')
        len++;
    while(*t++ != '\0')
        *len++ = *t;
    *len = *t;
    return s;
}

int main(){
    printf(strcat("hmmm", "...Mice!"));
    return 0;
}
