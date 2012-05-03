#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <qmath.h>
#include <data.h>
#include <QRgb>
#include <QVector>
#include <rmath.h>
#include <QLineF>
#include <quadtree.h>
#include <math.h>


struct renderPixel
{
    double r,g,b;
    long i;
};

class raytracer
{
public:
    raytracer(data *Daten,unsigned long scale,QuadTree *QTree);
    renderPixel renderPix(int x,int y,QVector< QVector<renderPixel> > *RgbiImage);

private:
    renderPixel trace(double x,double y,double alpha,QVector< QVector<renderPixel> > *RgbiImage);
    int drawRay(Coord Pos,Coord InterS,renderPixel value,QVector< QVector<renderPixel> > *RgbiImage);
    int location(double xG, double yG, double alphaG, Coord Pos);
    int InterSecQTree(Coord Pos,double alpha);
    int SearchNode(Coord Pos,double alpha, node TopNode);

    QuadTree *_QTree;
    data *_Daten;
    unsigned long _scale;
    QVector<Coord> InterSections;
    QVector< QVector<renderPixel> > *_RgbiImage;

};

#endif // RAYTRACER_H
