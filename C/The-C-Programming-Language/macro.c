#include <stdio.h>

#define square(x) (x)*(x)
#define swap(t, x, y) {t = x; x = y; y = t;}

int main(){
    printf("9 squared is %d\n", square(9));
    int t = 0;
    int x = 1;
    int y = 3;
    swap(t, x, y);
    printf("%d\n", x);
    return 0;
}
