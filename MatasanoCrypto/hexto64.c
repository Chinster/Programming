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

/* Receives a number under 64 and returns a char would represents it.
 * If called on non-64 digit behavior is undefined
 */
char num_to_base64(char digit)
{
    if (digit < 26)
        return digit + 'A';
    else if (digit < 52)
        return digit + 'a' - 26;
    else if (digit < 62)
        return digit +'0' - 52;
    else if (digit == 62)
        return '+';
    else if (digit == 63)
        return '/';
    else
        return '-';
}

/* Takes a hex string and prints out its base64 equivalent string.
 * Returns -1 on failure.
 */
int hex_to_base64(char *input)
{
    int length = strlen(input);
    for (int i = 1; i <= length; i++) {
        input[length - i]
    }
}

/* Converts a character to a value from 0-15,
 * its numerical interpretation in hex.
 * Returns -1 on failure;
 */
int char_to_hex(char hex)
{
    if (hex >= '0' && hex <= '9')
        return hex - '0';
    if (hex >= 'a' && hex <= 'f')
        return hex - 'a' + 10;
    return -1;
}

int stdin_to_double()
{
    double number = 0;
    char *input = malloc(sizeof(char) * MAX_BUFF);

    while (get_line("", input, MAX_BUFF) == 0) {
        int len = strlen(input);
        int extra = (len % 3) * 2; // 12 bits is a multiple of 6

        if (hex_to_base64(input)) {
            continue;
        }
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

