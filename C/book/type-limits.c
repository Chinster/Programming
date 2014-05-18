#include <stdio.h>
#include <limits.h>
#include <float.h>
main(){
    printf("TYPE:\t MAX\tMIN\n");
    printf("CHAR:\t%d\t%d\n", CHAR_MAX, CHAR_MIN);
    printf("INT:\t%d,\t%d\n", INT_MAX, INT_MIN);
    printf("LONG:\t%ld,\t%ld\n", LONG_MAX, LONG_MIN);
    printf("SIGNED CHAR:\t%d,\t%d\n", SCHAR_MAX, SCHAR_MIN);
    printf("SHORT:\t%d,\t%d\n", SHRT_MAX, SHRT_MIN);
    printf("UNSIGNED CHAR:\t%d\n", UCHAR_MAX);
    printf("UNSIGNED INT:\t%u\n", UINT_MAX);
    printf("UNSIGNED LONG:\t%lu\n", ULONG_MAX);
    printf("UNSIGNED SHORT:\t%u\n", USHRT_MAX);
}
