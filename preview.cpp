#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "preview.h"
#include "quadtree.h"

void viewpreview(data Daten,QGraphicsScene *preview,long scale)
{
    preview->setBackgroundBrush(QColor(0, 0, 0, 255));

    for(long i = 0;i < Daten.getSize();i++)
    {
        QPen Pen;
        if(Daten.getEdge(i).e == 0)
        {
            Pen.setColor(QColor(Daten.getEdge(i).r*255,Daten.getEdge(i).g*255, Daten.getEdge(i).b*255, 255));
        }
        else
        {
            Pen.setColor(QColor(255, 255, 255, 255));
        }
        preview->addLine(Daten.getEdge(i).x1*scale,Daten.getEdge(i).y1*-scale,Daten.getEdge(i).x2*scale,Daten.getEdge(i).y2*-scale,Pen);
    }
}
