#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <qmath.h>
#include <data.h>
#include <QRgb>
#include <QVector>
#include <rmath.h>
#include <QLineF>
//#include <quadtree.h>


struct renderPixel
{
    double r,g,b;
};

struct Cover
{
    double alpha1,alpha2,dalpha;
    double z1,z2;
    int ObjIndex;
};

class raytracer
{
public:
    raytracer(data *Daten,unsigned long scale);
    renderPixel renderPix(int x,int y);

private:
    renderPixel trace(double x,double y);
    int location(double xG, double yG, double alphaG, Coord Pos);
    int getCovering(Coord Pos, int i);
    int zSort();
    int coverOverlap(Cover C1,Cover C2);
    double abs(double var);

    data *_Daten;
    unsigned long _scale;
    QVector<Cover> covering;
    QVector<Cover> zCovering;

};

#endif // RAYTRACER_H
