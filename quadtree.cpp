#include "quadtree.h"

node QuadTree::getNode(long ElNumber)
{
    return Nodes[ElNumber];
}

long QuadTree::getNodeSize()
{
    return Nodes.size();
}

QuadTree::QuadTree(data *Daten)
{
    _Daten = Daten;

    Root.depth = 0;
    Root.leaf = false;

    Root.Bounds[0].x1 = -1.0;
    Root.Bounds[0].y1 = -1.0;
    Root.Bounds[0].x2 = 1.0;
    Root.Bounds[0].y2 = -1.0;

    Root.Bounds[1].x1 = 1.0;
    Root.Bounds[1].y1 = -1.0;
    Root.Bounds[1].x2 = 1.0;
    Root.Bounds[1].y2 = 1.0;

    Root.Bounds[2].x1 = 1.0;
    Root.Bounds[2].y1 = 1.0;
    Root.Bounds[2].x2 = -1.0;
    Root.Bounds[2].y2 = 1.0;

    Root.Bounds[3].x1 = -1.0;
    Root.Bounds[3].y1 = 1.0;
    Root.Bounds[3].x2 = -1.0;
    Root.Bounds[3].y2 = -1.0;

    Root.Center.x = 0.0;
    Root.Center.y = 0.0;

    Nodes.push_back(Root);
    Nodes[0].SubNIndex[0] = 1;
    Nodes[0].SubNIndex[1] = 2;
    Nodes[0].SubNIndex[2] = 3;
    Nodes[0].SubNIndex[3] = 4;
    this->Grow(Nodes[0],1);
    this->CountIntersecEdges();
}

int QuadTree::Grow(node TopNode,const long index)
{
    node Node[4];
    Node[0].depth = TopNode.depth +1;
    Node[1].depth = TopNode.depth +1;
    Node[2].depth = TopNode.depth +1;
    Node[3].depth = TopNode.depth +1;

    Node[0].leaf = true;
    Node[1].leaf = true;
    Node[2].leaf = true;
    Node[3].leaf = true;

    if(Node[0].depth < 10)
    {
        double xC;
        double yC;
        for(int i = 0; i < 4; i++)
        {
            double delta = pow(0.5,Node[0].depth);

            if (i == 0){
                xC = ((double)TopNode.Center.x) - delta;
                yC = ((double)TopNode.Center.y) - delta;
            }
            if (i == 1){
                xC = ((double)TopNode.Center.x) + delta;
                yC = ((double)TopNode.Center.y) - delta;
            }
            if (i == 2){
                xC = ((double)TopNode.Center.x) + delta;
                yC = ((double)TopNode.Center.y) + delta;
            }
            if (i == 3){
                xC = ((double)TopNode.Center.x) - delta;
                yC = ((double)TopNode.Center.y) + delta;
            }

           Node[i].Center.x = xC;
           Node[i].Center.y = yC;

           Node[i].Bounds[0].x1 = xC - delta;
           Node[i].Bounds[0].y1 = yC - delta;
           Node[i].Bounds[0].x2 = xC + delta;
           Node[i].Bounds[0].y2 = yC - delta;

           Node[i].Bounds[1].x1 = xC + delta;
           Node[i].Bounds[1].y1 = yC - delta;
           Node[i].Bounds[1].x2 = xC + delta;
           Node[i].Bounds[1].y2 = yC + delta;

           Node[i].Bounds[2].x1 = xC + delta;
           Node[i].Bounds[2].y1 = yC + delta;
           Node[i].Bounds[2].x2 = xC - delta;
           Node[i].Bounds[2].y2 = yC + delta;

           Node[i].Bounds[3].x1 = xC - delta;
           Node[i].Bounds[3].y1 = yC + delta;
           Node[i].Bounds[3].x2 = xC - delta;
           Node[i].Bounds[3].y2 = yC - delta;

           Nodes.push_back(Node[i]);
        }

        for(int j = 0; j < 4; j++)
        {
            int InEdge = 0;
            for(long i = 0; i < _Daten->getSize(); i++)
            {

                Coord pos1,pos2;
                pos1.x = _Daten->getEdge(i).x1;
                pos1.y = _Daten->getEdge(i).y1;
                pos2.x = _Daten->getEdge(i).x2;
                pos2.y = _Daten->getEdge(i).y2;

                if(inBounds(pos1,Nodes[index +j].Bounds[0].x1,Nodes[index +j].Bounds[0].y1,Nodes[index +j].Bounds[2].x1,Nodes[index +j].Bounds[2].y1)&&inBounds(pos2,Nodes[index +j].Bounds[0].x1,Nodes[index +j].Bounds[0].y1,Nodes[index +j].Bounds[2].x1,Nodes[index +j].Bounds[2].y1))
                {
                    Nodes[index +j].EdgeNbr.push_back(i);
                    InEdge++; //Count Edges which are Inside the Bound
                }

            }

            if(InEdge > 1)
            {
                Nodes[index +j].leaf = false;
                int newIndex;
                newIndex = this->Grow(Nodes[index +j],Nodes.size());
                Nodes[index +j].SubNIndex[0] = newIndex;
                Nodes[index +j].SubNIndex[1] = newIndex+1;
                Nodes[index +j].SubNIndex[2] = newIndex+2;
                Nodes[index +j].SubNIndex[3] = newIndex+3;
            }
      }

    }

    return index;
}


int QuadTree::CountIntersecEdges() //Count Edges which intersect Bounds
{
    for(int i= 0; i < Nodes.size(); i++)
    {
        for(long j = 0; j < _Daten->getSize(); j++)
        {
            edge Box;
            Box.x1 = Nodes[i].Bounds[0].x1;
            Box.y1 = Nodes[i].Bounds[0].y1;
            Box.x2 = Nodes[i].Bounds[2].x1;
            Box.y2 = Nodes[i].Bounds[2].y1;

            if(IntersecRect(_Daten->getEdge(j),Box) == 1)
            {
                Nodes[i].EdgeNbr.push_back(j);
            }
        }
    }
    return 0;
}


