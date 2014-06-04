#include <stdio.h>

// deletes letters from string1 that occur in string2
void squeeze(char s[], char del[]);

main(){
    char string[] = "Don't you dare delete me!";
    squeeze(string, "do");
    printf(string);
    return 0;
}

void squeeze(char s[], char del[]){
    int i, j, backref;
    backref = 0;
    for(i = 0; s[i] != '\0'; i++){
        s[backref++] = s[i];
        for(j = 0; del[j] != '\0'; j++)
            if(s[i] == del[j])
                s[--backref] = s[i + 1];
    }
    s[backref] = s[i]; //null char
}
