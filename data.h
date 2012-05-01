#ifndef DATA_H
#define DATA_H

#include <QtGui/QApplication>
#include <QVector>

struct edge
{
    double x1,x2,y1,y2;
    double r,g,b;
    double gl,e;
};

class data
{
private:
    QVector<edge> Edges;

public:
    data();
    edge getEdge(unsigned long ElNumbr);
    long getSize();
    int loadFile(QString FileName);

};

#endif // DATA_H
