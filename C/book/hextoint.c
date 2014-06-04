#include <stdio.h>

//converts hex string to decimal int
int htoi(char s[]);

main(){
    printf("%d", htoi("0X3Ad"));
    return 0;
}

int htoi(char s[]){
    int i, n;
    i = n = 0;
    if(s[0] != '\0')
        if(s[0] == '0' && tolower(s[1]) == 'x')
            i = 2;
    for(; s[i] != '\0'; i++){
        if(s[i] >= '0' && s[i] <= '9')
            n = n * 16 + (s[i] - '0');
        else if(s[i] >= 'A' && s[i] <= 'F')
            n = n * 16 + (s[i] - '7');    //'A'-'7'=10
        else if(s[i] >= 'a' && s[i] <= 'f')
            n = n * 16 + (s[i] - 'W');    //'a'-'W'=10
    }

    return n;
}
