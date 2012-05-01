#include "raytracer.h"
#include "quadtree.h"

#include <QDebug>

const double VeryBig = 2e10;
const double noInters = -2.0;
const double pi = 3.14159265;

raytracer::raytracer(data *Daten,unsigned long scale)
{
    _Daten = Daten;
    _scale = scale;
}

renderPixel raytracer::renderPix(int x,int y)
{
    double xp,yp,alpha;

    xp = (double)x/(_scale/2) - 1.0;
    yp = -((double)y/(_scale/2) - 1.0);

    return trace(xp,yp);
}

renderPixel raytracer::trace(double x,double y)
{
    Coord Pos;

    Pos.x = x;
    Pos.y = y;

    covering.clear();
    for(int i = 0; i < _Daten->getSize(); i++)
    {
        getCovering(Pos,i);
    }

    zCovering.clear();
    zSort();

    renderPixel value;
    value.r=0.0;
    value.g=0.0;
    value.b=0.0;
    for(int i = 0; i < zCovering.size(); i++)
    {
        edge currEdge = _Daten->getEdge(zCovering[i].ObjIndex);
        value.r += (value.r * i + (abs(zCovering[i].dalpha)/(2.0*pi))*currEdge.r*currEdge.e)/(i+1);
        value.g += (value.g * i + (abs(zCovering[i].dalpha)/(2.0*pi))*currEdge.g*currEdge.e)/(i+1);
        value.b += (value.b * i + (abs(zCovering[i].dalpha)/(2.0*pi))*currEdge.b*currEdge.e)/(i+1);
    }

    return value;
}

int raytracer::zSort()
{
    int noOverlap = 1;
    for(int i = 0; i < covering.size(); i++)
    {
        int overlap = 0;
        for(int j = 0; j < covering.size() ; j++)
        {
            if(j != i)
            {
                overlap = coverOverlap(covering[i],covering[j]);

                if(overlap != 0)
                {
                    noOverlap = 0;
                }
            }
        }

        if(noOverlap == 1)
        {
            zCovering.push_back(covering[i]);
        }
    }

}

int raytracer::coverOverlap(Cover C1,Cover C2) //If C1.alpha is inside C2 return 1. If C2.alpha is inside C1 return 2. Else return 0
{

    if(inside(C1.alpha1,C2.alpha1,C2.alpha2)||inside(C1.alpha2,C2.alpha1,C2.alpha2))
    {
        return 1;
    }
    if(inside(C2.alpha1,C1.alpha1,C1.alpha2)||inside(C2.alpha2,C1.alpha1,C1.alpha2))
    {
        return 2;
    }

    return 0;
}


int  raytracer::getCovering(Coord Pos,int i)
{
    edge currEdge = _Daten->getEdge(i);

        Cover currCover;
        currCover.alpha1 = atan2((Pos.y-currEdge.y1),(Pos.x-currEdge.x1));
        currCover.alpha2 = atan2((Pos.y-currEdge.y2),(Pos.x-currEdge.x2));



        currCover.dalpha = currCover.alpha1 - currCover.alpha2;
        if(currCover.dalpha > pi)
        {

                currCover.alpha1 = normalize(currCover.alpha1);
                currCover.alpha2 = normalize(currCover.alpha2);

            currCover.dalpha = currCover.alpha1 - currCover.alpha2;
        }
        if(currCover.dalpha < -pi)
        {

                currCover.alpha1 = normalize(currCover.alpha1);
                currCover.alpha2 = normalize(currCover.alpha2);

            currCover.dalpha = currCover.alpha1 - currCover.alpha2;
        }


        currCover.ObjIndex = i;

        currCover.z1 = sqrt((Pos.x - currEdge.x1)*(Pos.x - currEdge.x1)+(Pos.y - currEdge.y1)*(Pos.y - currEdge.y1));
        currCover.z2 = sqrt((Pos.x - currEdge.x2)*(Pos.x - currEdge.x2)+(Pos.y - currEdge.y2)*(Pos.y - currEdge.y1));

        covering.push_back(currCover);
    return 0;
}

int raytracer::location(double xG, double yG, double alphaG, Coord Pos)
{
    double m = tan(alphaG*Pi/180);
    double c;

    c = (Pos.y-yG)/m - Pos.x + xG;

    if(c >= 0){return 1;}
    else {return 0 ;}
}

double raytracer::abs(double var)
{
    if (var > 0)
    {
        return var;
    }
    else
    {
        return -var;
    }
}
