#ifndef BRESENHAMGRID_H
#define BRESENHAMGRID_H

#include <rmath.h>
#include <data.h>


#include <QVector>

const int gridSize = 64;

class BresenhamGrid
{
public:
    BresenhamGrid();
    void setGrid(data *Daten);
    long long getGrid(int x,int y);
    Coord Raytrace(edge Ray, double alpha);

private:
    int sgn(int x);
    QVector<long long> grid;
    QVector<int> edgeNumber[64][64];
    data *_Daten;
};

#endif // BRESENHAMGRID_H
