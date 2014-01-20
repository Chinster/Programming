#include <stdlib.h>
#include <stdio.h>

int main()
{
    //Bit Shifting
    int a = 1; //00000001
    a << 1;    //00000010
    puts( i );
    a >> 1;    //00000001
    puts( i );
    //AND OR operation & | 
    int b = 3; //00000011
    int c = 2; //00000010
    puts( b & c ); //00000010
    puts( b | c ); //00000011

    //XOR operation
    //returns 0 if both bits are the same.
    puts( b ^ c ); //00000001

    //Bit Complement
    puts( ~c ); //11111101
    signed int maxIntSigned = ~0;
    unsigned int maxIntUnsigned = ~0;
    puts( maxIntSigned );
    puts( maxIntUnsigned );
}
