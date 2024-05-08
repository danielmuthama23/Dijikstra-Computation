#include <stdio.h>
#include <math.h>
#include "point.h"

void POINTshow(Point p) {
   printf("(%5d, %5d) ", p.x, p.y);
}

double POINTdist(Point p, Point q) {
   double dx = p.x - q.x;
   double dy = p.y - q.y;
   return sqrt(dx*dx + dy*dy);
}

void POINTplot(Point p) {
    printf("F %f %f S %f\n", p.x*SCALEX, p.y*SCALEY, SIZE);
}
void LINEplot(Point p, Point q) {
    printf("F %f %f  ", p.x*SCALEX, p.y*SCALEY);
    printf("G %f %f\n", q.x*SCALEX, q.y*SCALEY);
}

