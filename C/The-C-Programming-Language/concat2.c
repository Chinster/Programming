// cat: concatenate files
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUFF 1000
int main(int argc, char *argv[]){
    char buf[MAX_BUFF];
    int fd, n_read;
    char *prog = argv[0]; //program name

    if(argc == 1) //no args, copy stdin
        while((n_read = read(0, buf, MAX_BUFF))  > 0) //stdin -> stdout
            write(1, buf, n_read);
    else
        while(--argc > 0)
            if((fd = open(*++argv, O_RDONLY, 0)) == -1){
                error("%s: can't open %s\n", prog, *argv);
            } else{
                while((n_read = read(fd, buf, MAX_BUFF)) > 0)
                    write(1, buf, n_read); //writes to stdout
                close(fd);
            }
    exit(0);
}
