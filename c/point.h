#ifndef POINT_H
#define POINT_H

#define SIZE  0.30
#define SCALEX (0.0001 * 512.0 * 1.38)
#define SCALEY (0.0001 * 512.0 * 2.1)

typedef struct {
   int x;
   int y;
} Point;

double POINTdist(Point, Point);
void   POINTshow(Point);
void   POINTplot(Point);
void   LINEplot(Point, Point);

#endif
