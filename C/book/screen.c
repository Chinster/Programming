// Uses structs to emulate vertex graphics
#include <stdio.h>
#define XMAX = 640
#define YMAX = 400

struct point{int x; int y;};
struct rect{
    struct point pt1;
    struct point pt2;
};

struct point makepoint(int x, int y){
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

int inbounds(struct point p, struct rect r){
    return p.x >= r.pt1.x && p.x < r.pt2.x
        && p.y >= r.pt1.y && p.y < r.pt2.y;
}

/*canonicalizes coordinates of rectangle. 
  Ensures pt1 is less than pt2. */
struct rect canonrect(struct rect r){
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

int main(){
    struct rect screen;
    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    return 0;
}
