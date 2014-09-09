#ifndef _ex22_h
#define _ex22_h

// allow var for other .c files
extern int THE_SIZE;

// get+set internal static vars in ex22.c
int get_age();
void set_age(int age);

// update static var
double update_ratio(double ratio);

void print_size();

#endif
