// Structs and Pointers To Them
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person * Person_create(char *name, int age, int height, int weight){
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}
