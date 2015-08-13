#include <stdio.h>
#include <unistd.h>

#define MAX_READ 20

int main() {
    char buffer[MAX_READ];

    int num_read = read(STDIN_FILENO, buffer, MAX_READ);
    if (num_read == -1) {
        printf("err read");
        return 1;
    }
    buffer[num_read] = '\0';
    printf("The input data was: %s\n", buffer);
}
