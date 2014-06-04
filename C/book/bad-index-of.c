#include <stdio.h>

//Returns the first index in string1 that has a letter in string2

int any(char s[], char search[]);

main(){
    printf("%d", any("where am I?", "here"));
    return 0;
}

int any(char s[], char search[]){
    int i, j;
    for(i = 0; s[i] != '\0'; i++)
        for(j = 0; search[j] != '\0'; j++)
            if(s[i] == search[j])
                return i;
    return -1;
}
