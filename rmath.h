#ifndef RMATH_H
#define RMATH_H

#include <QLineF>
#include <QPointF>
#include <data.h>
#include <qmath.h>

struct Coord
{
    double x,y;
    long i;
};

const double Pi = 3.14159265;

double radToDeg(double Rad);
double degToRad(double Deg);
double normalize(double alpha);

int sgn(int x);
bool inBounds(Coord pos,double xb1,double yb1,double xb2,double yb2);
int inDirection(double alpha, Coord pos, double x, double y);
Coord IntersecRay(Coord Ray,double alpha, edge Rect);
int IntersecRect(edge Ray, edge Rect);
Coord InterSection(Coord pos,double angle,edge currEdge);


#endif // RMATH_H
