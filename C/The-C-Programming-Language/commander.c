#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc == 1){
        fprintf(stderr, "There are no minions to command!");
        exit(2);
    }
    else{
        char *command = strdup("./");
        strcat(command, argv[1]);
        system(command);
    }
    exit(0);
}
