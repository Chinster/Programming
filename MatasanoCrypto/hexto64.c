#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFF 256
/* Sanitized getline from paxdiablo on stackoverflow.com
 */
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
static int get_line (char *prompt, char *buff, size_t s) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prompt != NULL) {
        printf ("%s", prompt);
        fflush (stdout);
    }
    if (fgets (buff, s, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

/* Receives a number under 64 and returns an integern that would represents it.
 * If called on non-64 digit behavior is undefined
 */
char num_to_base64(char digit)
{
    if (digit < 26)
        return digit + 'A';
    else if (digit < 52)
        return digit + 'a' - 26;
    else if (digit < 62)
        return digit + '0' - 52;
    else if (digit == 62)
        return '+';
    else if (digit == 63)
        return '/';
    else
        return '-';
}

/* Converts a character to a value from 0-15,
 * its numerical interpretation in hex.
 * Returns -1 on failure;
 */
char char_to_hex(char hex)
{
    if (hex >= '0' && hex <= '9')
        return hex - '0';
    if (hex >= 'a' && hex <= 'f')
        return hex - 'a' + 10;
    return -1;
}

/* Takes three hex digits and prints out their representation as two base64
 * digits.
 */
void num3_to_base64(char num1, char num2, char num3)
{
    // Split the digits of num2 between num1 and num3
    char first = (num1 << 2) | ((num2 & 0xc) >> 2);
    char second = (num3) | (num2 & 0x3) << 4;
    printf("%c%c", num_to_base64(first), num_to_base64(second));
}

/* Receives lines from standard input and converts tries to convert the hex
 * characters to base64. Behavior is likely undefined when not given hex string
 */
int stdin_to_double()
{
    char *input = malloc(sizeof(char) * MAX_BUFF);

    while (get_line("", input, MAX_BUFF) == 0) {
        int len = strlen(input);
        int extra = (len % 3);

        // Every 3 hex holds 12 data bits and 2 base64
        if (extra == 1) {
            char hex = char_to_hex(*input++);
            printf("%c", num_to_base64(hex));
        }
        else if (extra == 2) {
            char hex1 = char_to_hex(*input++);
            char hex2 = char_to_hex(*input++);
            // We have 8 data bits so pad the leading 2.
            hex2 |= (hex1 & 0x3) << 4;
            hex1 = (hex1 >> 2) & 0x3;
            printf("%c%c", num_to_base64(hex1), num_to_base64(hex2));
        }
        while (*input != '\0') {
            char hex1 = char_to_hex(*input++);
            char hex2 = char_to_hex(*input++);
            char hex3 = char_to_hex(*input++);
            num3_to_base64(hex1, hex2, hex3);
        }
        printf("\n");
    }

    free(input);
    return 0;
}

int main(int argc, char *argv[])
{
    /*
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
        }
    }*/
    return stdin_to_double();
}

