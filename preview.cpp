#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "preview.h"
#include "quadtree.h"

void viewpreview(data Daten,QuadTree *QTree,QGraphicsScene *preview, long scale)
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

    for(long i = 0; i < QTree->getNodeSize(); i++)
    {
        QPen Pen;
        node CurrNode = QTree->getNode(i);
        Pen.setColor(QColor(255, 255, 255, 255));
        preview->addLine(CurrNode.Bounds[0].x1*scale,CurrNode.Bounds[0].y1*-scale,CurrNode.Bounds[0].x2*scale,CurrNode.Bounds[0].y2*-scale,Pen);
        preview->addLine(CurrNode.Bounds[1].x1*scale,CurrNode.Bounds[1].y1*-scale,CurrNode.Bounds[1].x2*scale,CurrNode.Bounds[1].y2*-scale,Pen);
        preview->addLine(CurrNode.Bounds[2].x1*scale,CurrNode.Bounds[2].y1*-scale,CurrNode.Bounds[2].x2*scale,CurrNode.Bounds[2].y2*-scale,Pen);
        preview->addLine(CurrNode.Bounds[3].x1*scale,CurrNode.Bounds[3].y1*-scale,CurrNode.Bounds[3].x2*scale,CurrNode.Bounds[3].y2*-scale,Pen);

        if(CurrNode.leaf == true)
        {
            Pen.setColor(QColor(255, 0, 0, 255));
            preview->addLine(CurrNode.Center.x*scale,CurrNode.Center.y*-scale,CurrNode.Center.x*scale,CurrNode.Center.y*-scale+CurrNode.EdgeNbr.size()*5,Pen);
        }
    }
}
