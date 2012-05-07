#include "raytracer.h"
#include "quadtree.h"

#include <QDebug>

const double VeryBig = 2e10;
const double noInters = -2.0;
const double pi = 3.14159265;

raytracer::raytracer(data *Daten,unsigned long scale,BresenhamGrid grid)
{
    _Daten = Daten;
    _scale = scale;
    _grid  = grid;
}

renderPixel raytracer::renderPix(int x,int y, QVector<QVector<renderPixel> > *RgbiImage)
{
    double xp,yp,alpha;
/*
    x = (rand() % (_scale -50)) +20;
    y = (rand() % (_scale -50)) +20;
*/
    xp = (double)x/(_scale/2) - 1.0;
    yp = -((double)y/(_scale/2) - 1.0);

    alpha = (double)(qrand() % 3600) / 10;

    return trace(xp,yp,alpha);
}

renderPixel raytracer::trace(double x,double y,double alpha)
{
    Coord Pos;

    Pos.x = x;
    Pos.y = y;
/*
    // Calculate EVERY intersection of the Ray with the Edges
    for(long i = 0; i < _Daten->getSize(); i++)
    {
        InterSections.append(InterSection(Pos,alpha,_Daten->getEdge(i)));
    }

    //InterSecQTree(Pos,alpha);

    // Calculate Z-Buffer/the nearest of all intersections
    double zBuffer = VeryBig;
    long  BufferI = 0;
    Coord InterSec;
    InterSec.x = noInters;
    InterSec.y = noInters;
    for(long i = 0; i < InterSections.size(); i++)
    {
        if(InterSections[i].x != noInters)
        {
            if(zBuffer > sqrt((Pos.x-InterSections[i].x)*(Pos.x-InterSections[i].x)+(Pos.y-InterSections[i].y)*(Pos.y-InterSections[i].y)))
            {
            InterSec = InterSections[i];
            BufferI = InterSections[i].i;
            zBuffer = sqrt((Pos.x-InterSections[i].x)*(Pos.x-InterSections[i].x)+(Pos.y-InterSections[i].y)*(Pos.y-InterSections[i].y));
            }
        }
    }
    InterSections.clear();
*/
    edge Ray;
    Ray.x1 = Pos.x;
    Ray.y1 = Pos.y;
    Ray.x2 = Pos.x + cos(degToRad(alpha)) * 100.0;
    Ray.y2 = Pos.y + sin(degToRad(alpha)) * 100.0;

    Coord InterSec = _grid.Raytrace(Ray,alpha);
    // Calculate Shader
        if(_Daten->getEdge(InterSec.i).e > 0.0)
        {
            renderPixel value;
            value.r = _Daten->getEdge(InterSec.i).r * _Daten->getEdge(InterSec.i).e;
            value.g = _Daten->getEdge(InterSec.i).g * _Daten->getEdge(InterSec.i).e;
            value.b = _Daten->getEdge(InterSec.i).b * _Daten->getEdge(InterSec.i).e;

            //Draw Ray into the RgbiImage with the Bresenham from x,y to InterSec.x,InterSec.y
            //drawRay(Pos,InterSec,value,RgbiImage);

            return value;
        }//Reflective Material (Diffuse/Specular)
        else
        {
        if((_Daten->getEdge(InterSec.i).r +_Daten->getEdge(InterSec.i).g +_Daten->getEdge(InterSec.i).b) > 0.0)
        {
            double normale = atan2(_Daten->getEdge(InterSec.i).y2 - _Daten->getEdge(InterSec.i).y1,_Daten->getEdge(InterSec.i).x2 - _Daten->getEdge(InterSec.i).x1);
            normale = radToDeg(normale);

            if(normale < 180 && normale < 360){normale -= 180;}

            if(location(_Daten->getEdge(InterSec.i).x1,_Daten->getEdge(InterSec.i).y1,normale+90,Pos)){normale -= 180;}

            double refl = alpha + 2*(normale-alpha);
            refl = normalize(refl);

            renderPixel value;
            //value = this->trace(InterSec.x,InterSec.y,refl);

            value.r = 0;
            value.g = 0;
            value.b = 0;

            value.r = value.r * _Daten->getEdge(InterSec.i).r;
            value.g = value.g * _Daten->getEdge(InterSec.i).g;
            value.b = value.b * _Daten->getEdge(InterSec.i).b;

            return value;
        }
        else //Blackbody Material
        {
            renderPixel value;
            value.r = 0;
            value.g = 0;
            value.b = 0;

            //Draw Ray into the RgbiImage with the Bresenham from x,y to InterSec.x,InterSec.y
            //drawRay(Pos,InterSec,value,RgbiImage);

            return value;
        }
        }

    renderPixel value; //This may not be reached
    value.r = 0;
    value.g = 0;
    value.b = 0;

    return value;
}

int raytracer::drawRay(Coord Pos,Coord InterS,renderPixel value,QVector< QVector<renderPixel> > *RgbiImage)
{
    int x = (int)((Pos.x + 1.0) * (_scale/2));
    int y = _scale - (int)((Pos.y + 1.0) * (_scale/2));

    (*RgbiImage)[y][x].i++;
    (*RgbiImage)[y][x].r = ((*RgbiImage)[y][x].r * (*RgbiImage)[y][x].i + value.r)/((*RgbiImage)[y][x].i + 1);
    (*RgbiImage)[y][x].g = ((*RgbiImage)[y][x].g * (*RgbiImage)[y][x].i + value.g)/((*RgbiImage)[y][x].i + 1);
    (*RgbiImage)[y][x].b = ((*RgbiImage)[y][x].b * (*RgbiImage)[y][x].i + value.b)/((*RgbiImage)[y][x].i + 1);
}



int raytracer::location(double xG, double yG, double alphaG, Coord Pos)
{
    double m = tan(alphaG*Pi/180);
    double c;

    c = (Pos.y-yG)/m - Pos.x + xG;

    if(c >= 0){return 1;}
    else {return 0 ;}
}
