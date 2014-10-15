// Structs without Pointers To Them
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

// Returns an entire struct!
struct Person Person_create(char *name, int age, int height, int weight) {
    struct Person who = {name, age, height, weight};
    return who;
}

void Person_print(struct Person who){
    printf("name: %s\n", who.name);
    printf("\tage: %d\n", who.age);
    printf("\theight: %d\n", who.height);
    printf("\tweight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    struct Person joe = Person_create( "Joseph Puzzo", 20, 66, 130);
    struct Person sam = Person_create( "Samuel Harada", 19, 62, 140);
    Person_print(joe);
    Person_print(sam);

    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    sam.age += 20;
    sam.weight +=  20;
    Person_print(sam);

    return 0;
}
