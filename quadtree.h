#ifndef QUADTREE_H
#define QUADTREE_H

#include "data.h"
#include "rmath.h"

#include <QVector>
#include <math.h>

struct node
{
    long SubNIndex[4];
    QVector<unsigned long> EdgeNbr;
    edge Bounds[4];
    Coord Center;
    unsigned short quadrant;
    unsigned short depth;
    bool leaf;
};

class QuadTree
{
public:
    QuadTree(data *Daten);
    node getNode(long ElNumber);
    long getNodeSize();

private:
    int Grow(node TopNode, long index);
    int CountIntersecEdges();

    QVector<node> Nodes;
    QVector<edge> diag;
    node Root;
    data *_Daten;
};


#endif // QUADTREE_H
