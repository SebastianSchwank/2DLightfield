#include "bresenhamgrid.h"

#include <QDebug>

BresenhamGrid::BresenhamGrid()
{
    long long line = 0;
    for(int i = 0; i < 64; i++)
    {
        grid.push_back(line);
    }
}

Coord BresenhamGrid::Raytrace(edge Ray,double alpha)
{
    Coord Intersection;

    int xstart,ystart,xend,yend;
    xstart = (Ray.x1 + 1.0)/2 * gridSize;
    ystart = (Ray.y1 + 1.0)/2 * gridSize;
    xend = (Ray.x2 + 1.0)/2 * gridSize;
    yend = (Ray.y2 + 1.0)/2 * gridSize;

    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

    /* Entfernung in beiden Dimensionen berechnen */
       dx = xend - xstart;
       dy = yend - ystart;

    /* Vorzeichen des Inkrements bestimmen */
       incx = sgn(dx);
       incy = sgn(dy);
       if(dx<0) dx = -dx;
       if(dy<0) dy = -dy;

    /* feststellen, welche Entfernung größer ist */
       if (dx>dy)
       {
          /* x ist schnelle Richtung */
          pdx=incx; pdy=0;    /* pd. ist Parallelschritt */
          ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
          es =dy;   el =dx;   /* Fehlerschritte schnell, langsam */
       } else
       {
          /* y ist schnelle Richtung */
          pdx=0;    pdy=incy; /* pd. ist Parallelschritt */
          ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
          es =dx;   el =dy;   /* Fehlerschritte schnell, langsam */
       }

    /* Initialisierungen vor Schleifenbeginn */
       x = xstart;
       y = ystart;
       err = el/2;

       if(getGrid(x,y))
       {
           for(int i = 0;i < edgeNumber[y][x].size(); i++)
           {
               Coord currPos;
               currPos.x = Ray.x1;
               currPos.y = Ray.y2;

               edge currEdge;
               currEdge = _Daten->getEdge(edgeNumber[y][x][i]);

               Intersection = InterSection(currPos,alpha,currEdge);
               if(inBounds(Intersection,x/(gridSize/2.0)-1.0,y/(gridSize/2.0)-1.0,(x+1)/(gridSize/2.0)-1.0,(y+1)/(gridSize/2.0)-1.0))
               {
                     return Intersection;
               }
           }
       }

    /* Pixel berechnen */
       for(t=0; t<el; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
       {
          /* Aktualisierung Fehlerterm */
          err -= es;
          if(err<0)
          {
              /* Fehlerterm wieder positiv (>=0) machen */
              err += el;
              /* Schritt in langsame Richtung, Diagonalschritt */
              x += ddx;
              y += ddy;
          } else
          {
              /* Schritt in schnelle Richtung, Parallelschritt */
              x += pdx;
              y += pdy;
          }

          if(getGrid(x,y))
          {
              for(int i = 0;i < edgeNumber[y][x].size(); i++)
              {
                  Coord currPos;
                  currPos.x = Ray.x1;
                  currPos.y = Ray.y2;

                  edge currEdge;
                  currEdge = _Daten->getEdge(edgeNumber[y][x][i]);

                  Intersection = InterSection(currPos,alpha,currEdge);
                  Intersection.i = edgeNumber[y][x][i];
                  //if(inBounds(Intersection,x/(gridSize/2.0)-1.0,y/(gridSize/2.0)-1.0,(x+1)/(gridSize/2.0)-1.0,(y+1)/(gridSize/2.0)-1.0))
                  {
                        return Intersection;
                  }
              }
          }
       } /* gbham() */

       Intersection.i = 0;
       return Intersection;
}

void BresenhamGrid::setGrid(data *Daten)
{
    for(int x = 0; x < gridSize; x++)
    {
        for(int y = 0; y < gridSize; y++)
        {
            for(int i = 0; i < Daten->getSize(); i++)
            {
                edge currEdge = Daten->getEdge(i);
                Coord Edge1,Edge2;
                Edge1.x = currEdge.x1;
                Edge1.y = currEdge.y1;
                Edge2.x = currEdge.x2;
                Edge2.y = currEdge.y2;
                edge rect;
                rect.x1 = x/(gridSize/2.0)-1.0;
                rect.y1 = y/(gridSize/2.0)-1.0;
                rect.x2 = (x+1)/(gridSize/2.0)-1.0;
                rect.y2 = (y+1)/(gridSize/2.0)-1.0;
                if(IntersecRect(currEdge,rect)||inBounds(Edge1,rect.x1,rect.y1,rect.x2,rect.y2)||inBounds(Edge2,rect.x1,rect.y1,rect.x2,rect.y2))
                {
                    long long mask = 1;
                    mask = mask << x;
                    grid[y] = grid[y] | mask;

                    edgeNumber[y][x].push_back(i);
                }
            }
        }
    }
}

long long BresenhamGrid::getGrid(int x, int y)
{
    long long mask = 1;
    mask = mask << x;
    return (mask & grid[y]);
}

int BresenhamGrid::sgn(int x){
  return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}
