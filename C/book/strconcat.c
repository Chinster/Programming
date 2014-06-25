//strconcat(s, t) - copies string t to end of s
#include <stdio.h>

void strconcat(char s[], char t[]);
int main(){
    char s1[] = "Hm...";
    char s2[] = "Rice";
    strconcat(s1, s2);
    printf("%s\n", s1);

    return 0;
}

void strconcat(char s[], char t[]){
    char *end;
    char *adder;
    for(end = s; *end != '\0'; end++);
    for(adder = t; *adder != '\0'; adder++, end++){
        *end = *adder;
    }
    *end = '\0';
}
