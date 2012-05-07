#include "rmath.h"


const double noInters = -2.0;

int sgn(int x){
  return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

double radToDeg(double Rad)
{
    return (Rad / Pi) * 180;
}

double degToRad(double Deg)
{
    return (Deg / 180) *Pi;
}

double normalize(double alpha)
{
    if(alpha < 360 && alpha > 0)
    {
        return alpha;
    }
    if(alpha < 0)
    {
        return normalize(alpha + 360);
    }
    if(alpha > 360)
    {
        return normalize(alpha - 360);
    }

    return alpha;
}

int inBounds(Coord pos,double xb1,double yb1,double xb2,double yb2)
{
    if (((pos.x >= xb1) && (pos.x <= xb2)) || ((pos.x <= xb1) && (pos.x >= xb2)))
    {
        if(((pos.y >= yb1) && (pos.y <= yb2)) || ((pos.y <= yb1) && (pos.y >= yb2)))
        {
            return 1;
        }
    }

    return 0;
}

int inDirection(double alpha, Coord pos, double x, double y)
{
    if( ( ((270 < alpha) || (90 > alpha) )&& (x - pos.x < 0)) || (((270 > alpha) && (90 < alpha)) && (x - pos.x > 0)) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Coord IntersecRay(Coord Ray,double alpha,edge Rect)
{

    edge Edges[4];
    Edges[0].x1 = Rect.x1;
    Edges[0].y1 = Rect.y1;
    Edges[0].x2 = Rect.x2;
    Edges[0].y2 = Rect.y1 + 0.00001;

    Edges[0].x1 = Rect.x2;
    Edges[0].y1 = Rect.y1;
    Edges[0].x2 = Rect.x2 + 0.00001;
    Edges[0].y2 = Rect.y2;

    Edges[0].x1 = Rect.x2;
    Edges[0].y1 = Rect.y2;
    Edges[0].x2 = Rect.x1;
    Edges[0].y2 = Rect.y2 + 0.00001;

    Edges[0].x1 = Rect.x1;
    Edges[0].y1 = Rect.y2;
    Edges[0].x2 = Rect.x1 + 0.00001;
    Edges[0].y2 = Rect.y1;

    for(int i = 0; i < 4 ; i++)
    {
        Coord Intersec;

        Intersec = InterSection(Ray,alpha,Edges[i]);
        if(Intersec.x != noInters)
        {
            return Intersec;
        }
    }

    Coord Intersec;
    Intersec.x = noInters;
    Intersec.y = noInters;
    return Intersec;
}

int IntersecRect(edge Ray, edge Rect)
{
    QLineF Edges[4];
    Edges[0].setLine(Rect.x1,Rect.y1,Rect.x2, Rect.y1);
    Edges[1].setLine(Rect.x2,Rect.y1,Rect.x2, Rect.y2);
    Edges[2].setLine(Rect.x2,Rect.y2,Rect.x1, Rect.y2);
    Edges[3].setLine(Rect.x1,Rect.y2,Rect.x1, Rect.y1);

    QLineF currRay;
    currRay.setLine(Ray.x1,Ray.y1,Ray.x2,Ray.y2);
    for(int i = 0; i < 4 ; i++)
    {
        QPointF Intersec;
        int inter = 0;

        inter = Edges[i].intersect(currRay,&Intersec);
        if(inter == 1)
        {
            return 1;
        }
    }
    return 0;
}


Coord InterSection(Coord pos,double angle,edge currEdge)
{
    double m1,m2,v;
    Coord Intersec;

    m1 = qTan(angle * Pi/180);
    m2 = (currEdge.y1 - currEdge.y2)/(currEdge.x1 - currEdge.x2);

    v = (currEdge.y1-pos.y+pos.x*m2-currEdge.x1*m2)/(m1-m2);

    Intersec.x = pos.x + v;
    Intersec.y = pos.y + v * m1;


    if(inBounds(Intersec,pos.x-0.0001,pos.y-0.0001,pos.x+0.0001,pos.y+0.0001))
    {
        Intersec.x = noInters;
        Intersec.y = noInters;
        Intersec.i = 0;
        return Intersec;
    }
    else
    {
        if ( inBounds(Intersec,currEdge.x1,currEdge.y1,currEdge.x2,currEdge.y2) )
        {
            if (inDirection(angle,Intersec,pos.x,pos.y))
            {
                Intersec.i = 0;
                return Intersec;
            }
            else
            {
                Intersec.x = noInters;
                Intersec.y = noInters;
                Intersec.i = 0;
                return Intersec;
            }
        }
        else
        {
            Intersec.x = noInters;
            Intersec.y = noInters;
            Intersec.i = 0;
            return Intersec;
        }
    }

}
